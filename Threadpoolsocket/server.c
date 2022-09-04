#include "server.h"

// Reader Function
void reader(void* param)
{
    /* cs start */
    read_lock(datalock);
    /* cs end */

    printf("\nCurrent counter %d",data);
    sleep(5);
 
    /* cs start */
    read_unlock(datalock);
    /* cs end */

    printf("\n%d Reader is leaving",
           reader_count + 1);

}
 
// Writer Function
void writer(void* param)
{

    printf("\nWriter is trying to enter");
    /* cs start */
    write_lock(datalock);
    /* cs end */

    printf("\nWriter has entered");
    //Increment Counter
    data=data+1;

    /* cs start */
    write_unlock(datalock);
    /* cs end */


    printf("\nWriter is leaving");

}

int main(void)
{
    //Threadpool init

	TINFO_t *tinfo;
	RQ_t *rq;
	int rq_capacity=1000;
	int threadQ=4;
	readyqueue_init(&rq,rq_capacity,threadQ);
	threadpool_init(&tinfo, &rq,threadQ);
    set_job(reader,0);
	set_job(writer,1);
    datalock = lock_init();

    struct sockaddr_in stSockAddr;
    struct sockaddr_storage serverStorage;
    sem_init(&x, 0, 1);
    sem_init(&y, 0, 1);

    int SocketFD = socket(AF_INET,
                            SOCK_STREAM, 0);
 
    if(-1 == SocketFD)
    {
        perror("can not create socket");
        exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(PORT);
    stSockAddr.sin_addr.s_addr = INADDR_ANY;

    if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
        perror("error bind failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }
 
    if(-1 == listen(SocketFD, 10))
    {
        perror("error listen failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }
    int i=0;
    int counter=0;
    printf("Start Accepting\n");
    for(;;)
    {
        int addr_size = sizeof(serverStorage);
        int ConnectFD = accept(SocketFD, (struct sockaddr*)&serverStorage,
                           &addr_size);
        int choice = 0;
        
        if(0 > ConnectFD)
        {
            perror("error accept failed");
            close(SocketFD);
            exit(EXIT_FAILURE);
        }
        recv(ConnectFD,
             &choice, sizeof(choice), 0);
        add_task(rq,choice);
        
        
        /* perform read write operations ... */
        shutdown(ConnectFD, SHUT_RDWR);
        close(ConnectFD);
    }
    close_threadpool(&rq,&tinfo,threadQ);
    close(SocketFD);
    return 0;
}
