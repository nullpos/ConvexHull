#include "./Interface.h"

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

int crossProduct(point2_t p, point2_t q, point2_t a) {
    int flag = LEFT;

    int product = ((q.x-p.x) * (a.y-p.y)) - ((q.y-p.y) * (a.x-p.x));

    if(product < 0) {
        // rightside
        flag = RIGHT;
    } else {
        // leftside or on
        flag = LEFT;
    }

    return flag;
}

int edgeToPoint(point2_t *points, edge_t *edges) {
    point2_t start, source, target;
    int i = 0, j;
    int last;

    start = edges[0].p;
    source = edges[0].p;
    target = edges[0].q;
    
    last = 0;
    while(isValidEdge(edges[last]) == TRUE) {
        last++;
    }
    addPoint(points, target);
    do {
        for(j=0; j<last; j++) {
            source = edges[j].p;
            if(isEqualPoint(source, target) == TRUE) {
                target = edges[j].q;
                break;
            }
        }
        addPoint(points, target);        
    } while(isEqualPoint(target, start) == FALSE); 

    return 0;
}

int isEqualPoint(point2_t p, point2_t q) {
    int flag = FALSE;
    if((p.x == q.x) && (p.y == q.y)) {
        flag = TRUE;
    }
    return flag;
}

int addPoint(point2_t *points, point2_t point) {
    int i = 0;
    while(isValidPoint(points[i]) == TRUE) {
        i++;
    }
    points[i] = point;
    points[i+1].x = INT_MAX;
    points[i+1].y = INT_MAX;
    return 0;
}

int addEdge(edge_t *edges, point2_t p, point2_t q) {
    int i = 0;
    while(isValidEdge(edges[i]) == TRUE) {
        i++;
    }
    edges[i].p = p;
    edges[i].q = q;

    point2_t ip = {INT_MAX, INT_MAX};
    edges[i+1].p = ip;
    edges[i+1].q = ip;
    return 0;
}

int isValidPoint(point2_t point) {
    int flag = TRUE;
    if((point.x == INT_MAX) && (point.y == INT_MAX)) {
        flag = FALSE;
    }
    return flag;
}

int isValidEdge(edge_t edge) {
    int flag = TRUE;
    if((edge.p.x == INT_MAX) && (edge.p.y == INT_MAX) && (edge.q.x == INT_MAX) && (edge.q.y == INT_MAX)) {
        flag = FALSE;
    }
    return flag;
}
