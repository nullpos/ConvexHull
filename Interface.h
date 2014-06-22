#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <limits.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

#define ON 2
#define LEFT 1
#define RIGHT 0

typedef struct {
    int x;
    int y;
} point2_t;

typedef struct {
    point2_t p;
    point2_t q;
} edge_t;

extern point2_t IP;

extern int show(point2_t*);
extern long long int crossProduct(point2_t, point2_t, point2_t);
extern int whichSideOfVector(point2_t, point2_t, point2_t);
extern int sortEdges(edge_t*);
extern int edgeToPoint(point2_t*, edge_t*);
extern int addEdge(edge_t*, point2_t, point2_t);
extern int addPoint(point2_t*, point2_t);
extern int isValidEdge(edge_t);
extern int isValidPoint(point2_t);
extern double calcDeg(point2_t, point2_t, point2_t);
extern point2_t rotatePoint(point2_t, double);
#endif
