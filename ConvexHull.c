#include "./ConvexHull.h"

int show(point2_t *points) {
    int i = 0;
    while(points[i].x != INT_MAX && points[i].y != INT_MAX) {
        i++;
    }
    int j;
    for(j=0; j<i; j++) {
        printf("(%d, %d)", points[j].x, points[j].y);
        if((j+1) % 10 == 0) { printf("\n"); }
    }
    printf("\n");
    return 0;
}

int crossProduct(point2_t *p, point2_t *q, point2_t *a) {
    int flag = FALSE;

    int pqx = (q->x - p->x);
    int pqy = (q->y - p->y);
    int pax = (a->x - p->x);
    int pay = (a->y - p->y);

    int product = (pqx - pay) * (pqy - pax);

    if(product > 0) {
        // leftside
        flag = TRUE;
    } else {
        // rightside or on
        flag = FALSE;
    }

    return flag;
}

point2_t* directConvexHull(point2_t *points, point2_t *answer) {
    int i, j, k, flag;
    point2_t *p, *q, *a;
    //edge_t tmpAnswer[N];
    for(i=0; i<N; i++) {
        p = &points[i];
        for(j=0; j<N; j++) {
            q = &points[j];
            flag = TRUE;
            
            for(k=0; k<N; k++) {
                if(k == i || k == j) continue;
                a = &points[k];
                if(crossProduct(p, q, a) == TRUE) {
                    flag = FALSE;
                    break;
                }
            }
        }
        if(flag == TRUE) {
        //    addEdge(p, q, tmpAnswer);
        }
    }
    return answer;
}

int addEdge() {

}
