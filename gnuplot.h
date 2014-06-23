#ifndef GNUPLOT_H
#define GNUPLOT_H

#include "./Interface.h"

extern int outputToGnuplot(point2_t*, point2_t*, char*);
extern int makeGnuPlotFile(FILE*, point2_t*);
#endif
