#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#define NUMCPUS 8
double timer(){
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec+(double)current_time.tv_usec/1000000);
}

typedef struct __counter_t {
    int global; // global count
    pthread_mutex_t glock; // global lock
    int local[NUMCPUS]; // per-CPU count
    pthread_mutex_t llock[NUMCPUS]; // ... and locks
    int threshold; // update frequency
     } counter_t;

 // init: record threshold, init locks, init values
 // of all local counts and global count
void init(counter_t *c, int threshold) {
     c->threshold = threshold;
     c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    int i;
    for (i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
         }
     }

 // update: usually, just grab local lock and update
 // local amount; once local count has risen ’threshold’,
// grab global lock and transfer local values to it
void update(counter_t *c, int threadID, int amt) {
     int cpu = threadID % NUMCPUS;
    pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) {
         // transfer to global (assumes amt>0)
         pthread_mutex_lock(&c->glock);
         c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
        }
    pthread_mutex_unlock(&c->llock[cpu]);
     }

// get: just return global amount (approximate)
int get(counter_t *c) {
    pthread_mutex_lock(&c->glock);
   int val = c->global;
   pthread_mutex_unlock(&c->glock);
   return val; // only approximate!
   }

   void * mythread(counter_t *A){
    int N=1000000/NUMCPUS;
    for (int i=0;i<N;i++)
      update(A,pthread_self(),1);
   }

void main(int argc,char * argv[]){
    int NN=10000000;
    counter_t A;
    double start,end;
    init(&A,100);
    pthread_t p[NUMCPUS];
    start=timer();
    for (int i=0;i<NUMCPUS;i++){
        pthread_create(&p[i],NULL,mythread,&A);
    }
    for (int i=0;i<NUMCPUS;i++) {
        pthread_join(p[i], NULL);
    }
    end=timer();
    printf("Result counter: %d\n",A.global);
    printf("Time: %f\n",end-start);
}