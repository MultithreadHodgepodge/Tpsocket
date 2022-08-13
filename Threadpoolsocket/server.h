#include <netinet/in.h>  
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "../rwlock/rwlock.h"
#include"../simpleThreadpool/threadpool.h"
#define PORT 8080
void (*factory[])(void *);
static int data = 1;
sem_t x, y;
int reader_count = 0;

rwlock_t *datalock;