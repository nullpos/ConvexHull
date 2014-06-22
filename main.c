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

int main(int argc, char *argv[]) {
    if(argc == 1) usage(argv);
    int data_num = 0;
    FILE *fp;
    point2_t *answer;
    point2_t *points;
    IP.x = INT_MAX;
    IP.y = INT_MAX;

    int time_o = FALSE, way_o = FALSE, gnu_o = FALSE;
    point2_t* (*way_f)(point2_t*, point2_t*, int) = directConvexHull;

    int ch;
    extern char *optarg;
    extern int optind, opterr;

    while((ch = getopt(argc, argv, "df:gr:tw")) != -1) {
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
        case 'g':
            gnu_o = TRUE;
            break;
        case 'r':
            if(way_o == TRUE) {
                fprintf(stderr, "Only -f or -r can use.\n");
                break;
            }
            way_o = TRUE;

            data_num = atoi(optarg);
            if(data_num < 3) {
                fprintf(stderr, "I cannot search Convex Hull with under 2 points...huh?\n");
                exit(1);
            }

            points = (point2_t *)malloc(sizeof (point2_t) * (data_num+1));
            answer = (point2_t *)malloc(sizeof (point2_t) * (data_num+1));
            if(points == NULL || answer == NULL) {
                fprintf(stderr, "Error: Cannot allocate memory\n");
                exit(1);
            }

            srand((unsigned int)time(NULL));
            int i;
            for(i=0; i<data_num; i++) {
                (points + i)->x = i*2;//getRandInt();
                (points + i)->y = i*i;//getRandInt();
            }
            *(points + data_num) = IP;
            *answer = IP;
            break;
        case 'f':
            if(way_o == TRUE) {
                fprintf(stderr, "Error: Only -f or -r can use.\n");
                break;
            }
            way_o = TRUE;

            fp = fopen(optarg, "r");
            if(fp == NULL) {
                fprintf(stderr, "Error: Cannot open %s .\n", optarg);
                exit(1);
            }

            data_num = 0;
            char c;
            while((c = getc(fp)) != EOF) {
                if(c == '\n') data_num++;
            }
            if(data_num < 3) {
                fprintf(stderr, "I cannot search Convex Hull with under 2 points...huh?\n");
                exit(1);
            }

            points = (point2_t *)malloc(sizeof (point2_t) * (data_num+1));
            answer = (point2_t *)malloc(sizeof (point2_t) * (data_num+1));
            if(points == NULL || answer == NULL) {
                fprintf(stderr, "Error: Cannot allocate memory.\n");
                exit(1);
            }

            rewind(fp);

            int j = 0;
            while((fscanf(fp, "%d\t%d", &((points + j)->x), &((points + j)->y))) != EOF) {
                j++;
            }
            *(points + data_num) = IP;
            *answer = IP;
            break;
        default:
            usage(argv);
            break;
         }
    }
    argc -= optind;
    if((argc > -1 && optind == 0) || way_o == FALSE) usage(argv);
    argv += optind;

    clock_t c1,c2;
    if(time_o == TRUE) {
        c1 = clock();
    }

    (*way_f)(points, answer, data_num);

    if(time_o == TRUE) {
        c2 = clock();
        printf("clock time = %f\n", (double) (c2 - c1)/CLOCKS_PER_SEC);
    }
    if(gnu_o == TRUE) {
        outputToGnuplot(points, answer);
    }

    free(answer);
    answer = NULL;
    free(points);
    points = NULL;
    fclose(fp);
    printf("Complete.\n");
    return 0;
}

int getRandInt() {
    return XYMIN + (int)( rand() * (XYMAX - XYMIN + 1.0) / (1.0 + RAND_MAX) );
}
int usage(char *argv[]) {
    fprintf(stderr, "usage: %s {-r number|-f filename} [-d|-r] [option] ...\n", argv[0]);
    fprintf(stderr, "%s\n", "    -d,         , Search Convex Hull with direct way.");
    fprintf(stderr, "%s\n", "    -f filename , Input points data from 'filename' file.");
    fprintf(stderr, "%s\n", "    -r number   , Input random 'number' data points.");
    fprintf(stderr, "%s\n", "    -t          , Measure searching time and show it.");
    fprintf(stderr, "%s\n", "    -w          , Search Convex Hull with wrapping way.");
    fprintf(stderr, "%s\n", "");
    fprintf(stderr, "%s\n", "If you want to input from files, you must make file each 1 row like this example.");
    fprintf(stderr, "%s\n", "    ex.) 234[tab]-567");
    fprintf(stderr, "%s\n", "You shouldn't input the invalid (out of Integer range) coordinates of the points.");
    exit(1);
    return 0;
}
