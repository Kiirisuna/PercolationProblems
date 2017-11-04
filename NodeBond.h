//
// Created by lachi on 3/11/2017.
//

#ifndef PERCOLATIONPROBLEMS_NODEBOND_H
#define PERCOLATIONPROBLEMS_NODEBOND_H

#endif //PERCOLATIONPROBLEMS_NODEBOND_H
class Node{
public:
    Node(Node *north, Node *south, Node *east, Node *west, int occu, int nodei, int nodej);

    Node* getNorth();
    void setNorth(Node *north);
    Node* getSouth();
    void setSouth(Node *south);

    Node* getEast();
    void setEast(Node *east);
    Node* getWest();
    void setWest( Node *west);
    Node* getParent();
    void setParent(Node *parent);

    int getOccu();
    void setOccu(int occu);
    int getNodei() ;
    void setNodei(int nodei);
    int getNodej() ;
    void setNodej(int nodej);

private:
    Node  *north;
    Node  *south;
    Node  *east;
    Node  *west;
    Node  *parent;
    //int clusterNum;
    int occu;
    int nodei;
    int nodej;
};
class Bond{
private:
    Bond  *north;
    Bond  *south;
    Bond  *east;
    Bond  *west;
    Bond  *parent;
    //int clusterNum;
    int rBond;
    int bBond;
    int nodei;
    int nodej;
public:
    Bond(Bond *north,Bond *south,Bond *east,Bond *west,int rbond,int bbond,int nodei,int nodej);
    Bond* getNorth();
    void setNorth(Bond *north);
    Bond* getSouth();
    void setSouth(Bond *south);


    Bond* getEast();
    void setEast(Bond *east);
    Bond* getWest();
    void setWest(Bond *west);

    Bond *getParent() ;

    void setParent(Bond *parent);

    int getRBond() ;

    void setRBond(int rBond);

    int getBBond() ;

    void setBBond(int bBond);

    int getNodei() ;

    void setNodei(int nodei);

    int getNodej() ;

    void setNodej(int nodej);
};