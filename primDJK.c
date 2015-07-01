// Manmeet Singh - msingh11@ucsc.edu
// primDJK.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "minPQ.h"
#include "edgeList.h"
#include "primDJK.h"

void print_MST(MinPQ pq, int n){
	//printf("MEOW");
  int i;
  for(i=1;i<=n;i++){
    if(getStatus(pq,i)==INTREE){
      if(getParent(pq,i)!=-1)
      printf("There is an edge from %d to %d in the MST\n", i, getParent(pq,i));
    }
  }
}

void updateFringe(MinPQ pq,EdgeList adjInfoOfV, int v){
	int to;
	double wt;
	EdgeList remAdj = adjInfoOfV;
	EdgeInfo tmpInfo;
	while(remAdj!=NULL){
		tmpInfo = edgeFirst(remAdj);
		to = tmpInfo.to;
		wt = tmpInfo.wgt;
		if(getStatus(pq,to) == UNSEEN){
			insertPQ(pq,to,wt,v);
		}else{
			if(getStatus(pq,to) == FRINGE)
				if(getPriority(pq,to) > wt){
					decreaseKey(pq,to,wt,v);
				}
		}
		remAdj = edgeRest(remAdj);
	}

}

void primMST(EdgeList* adjInfo, int start_v, MinPQ pq, int n){
	int v;
	insertPQ(pq,start_v,0.0,-1);
	while(isEmptyPQ(pq)!=0){
		v = getMin(pq);
		delMin(pq);
		updateFringe(pq, adjInfo[v], v);
	}
	//print_MST(pq,n);
}

void updateFringeSSST(MinPQ pq,EdgeList adjInfoOfV,int v){
	double myDist, newDist;
	int to;
	EdgeList remAdj = adjInfoOfV;
	EdgeInfo tmpInfo;
	myDist = getPriority(pq,v);
	while (remAdj!=NULL){
		tmpInfo = edgeFirst(remAdj);
		to = tmpInfo.to;
		newDist = myDist + tmpInfo.wgt;
		if(getStatus(pq,to) == UNSEEN)
			insertPQ(pq,to,newDist,v);
		else{
			if(getStatus(pq,to) == FRINGE)
			if (newDist < getPriority(pq,to))
				decreaseKey(pq,to,newDist,v);
	}
	remAdj = edgeRest(remAdj);
	}
}

void dijkstraSSST(EdgeList* adjInfo, int start_v, MinPQ pq, int n){
	int v;
	insertPQ(pq,start_v,0.0,-1);
	while(isEmptyPQ(pq)!=0){
		v = getMin(pq);
		delMin(pq);
			updateFringeSSST(pq,adjInfo[v],v);
	}

}

