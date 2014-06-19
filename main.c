#include <stdio.h>
#include <limits.h>
#include "./ConvexHull.h"
#include "./Interface.h"

int main(int argc, char *argv[]) {
    point2_t points[N] = {
        {-7,2},
        {-5,-4},
        {-3,0},
        {-2,5},
        {-1,2},
        {0,-3},
        {2,-7},
        {4,2},
        {5,-3},
        {0,-3}
    };

    point2_t ip = {INT_MAX, INT_MAX};
    point2_t answer[N+1] = {ip};
    
    //directConvexHull(points, answer);
    wrappingConvexHull(points, answer);
    show(answer);

    return 0;
}
