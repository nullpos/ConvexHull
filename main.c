#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "./ConvexHull.h"
#include "./gnuplot.h"
#include "./Interface.h"

#define XYMAX 100
#define XYMIN -100

point2_t IP;

int main(int argc, char *argv[]) {
    int num;
    FILE *fp;
    point2_t *answer;
    point2_t *points;
    IP.x = INT_MAX;
    IP.y = INT_MAX;

    if(argc > 1) {
        if(sscanf(argv[1], "%d", &num) != EOF) {
            points = (point2_t *)malloc(sizeof (point2_t) * (num+1));
            answer = (point2_t *)malloc(sizeof (point2_t) * (num+1));
            if(points == NULL || answer == NULL) exit(1);

            srand((unsigned int)time(NULL));
            int i;
            for(i=0; i<num; i++) {
                (points + i)->x = getRandInt();
                (points + i)->y = getRandInt();
            }
            *(points + num) = IP;
            *answer = IP;
        } else if((fp = fopen(argv[1], "r")) != NULL) {
            //
        } else {
            usage();
        }
    } else {
        usage();
    }

    //directConvexHull(points, answer, num);
    wrappingConvexHull(points, answer, num);

    //show(points);
    //show(answer);

    outputToGnuplot(points, answer);

    free(answer);
    free(points);
    return 0;
}

int getRandInt() {
    return XYMIN + (int)( rand() * (XYMAX - XYMIN + 1.0) / (1.0 + RAND_MAX) );
}
int usage() {
    printf("usage: ./ConvexHull.exe [filename]\n");
    printf("usage: ./ConvexHull.exe [num]\n");
    exit(1);
    return 0;
}
