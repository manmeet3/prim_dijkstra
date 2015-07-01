// Manmeet Singh - msingh11@ucsc.edu
// minPQ.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "minPQ.h"

//const double INF = 9999999999;
/*
enum status {
    u  = 0,
    f = 1,
    t   = 2,
};*/

typedef struct MinPQNode * MinPQ;

struct MinPQNode;
typedef struct MinPQNode{
	int numVertices, numPQ;
	int minVertex;
	float oo;
	int* status;
	int* parent;
	double* fringeWgt;
}MinPQNode;

MinPQ createPQ(int n, int status[], double priority[], int parent[]){
	MinPQ pq = calloc(1, sizeof(MinPQ));
	pq->status = status;
	pq->parent = parent;
	pq->fringeWgt = priority;
	int i;
	for (i=1; i<=n; i++){
		pq->status[i] = UNSEEN;
		pq->parent[i] = -1;
		pq->fringeWgt[i] = INFINITY;
	}
	pq->numVertices = n;
	pq->numPQ = 0;
	pq->minVertex = -1;
	pq->oo = INFINITY;
	return pq;
}

//void insertPQ(MinPQ pq, int v, int newPar, double newW, int *parent, int *status, double *fringeWgt){
void insertPQ(MinPQ pq, int id, double priority, int par){
	int i;
	for (i=1;i<=8;i++){
		//printf("%d\n",pq->status[i]);
	}
    pq->parent[id] = par;
    pq->fringeWgt[id] = priority;
    pq->status[id] = FRINGE;
    pq->minVertex = -1;
    pq->numPQ++;
}

void decreaseKey(MinPQ pq, int id, double priority, int par){
    pq->parent[id] = par;
    pq->fringeWgt[id] = priority;
    pq->minVertex = -1;
}

void delMin(MinPQ pq){
    int oldMin = getMin(pq);
    pq->status[oldMin] = INTREE;
    pq->minVertex = -1;
    pq->numPQ--;
}

int isEmptyPQ(MinPQ pq){
	int r = pq->numPQ;
	return r;
}

void findMin(MinPQ pq){
    int v;
    double minWgt;
    minWgt = pq->oo;
    for (v=1; v<= pq->numVertices; v++){
        if (pq->status[v] == FRINGE){
            if (pq->fringeWgt[v]<minWgt){
                pq->minVertex=v;
                minWgt=pq->fringeWgt[v];
            }
        }
    }
}

int getMin(MinPQ pq){
    if (pq->minVertex == -1){
        findMin(pq);
    }
    return pq->minVertex;
}

double getPriority(MinPQ pq, int id)
{	return pq->fringeWgt[id];}

int getParent(MinPQ pq, int id)
{	return pq->parent[id];}

int getStatus(MinPQ pq, int id)
{	return pq->status[id];}
