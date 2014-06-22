#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <stdlib.h>
#include "./Interface.h"

extern point2_t* directConvexHull(point2_t*, point2_t*, int);
extern point2_t* wrappingConvexHull(point2_t*, point2_t*, int);

#endif
