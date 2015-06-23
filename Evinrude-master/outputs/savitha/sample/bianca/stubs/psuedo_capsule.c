#define _GNU_SOURCE
#include "capsule.h"

/* ---------------------------------------- */
unsigned short id(pthread_t id);
       
typedef struct {
        int size;
        pthread_t  threads[MAXTHREADS];
        process_t* processes[MAXTHREADS];
} t_hashid;

typedef struct { 
        void * (*start_routine)(void *); 
        void * arg; 
        pthread_mutex_t lock; 
        pthread_cond_t  wait;
} wrapper_t; 

t_hashid hashid; /* Le tableau des identifiant */
pthread_mutex_t lock, inside; /* Le GIL */
global_table_t global_table; /* La table des threads */
__thread process_t* tid; /* L'identifiant en TLS du thread courant */

/* ---------------------------------------- */
/* Wrapper de la routine appelé par pthread_create */
static void * wrapper_routine(void * data) {
    /* Put user data in thread-local variables */ 
    void * (*start_routine)(void *) = ((wrapper_t*)data)->start_routine; 
    void * arg = ((wrapper_t*)data)->arg; 

        pthread_mutex_lock(&inside);
        // tid = hashid.processes[id(pthread_self())];
        // assert(tid != NULL);
        VERBOSE("[INTERCEPT] --> SET TLS (%d)\n", tid->id);
        pthread_mutex_unlock(&inside);
       
        /* Tell the calling thread that we don't need its data anymore */ 
        pthread_mutex_lock(&((wrapper_t*)data)->lock); 
        pthread_cond_signal(&((wrapper_t*)data)->wait); 
        pthread_mutex_unlock(&((wrapper_t*)data)->lock);
       
    /* Call the real function */
    //  assert(arg != NULL);   
    return start_routine(arg); 
}

/* ---------------------------------------- */

void perror(const char *s) {
        event_t e;

        pthread_mutex_lock(&lock);
        pthread_mutex_unlock(&lock);
       
        VERBOSE("[INTERCEPT] --> perror\n");
        // e.owner = tid;
        // e.type = PERROR;
        // fire(&global_table, e);
       
        _BIANCAperror(s);
}
int close(int fd) {
        event_t e;

        pthread_mutex_lock(&lock);
        pthread_mutex_unlock(&lock);

        VERBOSE("[INTERCEPT] --> close\n");
        // e.owner = tid;
        // e.type = CLOSE;
        // fire(&global_table, e);

        return _BIANCAclose(fd);
}
ssize_t write(int fd, const void *buf, size_t count) {
        event_t e;
        pthread_mutex_lock(&lock);
        pthread_mutex_unlock(&lock);

        VERBOSE("[INTERCEPT] --> write\n");
        // e.owner = tid;
        // e.type = WRITE;
        // fire(&global_table, e);

        return _BIANCAwrite(fd, buf, count);
}
int printf(const char *format, ...) {
        va_list ap;
        int ret;
        event_t e;

        pthread_mutex_lock(&lock);
        pthread_mutex_unlock(&lock);
       
        _BIANCAprintf = (int (*)(const char*,...)) dlsym (RTLD_NEXT, "printf"); 
        VERBOSE("[INTERCEPT] --> printf\n");

        // e.owner = tid;
        // e.type = PRINTF;
        // fire(&global_table, e);

        va_start(ap, format); 
        ret = vprintf(format,ap);
        va_end(ap);
        return ret;
}
void exit(int status) {
        event_t e;

        pthread_mutex_lock(&lock);
        pthread_mutex_unlock(&lock);

        VERBOSE("[INTERCEPT] --> exit\n");
        // e.owner = tid;
        // e.type = EXIT;
        // fire(&global_table, e);

        _BIANCAexit(status);
}
int __builtin_puts(const char *s) {
        event_t e;

        pthread_mutex_lock(&lock);
        pthread_mutex_unlock(&lock);
       
        VERBOSE("[INTERCEPT] --> __builtin_puts\n");
        // e.owner = tid;
        // e.type = __BUILTIN_PUTS;
        // fire(&global_table, e);
       
        return _BIANCA__builtin_puts(s);
}
int pthread_create(pthread_t* thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void* arg) {
        event_t e;
        wrapper_t wrapper_data; 

        /* Lock */
        pthread_mutex_lock(&lock);
        pthread_mutex_lock(&inside);
        VERBOSE("[INTERCEPT] --> pthread_create\n");
       
        // e.owner = tid;
        // e.type = PTHREAD_CREATE;
        // fire(&global_table, e);
       
        /* Initialize the wrapper structure */ 
        wrapper_data.start_routine = start_routine; 
        wrapper_data.arg = arg;
       
        pthread_cond_init(&wrapper_data.wait, NULL); 
        pthread_mutex_init(&wrapper_data.lock, NULL); 
        pthread_mutex_lock(&wrapper_data.lock);
       
        int ret = _BIANCApthread_create(thread, attr, &wrapper_routine, &wrapper_data);
       
        // e.son = id(*thread);
        // post_fire(&global_table, e);
        // hashid.processes[e.son] = find_process_id(&global_table, e.son);
        pthread_mutex_unlock(&inside);
       
        pthread_cond_wait(&wrapper_data.wait, &wrapper_data.lock); 

        /* Unlock */
        pthread_mutex_unlock(&lock);
        return ret;
}
int pthread_join(pthread_t thread, void **value_ptr) {
        event_t e;
        int ret = _BIANCApthread_join(thread, value_ptr);

        pthread_mutex_lock(&lock);

        VERBOSE("[INTERCEPT] --> pthread_join\n");

        // e.owner = tid;
        // e.type = PTHREAD_JOIN;
        // fire(&global_table, e);

        pthread_mutex_unlock(&lock);
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
        cle = hashid.size;
        hashid.threads[cle] = id;
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

        pthread_mutex_init(&lock, NULL);
        pthread_mutex_init(&inside, NULL);
       
        /* Initialisation de la table des identités */
        // for (i = 0; i < 100; i++) { hashid.threads[i] = (pthread_t) -1; }
        // hashid.size = 0;
       
        /* Initialisation du réseau */
        // global_table = init(id(pthread_self()), P0_1_ENTRY);
        // tid = find_process_id(&global_table,0);
}
