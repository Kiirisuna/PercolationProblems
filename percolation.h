//
// Created by lachi on 5/10/2017.
//

#ifndef CITS3200_PERCOLATION_H
#define CITS3200_PERCOLATION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <omp.h>
#include <math.h>
#include "NodeBond.h"
//#include <mpi.h>



extern int gridS;
extern float p;
extern int percT;
extern int lrgestCluster;
extern int trdCount;
#endif //CITS3200_PERCOLATION_H

void exitStatus(char *ex);
int occupancy(void);
int gridSize(void);
int percStatus(void);
int percType(void);
int trdReturn(void);
void joinGridN(Node **grid);
void joinGridB(Bond **grid);
void sitePerc(Node **grid);
void bondPerc(Bond **grid);
int siteCheck(Node **grid);
int bondCheck(Bond **grid);
