#ifndef EVENT_H
#define EVENT_H

  typedef struct {
    int owner;
    int type;
    union {
      int son;
    };
  } event_t;

/*************** GENERATED ***************/
#define SEND 1
#define PERROR 2
#define CLOSE 3
#define RECV 4
#define SOCKET 5
#define PTHREAD_CREATE 6
#define PRINTF 7
#define ACCEPT 8
#define EXIT 9
#define BIND 10
#define LISTEN 11
#define PTHREAD_DETACH 12

/** Pour le DEBUG **/
static const char* events[] = {
  "",
  "SEND",
  "PERROR",
  "CLOSE",
  "RECV",
  "SOCKET",
  "PTHREAD_CREATE",
  "PRINTF",
  "ACCEPT",
  "EXIT",
  "BIND",
  "LISTEN",
  "PTHREAD_DETACH",
  ""
};

/*****************************************/

#endif /* End of include guard: EVENT_H */

