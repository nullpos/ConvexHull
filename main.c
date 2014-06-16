#include <stdio.h>
#include <limits.h>
#include "./ConvexHull.h"

#define N 10

int main(int argc, char *argv[]) {
    vector2_t vectors[N] = {
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

    vector2_t answer[N] = {{1,0},{0,-1},{INT_MAX,INT_MAX}};

    //directConvexHull(vectors, answer);
    show(answer);

    return 0;
}
