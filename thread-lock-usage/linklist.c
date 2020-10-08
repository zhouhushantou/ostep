#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <malloc.h>

#define NUMCPUS 1
double timer(){
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec+(double)current_time.tv_usec/1000000);
}

 // basic node structure
 typedef struct __node_t {
    int key;
     struct __node_t *next;
     } node_t;

 // basic list structure (one used per list)
 typedef struct __list_t {
     node_t *head;
     pthread_mutex_t lock;
     } list_t;

void List_Init(list_t *L) {
     L->head = NULL;
     pthread_mutex_init(&L->lock, NULL);
     }

 void List_Insert(list_t *L, int key) {
    // synchronization not needed
     node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
         perror("malloc");
         return;
         }
     new->key = key;

    // just lock critical section
     pthread_mutex_lock(&L->lock);
     new->next = L->head;
     L->head = new;
     pthread_mutex_unlock(&L->lock);
     }

 int List_Lookup(list_t *L, int key) {
     int rv = -1;
     pthread_mutex_lock(&L->lock);
     node_t *curr = L->head;
     while (curr) {
         if (curr->key == key) {
             rv = 0;
             break;
             }
         curr = curr->next;
        }
     pthread_mutex_unlock(&L->lock);
    return rv; // now both success and failure
    }

void * mythread(list_t *A){
    int N=1000000/NUMCPUS;
    for (int i=0;i<N;i++)
        List_Insert(A,1);
}

void main(int argc,char * argv[]){
    list_t A;
    double start,end;
    List_Init(&A);
    pthread_t p[NUMCPUS];
    start=timer();
    for (int i=0;i<NUMCPUS;i++){
        pthread_create(&p[i],NULL,mythread,&A);
    }
    for (int i=0;i<NUMCPUS;i++) {
        pthread_join(p[i], NULL);
    }
    end=timer();
    printf("Time: %f\n",end-start);
}