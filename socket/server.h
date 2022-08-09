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

#define PORT 8080
sem_t x, y;
pthread_t tid;
pthread_t writerthreads[1000];
pthread_t readerthreads[1000];
int readercount = 0;