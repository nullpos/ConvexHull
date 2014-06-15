#define SIZE_V(v) ((sizeof(v))/(sizeof(v[0])))

typedef struct {
    int x;
    int y;
} vector2_t;

vector2_t* directConvexHull(vector2_t* /* point list */, vector2_t* /* answer */);

int show(vector2_t *vectors) {
    int size = (sizeof(vectors)) / (sizeof(vectors[0]));
    printf("%d / %d = %d or %d\n", (int)(sizeof vectors), (int)(sizeof vectors[0]), size, (int)SIZE_V(vectors));


    int i;
    for(i=0; i<10; i++) {
        printf("(%d, %d) ", vectors[i].x, vectors[i].y);
    }
    return 0;
}
