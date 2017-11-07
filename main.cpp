#include <iostream>
#include <stdio.h>
#include<sys/time.h>




#include"percolation.h"

int trdCount;
int *startI;
int *finishI;
int myRank;

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int numProcesses;
    MPI_Comm_size(MPI_COMM_WORLD,&numProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
    printf("I am %i of %i processors \n",myRank,numProcesses);
    int i,sum;
    struct timeval start, end;

    if(myRank==0){
        gettimeofday(&start, NULL);
    }

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
    printf("here,after valiation %i\n",myRank);
    //Set number of threads that will be executed
    omp_set_num_threads(trdCount);

    startI=(int*)malloc(numProcesses*sizeof(int));
    finishI=(int*)malloc(numProcesses*sizeof(int));
    startI[myRank]=myRank*gridS/numProcesses;
    if (myRank==numProcesses-1){
        finishI[myRank]=gridS-1;
    }
    else {
        finishI[myRank]=((myRank+1)*gridS/numProcesses)-1;
    }

    if (validp==0){

        //Allocate memory for stack
        //Initialise grid of NODE and allocating memory
        Node **grid;
        grid = (Node **) malloc(sizeof(Node *) * gridS);
        for (int i=0; i < gridS; i++){
            grid[i]= (Node *) malloc(sizeof(Node) * gridS);
        }
        
        if(myRank==0) {
            //Initialise grid of NODE and allocating memory
            joinGridNM(grid);
            int occuArray[gridS*gridS];
            for(int k=0;k<gridS;k++){
                for(int l=0;l<gridS;l++){
                    occuArray[k*gridS+l]=grid[k][l].getOccu();
                }

            }
            for(int proc=1;proc<numProcesses;proc++){
                printf("Master Attempting to send to %i\t",proc);
                MPI_Send(&occuArray,gridS*gridS,MPI_INT,p,0,MPI_COMM_WORLD);
                printf("complete send \n");
            }
        }

        if(myRank!=0){
            printf("i am %i ready to recieve\n",myRank);
            int occuArray[gridS*gridS];
            MPI_Recv(&occuArray,gridS*gridS,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf("I am %i and  have recieved my occuArray\n",myRank);
            joinGridNS(grid,occuArray);
        }
        MPI_Barrier(MPI_COMM_WORLD);



        //Seeding occupancy probability for nodes in the grid
        //sitePerc(grid);
        //Run percolation code for site percolation
        int ans = siteCheck(grid);
        if(myRank!=0){
            printf("I am %i preparing to send results",myRank);
            MPI_Send(&ans,1,MPI_INT,0,0,MPI_COMM_WORLD);
            MPI_Send(&lrgestCluster,1,MPI_INT,0,1,MPI_COMM_WORLD);
            printf("I am %i and  have sent my results",myRank);

        }
        else{
            int answers[numProcesses];
            int lrgstClusters[numProcesses];
            answers[0]=ans;
            lrgstClusters[0]=lrgestCluster;
            for(int p=1;p<numProcesses;p++){
                printf("Master attempting to recieve results from %i",p);
                MPI_Recv(&answers[p],1,MPI_INT,p,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                MPI_Recv(&lrgstClusters[p],1,MPI_INT,p,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                printf("I am master and  have recieved my results");

            }
            for(int q=0;q<numProcesses;q++){
                if(lrgstClusters[q]>lrgestCluster){
                    lrgestCluster=lrgstClusters[q];
                }
                if(ans==1&&answers[q]!=1){
                    ans=0;
                }
            }
        }
        if(myRank==0){
            if (ans==0){
                printf("\n The grid percolates with largest cluster %i\n",lrgestCluster);
            } else {
                printf("\n The grid does not percolate and has a largest cluster of %i\n",lrgestCluster);
            }
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
    MPI_Finalize();
    if(myRank==0){
    gettimeofday(&end, NULL);
    float delta = ((end.tv_sec  - start.tv_sec) * 1000000u +
             end.tv_usec - start.tv_usec) / 1.e6;
    printf("time= %12.10f\n",delta);
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