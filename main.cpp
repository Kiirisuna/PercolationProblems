#include <iostream>
#include <stdio.h>




#include"percolation.h"

int trdCount;

int main(int argc, char *argv[])
{

    //Number of arguments checkers
    if(argc>6){
        printf("Too many arguments supplied! (Exiting)");
        exit(EXIT_SUCCESS);
    }

    if(argc<6){
        printf("too few arguments, treating you like a base level plebian");
        exit(EXIT_SUCCESS);
    }

    //Local variable for validity of input
    int valido=0;
    int validg=0;
    int validp;
    int validt=0;
    int validq=0;
    //Random seeding of numbers
    srand(time(NULL));

    //Check the validity of site or bond percolation argument
    if(strcmp("s",argv[1])==0){
        validp=0;

    } else if (strcmp("b",argv[1])==0){
        validp=1;
    } else {
        validp=2;
    }

    //check the validity of probability argument
    for (int i=0;i<strlen(argv[2]);i++){
        if (isdigit(argv[2][i]) == 0 && argv[2][i]!='.'){
            valido=1;
        }
    }

    if (valido==0) {
        p = atof(argv[2]);
        if (p < 0.0 || p > 1.0) {
            valido = 1;
        } else {
            valido = 0;
        }
    }

    //Check Validity of grid argument
    for(int i=0; i < strlen(argv[3]);i++) {
        if (isdigit(argv[3][i]) == 0) {
            validg = 1;
        }
    }

    if (validg == 0){
        gridS=atoi(argv[3]);
    }

    // Check validity of type argument
    for (int i=0;i<strlen(argv[4]);i++) {
        if (isdigit(argv[4][i]) == 0) {
            validt = 1;
        }
    }

    if (validt == 0){
        percT=atoi(argv[4]);
    }

    //Check the validity of thread number argument
    for (int i=0; i < strlen(argv[5]);i++) {
        if (isdigit(argv[5][i])==0){
            validq = 1;
        }
    }

    if (validq == 0){
        trdCount = atoi(argv[5]);
    }

    //Request user input if any command line arguments are incorrect
    while (validp==2) {
        printf ("\nInput was incorrect,try again, or insert 'EXIT' to exit");
        validp = percStatus();
    }

    while (valido==1){
        printf("\nInput was incorrect,try again, or insert 'EXIT' to exit");
        valido = occupancy();
    }


    while (validg==1){
        printf("\nInput was incorrect,try again, or insert 'EXIT' to exit");
        validg = gridSize();
    }

    while (validt==1){
        printf ("\nInput was incorrect,try again, or insert 'EXIT' to exit");
        validt = percType();
    }

    while (validq==1){
        printf ("\nInput was incorrect,try again, or insert 'EXIT' to exit");
        validq = trdReturn();
    }

    //Set number of threads that will be executed
    omp_set_num_threads(trdCount);



    if (validp==0){
        //Allocate memory for stack
        //Initialise grid of NODE and allocating memory
        Node **grid;
        grid = (Node **) malloc(sizeof(Node *) * gridS);
        for (int i=0; i < gridS; i++){
            grid[i]= (Node *) malloc(sizeof(Node) * gridS);
        }

        //Initialise grid of NODE and allocating memory
        joinGridN(grid);
        //Seeding occupancy probability for nodes in the grid
        //sitePerc(grid);
        //Run percolation code for site percolation
        int ans = siteCheck(grid);

        if (ans==0){
            printf("\n The grid percolates with largest cluster %i\n",lrgestCluster);
        } else {
            printf("\n The grid does not percolate and has a largest cluster of %i\n",lrgestCluster);
        }
    } else {
        Bond **grid;
        grid = (Bond **) malloc(sizeof(Bond *) * gridS);
        for (int i=0; i < gridS; i++){
            grid[i]= (Bond *) malloc(sizeof(Bond) * gridS);
        }

        joinGridB(grid);
        //bondPerc(grid);
        int ans = bondCheck(grid);

        if (ans==0){
            printf("\n The grid percolates with largest cluster %i\n",lrgestCluster);
        } else {
            printf("\n The grid does not percolate and has a largest cluster of %i\n",lrgestCluster);
        }
    }


    exit (EXIT_SUCCESS);
}


//    int trdCount = gridS/500;
//    if (trdCount <= 0){
//        trdCount = 1;
//    }
//    //split grid into trdCount^2 number of squares and give each thread a square
//    int gridSquares = trdCount^2;
//    int splitS = 0;
//    int moduloS = 0;
//    if (GridS % trdCount != 0){
//        splitS = gridS/trdCount;
//        moduloS = gridS%trdCount;
//    } else {
//        splitS = gridS/trdCount;
//    }