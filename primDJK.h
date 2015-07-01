// Manmeet Singh - msingh11@ucsc.edu
// primDJK.h

/* This header file extends accessibility of the prim's algorithm
 * and Dijkstra's algorithm for use in graph04.c
 * (split up from graph04.c due to its increasing length)
 */
#ifndef PRIMDJK_H_
#define PRIMDJK_H_

/* Two access functions, one for prim's MST and dijkstraSSST each.
 *
 * Pre-conditions: adjInfo with graph data (undirected for primMST),
 * starting vertex, initialized pq element, and # of vertices.
 *
 * Post-considitons: Arrays used in the MinPQ element filled with
 * prim MST or dijkstra shortest path.
 *
 */
void primMST(EdgeList* adjInfo, int start_v, MinPQ pq, int n);

void dijkstraSSST(EdgeList* adjInfo, int start_v, MinPQ pq, int n);

#endif /* PRIMDJK_H_ */
