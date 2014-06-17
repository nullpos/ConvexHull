#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <stdio.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

#define N 10

typedef struct {
    int x;
    int y;
} point2_t;

typedef struct {
    point2_t p;
    point2_t q;
} edge_t;

extern point2_t* directConvexHull(point2_t* /* point list */, point2_t* /* answer */);
extern int show(point2_t*);
extern int crossProduct(point2_t*, point2_t*, point2_t*);
extern int sortEdges(edge_t*);
extern int edgeToPoint(point2_t*, edge_t*);
extern int addEdge(point2_t*, point2_t*, edge_t*);

extern int isValidEdge(edge_t);
#endif
