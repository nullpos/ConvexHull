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
    point2_t ip = {INT_MAX, INT_MAX};
    edge_t answerEdge[N+1] = {{ip, ip}};
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
            addEdge(p, q, answerEdge);
        }
    }
    sortEdges(answerEdge);
    edgeToPoint(answer, answerEdge);
    return answer;
}

int sortEdges(edge_t *edges) {
    return 0;
}

int edgeToPoint(point2_t *points, edge_t *edges) {
    return 0;
}

int addEdge(point2_t *p, point2_t *q, edge_t *answer) {
    int i = 0;
    while(isValidEdge(answer[i]) == TRUE) {
        i++;
    }
    answer[i].p = *p;
    answer[i].q = *q;

    point2_t ip = {INT_MAX, INT_MAX};
    answer[i+1].p = ip;
    answer[i+1].q = ip;
    return 0;
}

int isValidEdge(edge_t edge) {
    int flag = TRUE;
    if((edge.p.x == INT_MAX) && (edge.p.y == INT_MAX) && (edge.q.x == INT_MAX) && (edge.q.y == INT_MAX)) {
        flag = FALSE;
    }
    return flag;
}
