// Manmeet Singh - msingh11@ucsc.edu
// graph04.c

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <unistd.h>
#include <math.h>

#include "minPQ.h"
#include "edgeList.h"
#include "primDJK.h"

#define STDIN_NAME	"-"
char *exec_name = NULL;
int exit_status = 0;
static int task = 0;

typedef struct Edge {
	int from;
	int to;
	double weight;
} Edge;

int* initArray(int n){
	return calloc (n+1, sizeof(int));
}

// Returns first line from input, the value of n.
char* getLine (FILE* in){
	char line[256];
	char* n = fgets (line, 1024, in);
	return n;
}

// Returns an array of n+1 length initiated to edgeNil.
EdgeList* initEdges (int n){
	EdgeList* graph = calloc (n+1, sizeof(EdgeList));
	int i;
	for (i=1;i<n+1;+i++){
		graph[i] = edgeNil;
	}
	return graph;
}

// Extracts and saves graph values from the line under observation
Edge parseEdge(char* line){
	Edge newE;
	int numFields;
	numFields = sscanf(line, " %d %d %lf %*s", &newE.from,
			              &newE.to, &newE.weight);
	if (numFields < 2 || numFields > 3){
		printf("Bad edge: %s", line);
	}
	if (numFields == 2)
		newE.weight = 0.0;
	return newE;
}

// Returns pointer to filename mentioned as argv[1].
FILE* scan_file (char* filename){
	FILE *inbuf;
	if (!strcmp(filename, STDIN_NAME)) inbuf = stdin;
	else inbuf = fopen (filename, "r");

	if (inbuf == NULL){
	fprintf (stderr, "%s: Unable to open input '%s' -> '%s'\n",
			exec_name, filename, strerror(errno));
	exit(exit_status++);
	}
	printf ("Opening %s for input\n", filename);

	return inbuf;
}

// Loads the edges created by parseEdge into the array
// Also checks if edge values are within range of n and
// skips them accordingly.
int loadEdges (FILE* in, EdgeList* adjVertices, int n){
	int num = 0;
	char line[1024];
	char* fgetsRetn;
	Edge e;
	EdgeInfo newInfo;

	fgetsRetn = fgets (line, 1024, in);

	while (fgetsRetn == line){
		//printf ("%s",fgetsRetn);
	    e = parseEdge(fgetsRetn);
		if(e.from < 1 || e.to <1 )
			printf("%d or %d an invalid edge", e.from, e.to);
	    if (e.from > (n) || e.to > (n))
	    	printf("%d or %d is greater than n=%d\n", e.from, e.to, n);
	    else{
	    	newInfo.to = e.to;
	    	newInfo.wgt = e.weight;
	    	//printf("%d %d %lf\n",e.from, newInfo.to, newInfo.wgt);
			adjVertices[e.from] = edgeCons(newInfo, adjVertices[e.from]);
			// If looking for MST, add reverse edge also;
			if (task == 0){
				newInfo.to = e.from;
				newInfo.wgt = e.weight;
				adjVertices[e.to] = edgeCons(newInfo, adjVertices[e.to]);
			}
			num++;
	    }
		fgetsRetn = fgets (line, 1024, in);
	}
	return num;
}


// Print function for an array of edgeList nodes.
void printList(EdgeList* adjInfo, int n){
	int i;
	EdgeList tmp;
	EdgeInfo tmpInfo;
	printf("Vertex\t[To, Weight]\n");
	for (i=1; i<=n; i++)
    {
		printf("%d\t",i);

		if (adjInfo[i] != NULL){
			tmpInfo = edgeFirst(adjInfo[i]);

			printf("[%d, %lf]", tmpInfo.to, tmpInfo.wgt);

			tmp = edgeRest(adjInfo[i]);
			while (tmp != NULL ){
				tmpInfo = edgeFirst(tmp);
				printf("[%d, %lf]", tmpInfo.to, tmpInfo.wgt);
				tmp = edgeRest(tmp);
			}
			printf("\n");
		}
		else printf("[NULL]\n");
    }
}

// Executes and prints the algorithm from primDJK.c according to command line opts.
void greedyTree(EdgeList* adjInfo,int status[],double priority[],int parent[],int n,int starting_V){
	MinPQ pq = createPQ(n,status,priority,parent);
	if (task == 0){
		primMST(adjInfo,starting_V,pq,n);
		printf("\n\t\t::Prim's MST::\nStarting vertex = %d\nVertex\t Status\t\tPriority\tParent\n", starting_V);
	}else {
		dijkstraSSST(adjInfo,starting_V,pq,n);
		printf("\n\t\t::Dijkstra's SSST::\nStarting vertex = %d\nVertex\t Status\t\tPriority\tParent\n", starting_V);

	}
	int i;
	for (i=1;i<=n;i++){
	printf(" %-7d  %-5d\t\t%-16lf%-10d\n",i,status[i],priority[i],parent[i]);
	}
	printf("*status: 116=INTREE 117=UNSEEN 102=FRINGE\n");

}

// Checks cmd line ags for a valid starting vertex, D/P and input file.
// Prim's alg is run by default if D or d is not detected in cmd line.
int checkOpts (int argc, char** argv, int n){
	int start_v;
	int check = sscanf (argv[2], "%i", &start_v);
	//int start_v = atoi(argv[2]);
	if(start_v > n || start_v < 1|| check!=1){
		fprintf (stderr, "Invalid Starting Vertex: Not in the graph");
		exit(1);
	}
	int option = getopt (argc, argv, "dDpP");
		switch (option) {
		case 'd': task = 1;
		break;
		case 'D': task = 1;
		break;
		case 'p': task = 0;
		break;
		case 'P': task = 0;
		break;
		}
	return start_v;
}

int main (int argc, char** argv){
	int m;
	int n;
	int starting_V;
	EdgeList* adjInfo;
	exec_name = basename (argv[0]);
	if (argc != 4){
		fprintf (stderr, "Usage: %s -D/-P startingVertex graph.in\n\t\tD=dijkstra/P=prim\n", exec_name);
		return exit_status;
	}
	FILE* in = scan_file(argv[3]);
	char* n_string = getLine(in);
	n = atoi(n_string);
	starting_V = checkOpts(argc, argv, n);

	adjInfo = initEdges(n);
	m = loadEdges(in, adjInfo, n);
	fclose(in);
	// print n and m
	printf ("n = %d\n", n);
	if (task==0) printf("m = %d\t\t\tUNDIRECTED\n",m);
	else printf("m = %d\n", m);
	printList(adjInfo, n);

	int* parent = initArray(n);
	double* fringeWgt = calloc(n+1, sizeof(double));
	int* status = initArray(n);
	greedyTree(adjInfo,status,fringeWgt,parent,n,starting_V);

	return exit_status;
}
