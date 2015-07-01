// Manmeet Singh - msingh11@ucsc.edu

/* minPQ.h
 * This file serves to make minPQ.c functions externally accessible.
 * Pre and post conditions for each group of functions is listed below.
 */

#ifndef C101MinPQ
#define C101MinPQ
/* Multiple typedefs for the same type are an error in C. */

typedef struct MinPQNode * MinPQ;

#define UNSEEN ('u')
#define FRINGE ('f')
#define INTREE ('t')

/* Access functions
 * Pre-conditions: an initialized MinPQ element
*/

/** isEmpty
*/
int isEmptyPQ(MinPQ pq);

/** getMin
*/
int getMin(MinPQ pq);

/** getStatus
*/
int getStatus(MinPQ pq, int id);

/** getParent
*/
int getParent(MinPQ pq, int id);

/** getPriority
*/
double getPriority(MinPQ pq, int id);

/* Manipulation procedures
 * Pre-conditions: an initialized MinPQ element with data to modify.
 * Post-conditions: one of the three specific operations below performed
 * 					on MinPQ elt collection of data.
 */

/** delMin
*/
void delMin(MinPQ pq);

/** insertPQ
*/
void insertPQ(MinPQ pq, int id, double priority, int par);

/** decreaseKey
*/
void decreaseKey(MinPQ pq, int id, double priority, int par);

/* Constructors
 * Pre-conditions: Three initialized arrays for status, weight, parent
 *
 * Post-conditions: A MinPQ element with parents=-1, fringeWgts=oo
 * and status = UNSEEN.
 * Additional info: numPQ, numVertices, minVertex, oo
 */

/**
*/
MinPQ createPQ(int n, int status[], double priority[], int parent[]);


#endif

