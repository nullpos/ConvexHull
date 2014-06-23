#include "./gnuplot.h"

int outputToGnuplot(point2_t *points, point2_t *answer, char* fileName) {
    FILE *opp, *oep, *gp;
    char ptitle[256] = "points.dat";
    char etitle[256] = "points.dat.ans";

    if(fileName != NULL) {
        sprintf(ptitle, "%s", fileName);
        sprintf(etitle, "%s.ans", fileName);
    }

    gp = popen("gnuplot -persist", "w");

    opp = fopen(ptitle, "w");
    oep = fopen(etitle, "w");

    makeGnuPlotFile(opp, points);
    makeGnuPlotFile(oep, answer);

    fprintf(gp, "unset key\n");
    fprintf(gp, "plot \"%s\" w p ps 1 pt 7, \"%s\" w l\n", ptitle, etitle);

    pclose(gp);
    fclose(opp);
    fclose(oep);
    return 0;
}

int makeGnuPlotFile(FILE *fp, point2_t *points) {
    int i = 0;
    while(isValidPoint(*(points + i)) == TRUE) {
        fprintf(fp, "%d\t%d\n", (points + i)->x, (points + i)->y);
        i++;
    }
    fprintf(fp, "%d\t%d\n", points->x, points->y);

    fflush(fp);
    return 0;
}
