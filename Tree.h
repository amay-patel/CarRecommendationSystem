//
// Created by Rohan Chander on 8/1/22.
//

#ifndef TREE_CAR_REC_SERVICE_TREE_H
#define TREE_CAR_REC_SERVICE_TREE_H
#include <iostream>
#include "Car.h"
#include <vector>

class Tree{
private:
    struct Node{
        bool leaf;
        vector<Car*> block;
        vector<Node*> children;
        int size;
        Node* parent;
        Node (Car* car){
            this->leaf = false;
            this->size = 0;
            this->block = {car};
            this->children = {};
            this->parent = nullptr;
        }
        Node(){
            this->leaf = false;
            this->size = 0;
            this->block = {};
            this->children = {};
            this->parent = nullptr;
        }
    };
    int maxNumChildren;
    //int height;
    Node* root;
    int blockSize;
    int size;
    //this vector acts as the bottom linked list
    vector<Car*> leafNodes;


public:
    // B+ Tree constructor
    Tree(int maxNumChildren, int blockSize);
    // Insert car in block vector in ascending location
    void BlockInsertion(vector<Car*>& block,Car* car);
    // Insert car in
    void ChildBlockInsertion(Node* parent, Node* child, Car* car);
    // Insert car in
    void ParentalInsert(Node* parent, Node* child, Car* car);
    // Insert car into Tree
    void Insert(Car* car);
    //Searches through tree
    vector<Car*> Search(Node* root, int lowerYear, int upperYeat);
    //inserts into leaf node vector
    void leafNodeInsertion(Car* toBeInserted, int indexFirstCarInNode, int indexLastCarInNode);

    Node *getRoot() const;

};

#endif //TREE_CAR_REC_SERVICE_TREE_H