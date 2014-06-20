#include "./ConvexHull.h"
#include "./Interface.h"

point2_t* wrappingConvexHull(point2_t *points, point2_t *answerPoints) {
    int last = 0;
    while(isValidPoint(points[last]) == TRUE) {
        last++;
    }

    point2_t min = points[0];
    point2_t max = points[0];
    int min_i,max_i;
    int i;
    for(i=0; i<last; i++) {
        if(points[i].y < min.y) {
            min = points[i];
            min_i = i;
        }
        if(points[i].y > max.y) {
            max = points[i];
            max_i = i;
        }
    }

    addPoint(answerPoints, min);

    point2_t p;
    point2_t q;
    int ans_i = 0;
    int pm = 1;
    int mindeg_i, mindeg, deg;
    int j;
    while(1) {
        if(isEqualPoint(answerPoints[ans_i], max) == TRUE) pm = -1;
        p.x = answerPoints[ans_i].x;
        p.y = answerPoints[ans_i].y;
        q.x = p.x + pm;
        q.y = p.y;

        mindeg = INT_MAX;
        for(j=0; j<last; j++) {
            if(isExistInPointsList(answerPoints, points[j]) == TRUE) {
                continue;
            }
            deg = calcDeg(p, q, points[j]);
            if(deg >= 0 && deg < mindeg) {
                mindeg = deg;
                mindeg_i = j;
            }
        }
        if(isEqualPoint(points[mindeg_i], answerPoints[ans_i]) == TRUE) break; 
        addPoint(answerPoints, points[mindeg_i]);
        ans_i++;
    }

    return answerPoints;
}

point2_t* directConvexHull(point2_t *points, point2_t *answerPoints) {
    int i, j, k, flag;
    point2_t *p, *q, *a;
    point2_t ip = {INT_MAX, INT_MAX};
    edge_t answerEdges[N+1] = {{ip, ip}};
    for(i=0; i<N; i++) {
        p = &points[i];
        for(j=0; j<N; j++) {
            q = &points[j];
            flag = TRUE;

            for(k=0; k<N; k++) {
                if(k == i || k == j) continue;
                a = &points[k];
                if(crossProduct(*p, *q, *a) >= 0) {
                    // left side
                    flag = FALSE;
                    break;
                }
            }
            if(flag == TRUE) {
                // all points are right-side
                addEdge(answerEdges, *p, *q);
                break;
            }
        }
    }
    edgeToPoint(answerPoints, answerEdges);
    return answerPoints;
}
