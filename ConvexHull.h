#define SIZE_V(v) ((sizeof(v))/(sizeof(v[0])))

typedef struct {
    int x;
    int y;
} vector2_t;

vector2_t* directConvexHull(vector2_t* /* point list */, vector2_t* /* answer */);

int show(vector2_t *vectors) {
    int i = 0;
    while(vectors[i].x != INT_MAX && vectors[i].y != INT_MAX) {
        i++;
    }
    int j;
    for(j=0; j<i; j++) {
        printf("(%d, %d)", vectors[j].x, vectors[j].y);
        if((j+1) % 10 == 0) { printf("\n"); }
    }
    printf("\n");
    return 0;
}
