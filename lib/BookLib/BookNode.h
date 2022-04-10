#ifndef _NODE_STRUCT_HEADER
#define _NODE_STRUCT_HEADER

#include "../types.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char   *Title[300];
    char   *Author[100];
    char   *ISBN[13];
    char   *Year[4];
    int     ID;
    struct  Node *next;
} bookNode;

bookNode    *pHead = NULL;
bookNode    *pTail = NULL;
uint32      NodeID = 0;

#endif