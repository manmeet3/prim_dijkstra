// Manmeet Singh - msingh11@ucsc.edu

/* edgeList.h
 * This header file makes the list functions of edgeList.c
 * available for external calls, in this case - to graph04.c
 * (following the ADT concept).
 */

#ifndef C101EdgeList
#define C101EdgeList
/* Multiple typedefs for the same type are an error in C. */

typedef struct EdgeListNode * EdgeList;

typedef struct EdgeInfoStruct
    {
    int to;
    double wgt;
    }
    EdgeInfo;

/** edgeNil denotes the empty EdgeList */
extern const EdgeList edgeNil;

/* Access functions
 * Pre-conditions: a non-empty EdgeList
 */

/** first
*/
EdgeInfo edgeFirst(EdgeList oldL);

/** rest
*/
EdgeList edgeRest(EdgeList oldL);

/* Constructors
 * Pre-conditions: A null/data containing EdgeList oldL
 * and an EdgeInfo element to be inserted.
 *
 * Post-conditions: New EdgeList node created with EdgeInfo newE
 * with oldL as the next node.
 */

/** cons
*/
EdgeList edgeCons(EdgeInfo newE, EdgeList oldL);

#endif
