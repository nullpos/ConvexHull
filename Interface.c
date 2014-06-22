#include "./Interface.h"

int show(point2_t *points) {
    int i = 0;
    while((points + i)->x != INT_MAX && (points + i)->y != INT_MAX) {
        i++;
    }
    int j;
    for(j=0; j<i; j++) {
        printf("(%d, %d)", (points + j)->x, (points + j)->y);
        if((j+1) % 10 == 0) { printf("\n"); }
    }
    printf("\n");
    return 0;
}

long long int crossProduct(point2_t p, point2_t q, point2_t a) {
    long long int product = ((q.x-p.x) * (a.y-p.y) - (q.y-p.y) * (a.x-p.x));
    return product;
}

int whichSideOfVector(point2_t p, point2_t q, point2_t a) {
    long long int cp = crossProduct(p, q, a);
    int flag;
    if(cp < 0) {
        flag = RIGHT;
    } else if(cp > 0) {
        flag = LEFT;
    } else {
        flag = ON;
    }
    return flag;
}

double calcDeg(point2_t p, point2_t q, point2_t a) {
    point2_t pq = {q.x - p.x, q.y - p.y};
    point2_t pa = {a.x - p.x, a.y - p.y};

    double qpv = atan2((double) pq.y, (double) pq.x);
    point2_t pa_ = rotatePoint(pa, (-1 *qpv));
    double apq = atan2((double) pa_.y, (double) pa_.x);

    return apq;
}

point2_t rotatePoint(point2_t p, double deg) {
    point2_t q;

    q.x = p.x * cos(deg) - p.y * sin(deg);
    q.y = p.x * sin(deg) + p.y * cos(deg);

    return q;
}

int isExistInPointsList(point2_t *points, point2_t point) {
    int flag = FALSE;
    int last = 0;
    while(isValidPoint(*(points + last)) == TRUE) {
        last++;
    }

    int i;
    for(i=0; i<last; i++) {
        if(isEqualPoint(*(points + i), point) == TRUE) {
            flag = TRUE;
            break;
        }
    }

    return flag;
}

int edgeToPoint(point2_t *points, edge_t *edges) {
    point2_t start, source, target;
    int i = 0, j;
    int last;

    start = edges->p;
    source = edges->p;
    target = edges->q;

    last = 0;
    while(isValidEdge(*(edges + last)) == TRUE) {
        last++;
    }
    addPoint(points, target);
    do {
        for(j=0; j<last; j++) {
            source = (edges + j)->p;
            if(isEqualPoint(source, target) == TRUE) {
                target = (edges + j)->q;
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
    while(isValidPoint(*(points + i)) == TRUE) {
        i++;
    }
    *(points + i) = point;
    *(points + i+1) = IP;
    return 0;
}

int addEdge(edge_t *edges, point2_t p, point2_t q) {
    int i = 0;
    while(isValidEdge(*(edges + i)) == TRUE) {
        i++;
    }
    (edges + i)->p = p;
    (edges + i)->q = q;

    (edges + i+1)->p = IP;
    (edges + i+1)->q = IP;
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
