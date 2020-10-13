#include <stdio.h>
#include <pthread.h>
#include "request.h"
#include "io_helper.h"

char default_root[] = ".";

//the queue data structure
typedef struct node_t{
    int value;
    struct node_t *next;
}node;

typedef struct queue_t{
    int size;
    node *head;
    node *foot;
}queue;
//initialize a new node
node *newNode(int value){
    node * A=(node *) malloc(sizeof(node));
    A->value=value;
    A->next=NULL;
    return A;
}

//initialize a queue
queue * newQueue(){
    queue * A=(queue *) malloc(sizeof(queue));
    A->size=0;
    A->head=NULL;
    A->foot=NULL;
    return A;
}

int getSize(queue *A){
    return A->size;
}
//add to the end of the queue
void enque(queue *A,int value){
    //if it is empty queue
    node * B;
    if(getSize(A)==0){
        B=newNode(value);
        A->head=B;
        A->foot=B;
        A->size++;
        return;
    }
    //if it is not empty
    B=newNode(value);
    A->foot->next=B;
    A->foot=B;
    A->size++;
    return;
}

//remove from queue
int deque(queue *A){
    if(A->head==NULL){
        return -1;
    }
    int B=A->head->value;
    A->size--;
    A->head=A->head->next;
    return B;
}

/*int main(int argc, char *argv[]) {
    queue *A=newQueue();
    printf("%d\n",deque(A));
    enque(A,2);
    enque(A,5);
    enque(A,7);
    printf("%d\n",deque(A));
    printf("%d\n",deque(A));
    printf("%d\n",deque(A));
    printf("%d\n",deque(A));
}*/
queue *buff;
pthread_cond_t empty,fill;
pthread_mutex_t mutex;

 void * worker_thread() {
     int conn_fd;
     pthread_mutex_lock(&mutex);
     while (getSize(buff) == 0) {
         pthread_cond_wait(&fill, &mutex);
     }
     conn_fd = deque(buff);
     pthread_cond_signal(&empty);
     pthread_mutex_unlock(&mutex);
     printf("thread %ud is working on fd %d and buffSize is %d\n", pthread_self(), conn_fd,getSize(buff));
     request_handle(conn_fd);
     close_or_die(conn_fd);
 }

//
// ./wserver [-d <basedir>] [-p <portnum>] 
//
int main(int argc, char *argv[]) {
    int c;
    char *root_dir = default_root;
    int port = 10000;
    int buffSize=8;
    buff=newQueue();
    
    while ((c = getopt(argc, argv, "d:p:b:")) != -1)
	switch (c) {
        case 'd':
            root_dir = optarg;
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case 'b':
            buffSize = atoi(optarg);
            break;
        default:
            fprintf(stderr, "usage: wserver [-d basedir] [-p port]\n");
            exit(1);
    }

    // run out of this directory
    chdir_or_die(root_dir);

    //creat worker threads
    pthread_t * worker=(pthread_t *) malloc(buffSize*sizeof(pthread_t));

    for(int i=0;i<buffSize;i++) {
        pthread_create(&worker[i], NULL, worker_thread, NULL);
    }

    for(int i=0;i<buffSize;i++){

        sleep(2);
    }

    // now, get to work
    int listen_fd = open_listen_fd_or_die(port);
    while (1) {
        struct sockaddr_in client_addr;
        int client_len = sizeof(client_addr);
        int conn_fd = accept_or_die(listen_fd, (sockaddr_t *) &client_addr, (socklen_t *) &client_len);
        pthread_mutex_lock(&mutex);
        while (getSize(buff) == buffSize) {
            pthread_cond_wait(&empty, &mutex);
        }
        enque(buff,conn_fd);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}


    


 
