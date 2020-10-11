//
// Created by hushantou on 2020/10/11.
//

#ifndef CONCURRENCY_MAPREDUCE_BST_H
#define CONCURRENCY_MAPREDUCE_BST_H

typedef struct node node;
node *newNode(char * key,char* value);
node *addNode(node *rootNode, char * key,char* value);
void cleanTree(node *root);
void printTree(node *root);
void *map(void * fileName);
void countKey(node *root,char * key,int * count);

#endif //CONCURRENCY_MAPREDUCE_BST_H
