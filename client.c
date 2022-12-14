#include "client.h"
void* clienthread(void* args)
{
 
    int client_request = *((int*)args);
    int network_socket;
 
    // Create a stream socket
    network_socket = socket(AF_INET,
                            SOCK_STREAM, 0);
 
    // Initialise port number and address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
 
    // Initiate a socket connection
    int connection_status = connect(network_socket,
                                    (struct sockaddr*)&server_address,
                                    sizeof(server_address));
 
    // Check for connection error
    if (connection_status < 0) {
        puts("Error\n");
        return 0;
    }
 
    printf("Connection established %d\n", client_request);
 
    // Send data to the socket
    send(network_socket, &client_request,
         sizeof(client_request), 0);
 
    // Close the connection
    close(network_socket);
    pthread_exit(NULL);
 
    return 0;
}
 

#define QUNTITY 1000
int main(int argc,char *argv[])
{
    time_t start=time(NULL);
    FILE *f = fopen("time.txt", "w");
    printf("1. Read\n");
    printf("2. Write\n");
 
    // Input
    pthread_t tid[QUNTITY];
    int i,choice;
    for(i=0;i<QUNTITY;i++){
        choice=rand()%2;
        
        if (i % 10) {
            choice = 1;
        } else {
            choice = 0;
        }

        pthread_create(&tid[i], NULL,
                       clienthread,
                       &choice);
    }
    
 
    // Suspend execution of
    // calling thread
    for(i=0;i<QUNTITY;i++)
        pthread_join(tid[i], NULL);
    sleep(5);

    choice = 0;
    pthread_create(&tid[0], NULL,
                       clienthread,
                       &choice);
    pthread_join(tid[0], NULL);

    fprintf(f, "%ld\n", time(NULL)-start);

}