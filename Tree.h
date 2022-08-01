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
        vector<Car> block;
        vector<Node> children;
        int degree;
        int size;
        Node parent;
        Node(Car car){
            this->leaf = false;
            this->size = 0;
            this->block = {};
            block.push_back(car);
            degree = maxNumChildren;
            this->children = {};
            this->parent = nullptr;
        }
    };
    static int maxNumChildren;
    //int height;
    Node* root;
    int blockSize;
    int size;

public:
    Tree(int maxNumChildren, int blockSize);
    void Insert(Car car);
    void BlockInsertion(vector<Car>& block,Car car);
    void ParentalInsert(Node* parent, Node* child, Car car);
    void ChildBlockInsertion(Node* parent, Node* child, Car car);

};


#endif //TREE_CAR_REC_SERVICE_TREE_H