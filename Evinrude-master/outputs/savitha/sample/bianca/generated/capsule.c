#define _GNU_SOURCE
#include "capsule.h"

/* ---------------------------------------- */
unsigned int id(pthread_t id);
       
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
        tid = hashid.processes[id(_BIANCA_monitor_pthread_self())];
        assert(tid != NULL);
        VERBOSE("[INTERCEPT] --> SET TLS (%d)\n", tid->id);
        pthread_mutex_unlock(&inside);
       
        /* Tell the calling thread that we don't need its data anymore */
        pthread_mutex_lock(&((wrapper_t*)data)->lock);
        pthread_cond_signal(&((wrapper_t*)data)->wait);
        pthread_mutex_unlock(&((wrapper_t*)data)->lock);
       
    /* Call the real function */
    //assert(arg != NULL);     
    return start_routine(arg);
}
/* ---------------------------------------- */



/* ---------------------------------------- */

/* Recherche de l'identifiant pour un thread_id donné */
unsigned int id(pthread_t id) {
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

/* Initialisation de BIANCA */
void bianca_init() {
        int i;
       
        /* Définition et surcharge des fonctions systÚme utilisees par le moniteur */
        if (!_BIANCA_monitor_fprintf) {
                _BIANCA_monitor_fprintf = (int (*)(FILE *, const char *, ...)) dlsym (RTLD_NEXT, "fprintf");
                if (_BIANCA_monitor_fprintf == NULL) { return; } else { VERBOSE("[!] Surcharge de FPRINTF : OK !\n"); }
        }
        if (!_BIANCA_monitor_free) {
                _BIANCA_monitor_free = (void (*)(void *)) dlsym (RTLD_NEXT, "free");
                if (_BIANCA_monitor_free == NULL) { return; } else { VERBOSE("[!] Surcharge de FREE : OK !\n"); }
        }
        if (!_BIANCA_monitor_pthread_mutex_init) {
                _BIANCA_monitor_pthread_mutex_init = (int (*)(pthread_mutex_t *, const pthread_mutexattr_t *)) dlsym (RTLD_NEXT, "pthread_mutex_init");
                if (_BIANCA_monitor_pthread_mutex_init == NULL) { return; } else { VERBOSE("[!] Surcharge de PTHREAD_MUTEX_INIT !\n"); }
        }
        if (!_BIANCA_monitor_pthread_self) {
                _BIANCA_monitor_pthread_self = (pthread_t (*)(void)) dlsym (RTLD_NEXT, "pthread_self");
                if (_BIANCA_monitor_pthread_self == NULL) { return; } else { VERBOSE("[!] Surcharge de PTHREAD_SELF !\n"); }
        }
       
        /* Evenements �  capter */
        

        _BIANCA_monitor_pthread_mutex_init(&lock, NULL);
        _BIANCA_monitor_pthread_mutex_init(&inside, NULL);
       
        /* Initialisation de la table des identités */
        for (i = 0; i < 100; i++) { hashid.threads[i] = (pthread_t) -1; }
        hashid.size = 0;
       
        /* Initialisation du réseau */
        global_table = init(id(_BIANCA_monitor_pthread_self()), MAIN_ENTRY);
        tid = find_process_id(&global_table,0);
       
        VERBOSE("INITIALISATION TERMINEE\n");
}
