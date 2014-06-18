#include "./ConvexHull.h"
#include "./Interface.h"

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
                if(crossProduct(*p, *q, *a) == LEFT) {
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
