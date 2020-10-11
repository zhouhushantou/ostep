#include <mapreduce.h>
#include <common_thread.h>
#include <bst.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

node ** root;
pthread_mutex_t *lock;
int num_partitions;
int num_mappers;
int num_reducers;

double timer(){
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec+(double)current_time.tv_usec/1000000);
}

unsigned long MR_DefaultHashPartition(char *key, int num_partitions) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++) != '\0')
        hash = hash * 33 + c;
    return hash % num_partitions;
}

void MR_Emit(char * key, char* value) {
    unsigned long N=MR_DefaultHashPartition(key,num_partitions);
    Pthread_mutex_lock(&lock[N]);
    root[N] = addNode(root[N], key, value);
    Pthread_mutex_unlock(&lock[N]);
}

void *map(void * fileName){
    //printf("map thread: %lu started\n",pthread_self());
    FILE *fp = fopen((char *)fileName, "r");
    assert(fp != NULL);
    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, fp) != -1) {
        char *token, *dummy = line;
        while ((token = strsep(&dummy, " \t\n\r")) != NULL) {
            MR_Emit(token, "1");
        }
    }
    free(line);
    fclose(fp);
}

void *reduce(char *key) {
    //printf("reduce thread: %lu started\n",pthread_self());
    int count = 0;
    unsigned long N=MR_DefaultHashPartition(key,num_partitions);
    countKey(root[N],key,&count);
    printf("%s %d\n", key, count);
}

void main() {
    char *fileName[] = {"/home/hushantou/ostep-projects/concurrency-mapreduce/chap1",
                        "/home/hushantou/ostep-projects/concurrency-mapreduce/chap2",
                        "/home/hushantou/ostep-projects/concurrency-mapreduce/chap3",
                        "/home/hushantou/ostep-projects/concurrency-mapreduce/chap4",
                        "/home/hushantou/ostep-projects/concurrency-mapreduce/chap5",
                        "/home/hushantou/ostep-projects/concurrency-mapreduce/chap6",
                        "/home/hushantou/ostep-projects/concurrency-mapreduce/chap7",
                        "/home/hushantou/ostep-projects/concurrency-mapreduce/chap8"};
    num_partitions = 10;
    num_mappers = 8;
    num_reducers = 9;

    pthread_t *p=(pthread_t *)malloc(num_mappers*sizeof(pthread_t));
    root = (node **) malloc(num_partitions * sizeof(node *));
    for (int i = 0; i < num_partitions; i++) {
        root[i] = NULL;
    }
    lock = (pthread_mutex_t *) malloc(num_partitions * sizeof(pthread_mutex_t));
    for (int i = 0; i < num_partitions; i++) {
        pthread_mutex_init(&lock[i],NULL);
    }
    double start, end;

    for (int i = 0; i < num_mappers; i++) {
        Pthread_create(&p[i], NULL, map, fileName[i]);
    }
    for (int i = 0; i < num_mappers; i++) {
        Pthread_join(p[i], NULL);
    }


    //for (int i = 9; i < num_partitions; i++) {
 //       printTree(root[i]);
   // }

    pthread_t *q=(pthread_t *)malloc(num_reducers*sizeof(pthread_t));
    char * keys[]={"other","world","never","the","how","for","by","pride","next"};
    start = timer();
   for (int i = 0; i < num_reducers; i++) {
        Pthread_create(&q[i], NULL, reduce,keys[i]);
    }
    for (int i = 0; i < num_reducers; i++) {
        Pthread_join(q[i], NULL);
    }
    end = timer();
    printf("time spent:%f", end - start);
    for (int i = 0; i < num_partitions; i++) {
        cleanTree(root[i]);
    }
}