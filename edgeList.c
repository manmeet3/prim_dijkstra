// Manmeet Singh - msingh11@ucsc.edu
// edgeList.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edgeList.h"

const EdgeList edgeNil = NULL;

typedef struct EdgeListNode{
	EdgeInfo edge;
	EdgeList next;
}EdgeListNode;

EdgeList edgeCons(EdgeInfo newE, EdgeList oldL){
    EdgeList newList = calloc (1, sizeof(struct EdgeListNode));
    	newList->edge = newE;
		newList->next = oldL;
		return newList;
}

EdgeInfo edgeFirst(EdgeList oldL)
		{ return oldL->edge; }

EdgeList edgeRest(EdgeList oldL)
		{ return oldL->next; }
