//
// Created by lachi on 3/11/2017.
//
#include "percolation.h"
Node::Node(Node *north, Node *south, Node *east, Node *west, int occu, int nodei, int nodej) {
    this->north=north;
    this->south=south;
    this->east=east;
    this->west=west;
    this->occu=occu;
    this->nodei=nodei;
    this->nodej=nodej; }

Node* Node::getNorth() {
    return north;
}

void Node::setNorth(Node *north) {
    this->north = north;
}

Node* Node::getSouth() {
    return Node::south;
}

void Node::setSouth(Node *south) {
    this->south = south;
}

Node* Node::getEast() {
    return east;
}

void Node::setEast(Node *east) {
    this->east = east;
}

Node* Node::getWest()  {
    return west;
}

void Node::setWest(Node *west) {
    this->west = west;
}

Node* Node::getParent()  {
    return parent;
}

void Node::setParent(Node *parent) {
    this->parent = parent;
}

int Node::getOccu()  {
    return occu;
}

void Node::setOccu(int occu) {
    this->occu = occu;
}

int Node::getNodei()  {
    return nodei;
}

void Node::setNodei(int nodei) {
    this->nodei = nodei;
}

int Node::getNodej()  {
    return nodej;
}

void Node::setNodej(int nodej) {
    this->nodej = nodej;
}

Bond::Bond(Bond *north, Bond *south,Bond *west, Bond *east, int rbond,int bbond,int nodei,int nodej) {
    this->north=north;
    this->south=south;
    this->east=east;
    this->west=west;
    this->rBond=rbond;
    this->bBond=bbond;
    this->nodei=nodei;
    this->nodej=nodej;
}
Bond* Bond::getNorth(){
    return north;
}
void Bond::setNorth(Bond *north){
 this->north=north;
}
Bond* Bond::getSouth(){
    return south;

}
void Bond::setSouth(Bond *south){
    this->south=south;
}

Bond* Bond::getEast(){
    return east;
}

void Bond::setEast(Bond *east){
 this->east=east;
}
Bond* Bond::getWest(){
    return west;
}
void Bond::setWest(Bond *west){
    this->west=west;
}

Bond *Bond::getParent()  {
    return parent;
}

void Bond::setParent(Bond *parent) {
    Bond::parent = parent;
}

int Bond::getRBond()  {
    return rBond;
}

void Bond::setRBond(int rBond) {
    Bond::rBond = rBond;
}

int Bond::getBBond()  {
    return bBond;
}

void Bond::setBBond(int bBond) {
    Bond::bBond = bBond;
}

int Bond::getNodei()  {
    return nodei;
}

void Bond::setNodei(int nodei) {
    Bond::nodei = nodei;
}

int Bond::getNodej()  {
    return nodej;
}

void Bond::setNodej(int nodej) {
    Bond::nodej = nodej;
}

