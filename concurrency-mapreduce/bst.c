#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <common_thread.h>

//define node class
typedef struct node
{
    struct node *left;
    struct node *right;
    char * key;
    char * value;
} node;

//creat a new node
node *newNode(char * key,char *value)
{
    node *t = (node *)malloc(sizeof(node));
    t->key=(char *)malloc(sizeof(key));
    strcpy(t->key,key);
    t->value=(char *)malloc(sizeof(value));
    strcpy(t->value,value);
    t->left = NULL;
    t->right = NULL;
    return t;
}

//add a new node to the tree
node *addNode(node *rootNode, char * key,char * value)
{
    if (rootNode == NULL)
    {
        rootNode = newNode(key,value);
        return rootNode;
    }
    int flag=strcmp(key, rootNode->key);  //return 0 if equal, negative means first is smaller than the second
    if (flag>=0)
    {
        //if the key value is larger or equal to the present rootNode, then add to the right side
        rootNode->right = addNode(rootNode->right, key,value);
    }
    else
    {
        rootNode->left = addNode(rootNode->left, key,value);
    }
    return rootNode;
}

void cleanTree(node *root)
{
    if (root != NULL)
    {
        if (root->left != NULL)
        {
            cleanTree(root->left);
        }
        if (root->right != NULL)
        {
            cleanTree(root->right);
        }
        free(root);
        root = NULL;  // reset pointer
    }
}

int NC=0;
void printTree(node *root)
{
    if (root != NULL)
    {
        printTree(root->left);
        printf("%d %s %s\n", NC++,root->key,root->value);
        printTree(root->right);
    }
}

void countKey(node *root,char * key,int * count)
{

    if (root != NULL)
    {
        countKey(root->left,key,count);
        if(strcmp(root->key,key)>0)
            return;
        if(strcmp(root->key,key)==0) {
            (*count)++;
        }
        countKey(root->right,key,count);
    }
}

/*pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void *map(void * fileName){
    printf("thread: %lu started\n",pthread_self());
    FILE *fp = fopen((char *)fileName, "r");
    assert(fp != NULL);
    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, fp) != -1) {
        char *token, *dummy = line;
        while ((token = strsep(&dummy, " \t\n\r")) != NULL) {
            Pthread_mutex_lock(&lock);
            root=addNode(root,token, '1');
            Pthread_mutex_unlock(&lock);
        }
    }
    free(line);
    fclose(fp);
}

void main(){
    char * fileName1="/home/hushantou/ostep-projects/concurrency-mapreduce/Henry1";
    char * fileName2="/home/hushantou/ostep-projects/concurrency-mapreduce/Henry1";
    pthread_t p1, p2,p3,p4,p5;
    printf("main: begin\n");
    Pthread_create(&p1, NULL, map, fileName1);
    Pthread_create(&p2, NULL, map, fileName2);
    Pthread_create(&p3, NULL, map, fileName2);


    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    Pthread_join(p3, NULL);

    printTree(root);
    cleanTree(root);
}*/