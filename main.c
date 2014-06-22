#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "./ConvexHull.h"
#include "./gnuplot.h"
#include "./Interface.h"

#define XYMAX 100
#define XYMIN -100

point2_t IP;
/*
    -t          // time

    -d,-w       // how to solve
    -r 100      // random
    -f filename // input from file
*/
int main(int argc, char *argv[]) {
    int num;
    FILE *fp;
    point2_t *answer;
    point2_t *points;
    IP.x = INT_MAX;
    IP.y = INT_MAX;

    int time_o = FALSE;
    point2_t* (*way_f)(point2_t*, point2_t*, int) = directConvexHull;

    int ch;
    extern char *optarg;
    extern int optind, opterr;

    while((ch = getopt(argc, argv, "tdwr:f:")) != -1) {
        switch(ch) {
        case 't':
            time_o = TRUE;
            break;
        case 'd':
            way_f = directConvexHull;
            break;
        case 'w':
            way_f = wrappingConvexHull;
            break;
        case 'r':
            num = atoi(optarg);
            points = (point2_t *)malloc(sizeof (point2_t) * (num+1));
            answer = (point2_t *)malloc(sizeof (point2_t) * (num+1));
            if(points == NULL || answer == NULL) {
                fprintf(stderr, "Error: Cannot allocate memory\n");
                exit(1);
            }

            srand((unsigned int)time(NULL));
            int i;
            for(i=0; i<num; i++) {
                (points + i)->x = getRandInt();
                (points + i)->y = getRandInt();
            }
            *(points + num) = IP;
            *answer = IP;
            break;
        case 'f':
            break;
        default:
            break;
         }
    }
    argc -= optind;
    argv += optind;

    clock_t c1,c2;
    if(time_o == TRUE) {
        c1 = clock();
    }

    (*way_f)(points, answer, num);

    if(time_o == TRUE) {
        c2 = clock();
        printf("clock time = %f\n", (double) (c2 - c1)/CLOCKS_PER_SEC);
    }

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
