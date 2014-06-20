
all: ConvexHull.exe

ConvexHull.exe: main.o Interface.o ConvexHull.o gnuplot.o
	gcc -o ConvexHull.exe main.o Interface.o ConvexHull.o gnuplot.o -lm

main.o: main.c Interface.h ConvexHull.h gnuplot.h
	gcc -c main.c

Interface.o: Interface.c
	gcc -c Interface.c

ConvexHull.o: ConvexHull.c Interface.h
	gcc -c ConvexHull.c

gnuplot.o: gnuplot.c
	gcc -c gnuplot.c
