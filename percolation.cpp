#include <stack>
#include <map>
#include "percolation.h"


#define CHARLEN 20

//global variables, gridS = grid size, p = probability
//percT = top to bottom/ left to right/ both, lrgestCluster = largest cluster size
int gridS = 0;
float p = 0.0;
int percT;
int lrgestCluster;
int currentCluster=0;



//Function for exit status
void exitStatus(char *ex){
    if (strcmp("EXIT",ex)==0){
        printf("\nExiting program...");
        exit(EXIT_SUCCESS);
    }
}

//Function for probability input
int occupancy(void){
    char temp[CHARLEN];
    printf ("\nEnter occupancy probability (0 to 1.0):");
    scanf("%s",temp);
    exitStatus(temp);
    for (int i=0;i<strlen(temp);i++){
        if (isdigit(temp[i]) ==0  && temp[i]!='.'){
            return 1;
        }
    }
    p = atof(temp);
    if(p<0.0 || p > 1.0){
        return 1;
    }
    return 0;
}

//Function for grid size input
int gridSize(void){
    char temp[CHARLEN];
    printf("\nEnter grid size:");
    scanf("%s",temp);
    exitStatus(temp);
    for (int i=0;i<strlen(temp);i++){
        if (isdigit(temp[i]) == 0){
            return 1;
        }
    }
    gridS=atoi(temp);
    return 0;
}

//Function for site/bond percolation input
int percStatus(void){
    char perc[CHARLEN];
    printf("\nEnter 's' or 'b' for site or bond percolation:");
    scanf("%s",perc);
    exitStatus(perc);
    if(strcmp(perc,"s")==0){
        return 0;
    } else if (strcmp("b",perc)==0) {
        return 1;
    } else {
        return 2;
    }
}

//Function for percolation type input
int percType(void){
    char temp[CHARLEN];
    printf("\nEnter 0, 1 or 2 for vertical, horizontal or vertical/horizontal percolation:");
    scanf("%s",temp);
    exitStatus(temp);
    for (int i=0;i<strlen(temp);i++){
        if (isdigit(temp[i]) == 0){
            return 1;
        }
    }
    percT=atoi(temp);
    if (percT != 0 && percT != 1 && percT !=2){
        return 1;
    }
    return 0;

}

//Function for thread count input
int trdReturn(void){
    char temp[CHARLEN];
    printf("\nEnter number of desired threads:");
    scanf("%s",temp);
    exitStatus(temp);
    for (int i=0;i<strlen(temp);i++){
        if (isdigit(temp[i]) == 0){
            return 1;
        }
    }
    trdCount=atoi(temp);
    return 0;
}

//Fucntion for creating a wraparound site percolation grid
void joinGridN(Node **grid) {
    for (int i = 0; i < gridS; i++) {
#pragma omp paralell for
        for (int j = 0; j < gridS; j++) {
            Node *gp = &grid[i][j];
            int NSEW[4];
            //Determining the 'j' of north and south component
            if (j == 0) {
                NSEW[0] = gridS - 1;
                NSEW[1] = j + 1;
            } else if (j == gridS - 1) {
                NSEW[0] = j - 1;
                NSEW[1] = 0;
            } else {
                NSEW[0] = j - 1;
                NSEW[1] = j + 1;
            }
            //Determining the 'i' of east and west component
            if (i == 0) {
                NSEW[2] = i + 1;
                NSEW[3] = gridS - 1;
            } else if (i == gridS - 1) {
                NSEW[2] = 0;
                NSEW[3] = i - 1;
            } else {
                NSEW[2] = i + 1;
                NSEW[3] = i - 1;
            }
            //Updating fields in the structure
            gp->setWest(&grid[NSEW[3]][j]);
            gp->setEast(&grid[NSEW[2]][j]);
            gp->setSouth(&grid[i][NSEW[1]]);
            gp->setNorth(&grid[i][NSEW[0]]);
            gp->setNodei(i);
            gp->setNodej(j);
            float occup;
            //Generate random number from 0 to 1 for node occupancy
            occup = rand();
            occup /= (RAND_MAX);
            //Check if node is occupied
            if (occup <= p) {
                gp->setOccu(0);
            } else {
                gp->setOccu(1);
            }
        }
    }
}

//function for creating a wraparound bond percolation grid
void joinGridB(Bond **grid){
    for (int i=0; i < gridS; i++){
#pragma omp paralell for
        for (int j=0; j < gridS; j++){
            Bond *gp = &grid[i][j];
            int NSEW[4];
            //Determining the 'j' of north and south component
            if(j==0){
                NSEW[0]=gridS-1;
                NSEW[1]=j+1;
            }else if(j==gridS-1){
                NSEW[0]=j-1;
                NSEW[1]=0;
            }else{
                NSEW[0]=j-1;
                NSEW[1]=j+1;
            }
            //Determining the 'i' of east and west component
            if(i==0){
                NSEW[2]=i+1;
                NSEW[3]=gridS-1;
            }else if(i==gridS-1){
                NSEW[2]=0;
                NSEW[3]=i-1;
            }else{
                NSEW[2]=i+1;
                NSEW[3]=i-1;
            }
            //Updating fields in the structure
            gp->setWest(&grid[NSEW[3]][j]);
            gp->setEast(&grid[NSEW[2]][j]);
            gp->setSouth(&grid[i][NSEW[1]]);
            gp->setNorth(&grid[i][NSEW[0]]);
            gp->setNodei(i);
            gp->setNodej(j);
            float rOccup;
            float bOccup;
            //Generate random number from 0 to 1 for bond occupancy
            rOccup = rand();
            rOccup /= (RAND_MAX);
            bOccup = rand();
            bOccup /= (RAND_MAX);
            //Check if bonds are occupied
            if (rOccup <= p){
                gp ->setRBond(0) ;
            } else {
                gp ->setRBond(1) ;
            }
            if (bOccup <= p){
                gp ->setBBond(0) ;
            } else {
                gp ->setBBond(1) ;
            }
            }
        }
    }

/*
//function for determining if a grid node is occupied for site percolation 
void sitePerc(Node **grid){
    for (int i=0; i < gridS; i++){
        for (int j=0; j < gridS; j++){
            Node *gp = &grid[i][j];
            float occup;
            //Generate random number from 0 to 1 for node occupancy
            occup = rand();
            occup /= (RAND_MAX);
            //Check if node is occupied
            if (occup <= p){
                gp -> setOccu(0);
            } else {
                gp -> setOccu(1);
            }

        }
    }
}
*/
/*
// fill bonds with occupancy
void bondPerc(Bond **grid){
    for (int i=0; i < gridS; i++){
        for (int j=0; j < gridS; j++){
            Bond *gp = &grid[i][j];
            float rOccup;
            float bOccup;
            //Generate random number from 0 to 1 for bond occupancy
            rOccup = rand();
            rOccup /= (RAND_MAX);
            bOccup = rand();
            bOccup /= (RAND_MAX);
            //Check if bonds are occupied
            if (rOccup <= p){
                gp ->setRBond(0) ;
            } else {
                gp ->setRBond(1) ;
            }
            if (bOccup <= p){
                gp ->setBBond(0) ;
            } else {
                gp ->setBBond(1) ;
            }
        }
    }
}
*/
int siteCheck(Node **grid){
    std::map<Node*,bool> visited;
    int percolates=1;
    for(int i=0;i<gridS;i++){
#pragma omp parallel for firstprivate(visited)\
        lastprivate(visited)
        for(int j=0;j<gridS;j++){
            std::stack<Node*> nodeS;
            Node *gridPoint=&grid[i][j];
            Node *startPoint=&grid[i][j];
            int clusterSize=0;
            //Push site onto stack
            if (gridPoint->getOccu()==0 && visited[gridPoint]!=true){
                nodeS.push(gridPoint);
                visited[gridPoint]=true;
            }else{
                continue;
            }

            //Array for checking if it percolates
            int visitedRows[gridS];
            int visitedCols[gridS];
            //Initialise the array with 1s (not seen)
            for (int p=0;p < gridS; p++){
                visitedRows[p]=1;
                visitedCols[p]=1;
            }
            //Set the current grid row and column to 0 (seen)
            visitedRows[i]=0;
            visitedCols[j]=0;

            while(!nodeS.empty()){
                Node *site;
                site = nodeS.top();
                nodeS.pop();
                visitedRows[site->getNodei()]=0;
                visitedCols[site->getNodej()]=0;

                if(site->getNorth()->getOccu()==0 && visited[site->getNorth()]!=true){
                    nodeS.push(site->getNorth());
                    visited[site->getNorth()]=true;
                } else {
                    visited[site->getNorth()]=true;
                }

                if(site->getSouth()->getOccu()==0 && visited[site->getSouth()]!=true){
                    nodeS.push(site->getSouth());
                    visited[site->getSouth()]=true;
                } else {
                    visited[site->getSouth()]=true;
                }

                if(site->getEast()->getOccu()==0 && visited[site->getEast()]!=true){
                    nodeS.push(site->getEast());
                    visited[site->getEast()]=true;
                } else {
                    visited[site->getEast()]=true;
                }

                if(site->getWest()->getOccu()==0 && visited[site->getWest()]!=true){
                    nodeS.push(site->getWest());
                    visited[site->getWest()]=true;
                } else {
                    visited[site->getWest()]=true;
                }
                //Increase cluster size
                clusterSize+=1;
            }

            int tempPerc= 1;
            //If grid hasn't percolate yet, execute the following
            if (percolates == 1) {
                //If vertical percolation
                if (percT == 0) {
                    //If any element in array is 1, exit loop
                    for (int e = 0; e < gridS; e++) {
                        if (visitedRows[e] == 1) {
                            break;
                        }
                        //Update percolate if reached the final element
                        if (e == gridS - 1) {
                            tempPerc = 0;
                        }
                    }
                    //If horizontal percolation
                } else if (percT == 1) {
                    for (int e = 0; e < gridS; e++) {
                        if (visitedCols[e] == 1) {
                            break;
                        }

                        if (e == gridS - 1) {
                            tempPerc = 0;
                        }
                    }
                    //If vertical/ horizontal percolation
                } else {
                    for (int e = 0; e < gridS; e++) {
                        if ((visitedCols[e] == 1 || visitedRows[e] == 1)) {
                            break;
                        }

                        if (e == gridS - 1) {
                            tempPerc = 0;
                        }
                    }
                }
            }
//#pragma omp critical

                //Update largest cluster, if current cluster is larger
                if (clusterSize > lrgestCluster)lrgestCluster = clusterSize;
                if (tempPerc == 0){
                    percolates = 0;
                }

            //printf ("Fucking Random Potatoes aye\n");
        }
        //printf(visited.empty()?"empty\n":"not empty\n");
    }
    //Return if grid percolates or not
    return percolates;
}


int bondCheck(Bond **grid){
    std::map<Node*,bool> rVisited;
    std::map<Node*,bool> bVisited;
    int  percolates = 1;
    for(int i=0;i<gridS;i++) {
#pragma omp parallel for firstprivate(rVisited,bVisited)\
        lastprivate(rVisited,bVisited)
        for (int j = 0; j < gridS; j++) {
            Bond *gridPoint = &grid[i][j];
            std::stack<Bond*> bondS;

            int visitedRows[gridS];
            int visitedCols[gridS];

            for (int p=0;p < gridS; p++){
                visitedRows[p]=1;
                visitedCols[p]=1;
            }

            visitedRows[i]=0;
            visitedCols[j]=0;

            int clusterSize=0;
            bondS.push(gridPoint);

            while(!bondS.empty()){
                Bond *bond;
                bond = bondS.top();
                bondS.pop();
                visitedRows[bond->getNodei()]=0;
                visitedCols[bond->getNodej()]=0;
                //Check each bond, update check array and push node onto stack
                if(bond->getRBond() == 0 && rVisited[bond]!=true){
                    bondS.push(bond->getEast());
                }
                if(bond->getBBond() == 0 && bVisited[bond]!=true){
                    bondS.push(bond->getSouth());
                }
                if(bond->getWest()->getRBond() == 0 && rVisited[bond->getWest()]!=true) {
                    bondS.push(bond->getWest());
                }
                if(bond->getNorth()->getBBond() == 0 && bVisited[bond->getNorth()]!=true) {
                    bondS.push(bond->getNorth());
                }
                clusterSize +=1;
            }
            {
                int tempPerc = 1;
                if (percolates == 1) {
                    if (percT == 0) {
                        for (int e = 0; e < gridS; e++) {
                            if (visitedRows[e] == 1) {
                                break;
                            }
                            if (e == gridS - 1) {
                                tempPerc = 0;
                            }
                        }
                    } else if (percT == 1) {
                        for (int e = 0; e < gridS; e++) {
                            if (visitedCols[e] == 1) {
                                break;
                            }
                            if (e == gridS - 1) {
                                tempPerc = 0;
                            }
                        }
                    } else {
                        for (int e = 0; e < gridS; e++) {
                            if ((visitedCols[e] == 1 || visitedRows[e] == 1)) {
                                break;
                            }
                            if (e == gridS - 1) {
                                tempPerc = 0;
                            }
                        }
                    }
                }

                if (clusterSize > lrgestCluster)lrgestCluster = clusterSize;
                if (tempPerc == 0){
                    percolates = 0;
                }
            }
        }
    }
    return percolates;
}