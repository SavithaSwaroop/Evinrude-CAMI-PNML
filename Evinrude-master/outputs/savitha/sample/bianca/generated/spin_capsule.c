#define _GNU_SOURCE
#include "capsule.h"

/* ---------------------------------------- */
unsigned short id(pthread_t id);
       
typedef struct {
        int size;
        pthread_t  threads[MAXTHREADS];
        process_t* processes[MAXTHREADS];
} t_hashid;

t_hashid hashid;
pthread_spinlock_t lock;
global_table_t global_table;

/* ---------------------------------------- */

void perror(const char *s) {
        event_t e;

        pthread_spin_lock(&lock);
        pthread_spin_unlock(&lock);
       
        VERBOSE("[INTERCEPT] --> perror\n");
        e.owner = hashid.processes[id(pthread_self())];
        e.type = PERROR;
        fire(&global_table, e);
       
        _BIANCAperror(s);
}
int close(int fd) {
        event_t e;

        pthread_spin_lock(&lock);
        pthread_spin_unlock(&lock);

        VERBOSE("[INTERCEPT] --> close\n");
        e.owner = hashid.processes[id(pthread_self())];
        e.type = CLOSE;
        fire(&global_table, e);

        return _BIANCAclose(fd);
}
ssize_t write(int fd, const void *buf, size_t count) {
        event_t e;
        pthread_spin_lock(&lock);
        pthread_spin_unlock(&lock);

        VERBOSE("[INTERCEPT] --> write\n");
        e.owner = hashid.processes[id(pthread_self())];
        e.type = WRITE;
        fire(&global_table, e);

        return _BIANCAwrite(fd, buf, count);
}
int printf(const char *format, ...) {
        va_list ap;
        int ret;
        event_t e;

        pthread_spin_lock(&lock);
        pthread_spin_unlock(&lock);
       
        _BIANCAprintf = (int (*)(const char*,...)) dlsym (RTLD_NEXT, "printf"); 
        VERBOSE("[INTERCEPT] --> printf\n");

        e.owner = hashid.processes[id(pthread_self())];
        e.type = PRINTF;
        fire(&global_table, e);

        va_start(ap, format); 
        ret = vprintf(format,ap);
        va_end(ap);
        return ret;
}
void exit(int status) {
        event_t e;

        pthread_spin_lock(&lock);
        pthread_spin_unlock(&lock);

        VERBOSE("[INTERCEPT] --> exit\n");
        e.owner = hashid.processes[id(pthread_self())];
        e.type = EXIT;
        fire(&global_table, e);

        _BIANCAexit(status);
}
int __builtin_puts(const char *s) {
        event_t e;

        pthread_spin_lock(&lock);
        pthread_spin_unlock(&lock);
       
        VERBOSE("[INTERCEPT] --> __builtin_puts\n");
        e.owner = hashid.processes[id(pthread_self())];
        e.type = __BUILTIN_PUTS;
        fire(&global_table, e);
       
        return _BIANCA__builtin_puts(s);
}
int pthread_create(pthread_t* thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void* arg) {
        event_t e;

        pthread_spin_lock(&lock);
       
        VERBOSE("[INTERCEPT] --> pthread_create\n");
       
        /* lock */
        e.owner = hashid.processes[id(pthread_self())];
        e.type = PTHREAD_CREATE;
        fire(&global_table, e);
       
        int ret = _BIANCApthread_create(thread, attr, start_routine, arg);
       
        e.son = id(*thread);
        post_fire(&global_table, e);
        hashid.processes[e.son] = find_process_id(&global_table, e.son);

        pthread_spin_unlock(&lock);
        return ret;
}
int pthread_join(pthread_t thread, void **value_ptr) {
        event_t e;
        int ret = _BIANCApthread_join(thread, value_ptr);

        pthread_spin_lock(&lock);

        VERBOSE("[INTERCEPT] --> pthread_join\n");

        e.owner = hashid.processes[id(pthread_self())];
        e.type = PTHREAD_JOIN;
        fire(&global_table, e);

        pthread_spin_unlock(&lock);
        return ret;
}

/* ---------------------------------------- */

unsigned short id(pthread_t id) {
        int i, cle;
        for (i = 0; i < hashid.size; i++) {
                if (hashid.threads[i] == id) { 
                        VERBOSE("Correspondance %ld -> %d\n", (long int)id, i);
                        return i;
                }
        }
       
        /* Insertion dans la table */
        hashid.threads[hashid.size] = id;
        cle = hashid.size;
        VERBOSE("Creation %ld -> %d\n", (long int)id, cle);
        hashid.size++;
       
        return cle;
}

void bianca_init() {
        int i;
       
        _BIANCAperror = (void (*)(const char*)) dlsym (RTLD_NEXT, "perror");
        _BIANCAclose = (int (*)(int)) dlsym (RTLD_NEXT, "close");
        _BIANCAexit = (void (*)(int)) dlsym (RTLD_NEXT, "exit");
        _BIANCAwrite = (int (*)(int, const void*, size_t)) dlsym (RTLD_NEXT, "write");
        _BIANCA__builtin_puts = (int (*)(const char*)) dlsym (RTLD_NEXT, "__builtin_puts");
        _BIANCApthread_create = (int (*)(pthread_t*, const pthread_attr_t*, void *(*start_routine)(void*), void*)) dlsym (RTLD_NEXT, "pthread_create");
        _BIANCAprintf = (int (*)(const char*,...)) dlsym (RTLD_NEXT, "printf");
        _BIANCApthread_join = (int (*)(pthread_t, void **value_ptr)) dlsym (RTLD_NEXT, "pthread_join");

        pthread_spin_init(&lock, NULL);
       
        /* Initialisation de la table des identités */
        for (i = 0; i < 100; i++) { hashid.threads[i] = (pthread_t) -1; }
        hashid.size = 0;
       
        /* Initialisation du réseau */
        global_table = init(id(pthread_self()), P0_1_ENTRY);
        hashid.processes[0] = find_process_id(&global_table,0);
}
