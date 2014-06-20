#include "./Interface.h"
#include "./gnuplot.h"

int outputToGnuplot(point2_t *points, point2_t *answer) {
    FILE *opp, *oep, *gp;
    char *ptitle = "points.dat";
    char *etitle = "edges.dat";

    gp = popen("gnuplot -persist", "w");
    opp = fopen(ptitle, "w");
    oep = fopen(etitle, "w");

    
    makeGnuPlotFile(opp, points);
    makeGnuPlotFile(oep, answer);
    
    fprintf(gp, "plot \"%s\" w d, \"%s\" w l", ptitle, etitle);
    
    pclose(gp);
    fclose(opp);
    fclose(oep);

    return 0;
}

int makeGnuPlotFile(FILE *fp, point2_t *points) {
    int last = 0;
    while(isValidPoint(points[last]) == TRUE) {
        last++;
    }
    int i;
    for(i=0; i<last; i++) {
        fprintf(fp, "%d\t%d\n", points[i].x, points[i].y);
    }
    fprintf(fp, "%d\t%d\n", points[0].x, points[0].y);

    return 0;
}
