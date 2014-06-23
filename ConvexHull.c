#include "./ConvexHull.h"

point2_t* wrappingConvexHull(point2_t *points, point2_t *answerPoints, int point_num) {
    printf("search with wrappingConvexHull()\n");
    int last = 0;
    while(isValidPoint(*(points + last)) == TRUE) {
        last++;
    }

    point2_t min = *points;
    point2_t max = *points;
    int min_i,max_i;
    int i;
    for(i=0; i<last; i++) {
        if((points + i)->y < min.y) {
            min = *(points + i);
            min_i = i;
        }
        if((points + i)->y > max.y) {
            max = *(points + i);
            max_i = i;
        }
    }

    addPoint(answerPoints, min);

    point2_t p;
    point2_t q;
    point2_t a;
    int ans_i = 0;
    int pm = 1;
    int mindeg_i;
    double mindeg, deg;
    int j;
    while(1) {
        if(isEqualPoint(*(answerPoints + ans_i), max) == TRUE) pm = -1;
        p.x = (answerPoints + ans_i)->x;
        p.y = (answerPoints + ans_i)->y;
        q.x = p.x + pm;
        q.y = p.y;

        mindeg = INT_MAX;
        for(j=0; j<last; j++) {
            a = *(points + j);
            if((isExistInPointsList(answerPoints, a) == TRUE && isEqualPoint(*answerPoints, a) == FALSE) ||
                isEqualPoint(p, a) == TRUE) {
                continue;
            }
            deg = calcDeg(p, q, a);
            if(deg >= 0 && deg < mindeg) {
                mindeg = deg;
                mindeg_i = j;
            }
        }
        if(isEqualPoint(*(points + mindeg_i), *(answerPoints + ans_i)) == TRUE) break;
        addPoint(answerPoints, *(points + mindeg_i));
        ans_i++;
    }

    return answerPoints;
}

point2_t* directConvexHull(point2_t *points, point2_t *answerPoints, int point_num) {
    printf("search with directConvexHull()\n");
    int i, j, k, flag;
    point2_t *p, *q, *a;
    edge_t *answerEdges;
    answerEdges = (edge_t *)malloc(sizeof (edge_t) * (point_num+1));
    if(answerEdges == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory.\n");
        exit(1);
    }
    edge_t ie = {IP,IP};
    *answerEdges = ie;

    int last = 0;
    while(isValidPoint(*(points + last)) == TRUE) {
        last++;
    }

    int side;
    for(i=0; i<last; i++) {
        p = (points + i);
        for(j=0; j<last; j++) {
            q = (points + j);
            if(isEqualPoint(*p, *q) == TRUE) continue;
            flag = TRUE;

            for(k=0; k<last; k++) {
                a = (points + k);
                if(isEqualPoint(*p, *a) == TRUE) continue;
                if(isEqualPoint(*a, *q) == TRUE) continue;
                if(k == i || k == j) continue;
                side = whichSideOfVector(*p, *q, *a);
                if(side == LEFT) {
                    // left side
                    flag = FALSE;
                    break;
                } else if(side == ON) {
                    if((p->x <= a->x && q->x <= a->x) || (p->x >= a->x && q->x >= a->x)) {
                        // a is outside of pq
                        flag = FALSE;
                        break;
                    } else {
                        // a is inside of pq
                    }
                }
            }
            if(flag == TRUE) {
                // all points are right-side or on
                addEdge(answerEdges, *p, *q);
                break;
            }
        }
    }
    edgeToPoint(answerPoints, answerEdges);
    free(answerEdges);
    answerEdges = NULL;
    return answerPoints;
}
