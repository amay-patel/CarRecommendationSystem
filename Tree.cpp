//
// Created by Rohan Chander on 8/1/22.
//

#include "Tree.h"

Tree::Tree(int maxNumChildren, int blockSize) {
    this->maxNumChildren = maxNumChildren;
    this->blockSize = blockSize;
    this->root = nullptr;
    this->size = 0;
}

void Tree::BlockInsertion(vector<Car*>& block, Car* car) {
    for (auto iter = block.begin(); iter < block.end(); iter++) {
        if ((*iter)->getModel() > car->getModel()) {
            block.insert(iter, car);
            break;
        }
        if(iter+1 == block.end()){
            block.insert(iter+1, car);
            break;
        }
    }
    /*int index;
    for(int i = 0; i< block.size(); i++){
        if(car.getModel() < block[i].getModel()){
            index = i;
            break;
        }
        if(i == block.size()-1){
            index = i;
        }
    }
    Car endCar = block[block.size()-1];
    for(int i = block.size()-1; i>= index; i--){
        block[i] = block[i-1];
    }
    block[index] = car;
    block.push_back(endCar);*/
}

void Tree::ChildBlockInsertion(Node *parent, Node *child, Car* car) {
    int childBlockIndex = 0;
    int parentBlockIndex = 0;
    for(int i = 0; i < parent->size; i++){
        if(car->getModel() < parent->block[i]->getModel()){
            childBlockIndex = i+1;
            parentBlockIndex = i;
            break;
        }
        if(i == parent->size-1){
            childBlockIndex = parent->size+1;
            parentBlockIndex = parent->size;
            break;
        }
        Car* temp = parent->block[parent->size-1];
        for(int i = parent->size; i> parentBlockIndex; i--){
            parent->block[i] = parent->block[i-1];
        }
        Node* temp2 = parent->children[parent->children.size()-1];
        for(int i = parent->size+1; i> childBlockIndex; i--){
            parent->children[i] = parent->children[i-1];
        }
        parent->block[parentBlockIndex] = car;
        parent->block.push_back(temp);
        parent->children[childBlockIndex] = child;
        parent->children.push_back(temp2);

    }
}

void Tree::ParentalInsert(Node *parent, Node *child, Car* car) {
    if(parent->size < maxNumChildren-1){
        ChildBlockInsertion(parent, child, car);
        parent->size++;
    }
    else{
        Node* anotherNode;
        anotherNode->parent = parent->parent;

        vector<Car*> parentBlockCopy;
        for(int i = 0; i< parent->block.size(); i++){
            parentBlockCopy[i] = parent->block[i];
        }
        BlockInsertion(parentBlockCopy, car);

        vector<Node*> childrenOfParentCopy;
        for(int i = 0; i< parent->size+1; i++){
            childrenOfParentCopy[i] = parent->children[i];
        }

        childrenOfParentCopy[parent->size+1] = nullptr;
        //Maybe can use blockInsertion instead//
        int replacementIndex = 0;
        for(int i = 0; i< parent->size; i++){
            if(car->getModel() < parentBlockCopy[i]->getModel()){
                replacementIndex = i;
                break;
            }
            if(i == parent->size-1){
                replacementIndex = parent->size-1;
                break;
            }
        }
        int indexCheck = 0;
        for(auto iter = childrenOfParentCopy.begin(); iter< childrenOfParentCopy.end(); iter++){
            if(indexCheck==replacementIndex){
                childrenOfParentCopy.insert(iter, child);
                break;
            }
            indexCheck++;
        }
        //Splitting of parent node into 2//
        parent->size = maxNumChildren/2;
        if(maxNumChildren % 2 == 0){
            anotherNode->size = maxNumChildren/2-1;
        }
        else{
            anotherNode->size = maxNumChildren/2;
        }

        //Copying data over from ParentBlockCopy back into anotherNode and Parent node//
        for(int i = 0; i< parent->size; i++){
            parent->block[i] = parentBlockCopy[i];
            parent->children[i] = childrenOfParentCopy[i];
        }
        //No idea why but okay//
        parent->children[parent->size] = childrenOfParentCopy[parent->size];

        for(int i = 0; i< anotherNode->size; i++){
            anotherNode->block[i] = parentBlockCopy[parent->size+i+1];
            anotherNode->children[i] = childrenOfParentCopy[i+1+ parent->size];
            anotherNode->children[i]->parent = anotherNode;
        }
        anotherNode->children[anotherNode->size] = childrenOfParentCopy[anotherNode->size+parent->size+1];
        anotherNode->children[anotherNode->size]->parent = anotherNode;

        //Handles pushing up to parent//

        //In case is root//
        Car* c = anotherNode->block[0];
        if(parent->parent == nullptr){
            Node* newRoot;
            parent->parent = newRoot;
            anotherNode->parent = newRoot;
            newRoot->block[0] = c;
            newRoot->size++;
            newRoot->children[0] = parent;
            newRoot->children[1] = anotherNode;
            this->root = newRoot;
        }
        else{
            ParentalInsert(parent->parent, anotherNode, c);
        }
    }
}

void Tree::Insert(Car* car) {
    if(this->root == nullptr){
        this->root = new Node(car);
        this->size++;
        this->root->leaf = true;
        this->root->size++;
    }
    else{
        Node* search = root;
        //Searches inside tree for appropriate place to put, traverses down to leaves//
        while(!search->leaf){
            for(int i = 0; i < search->size; i++){
                //Passes the search onto the according children block
                if(car->getModel() < search->block[i]->getModel()){
                    search = search->children[i];
                    break;
                }
                if(i == search->size){
                    //Makes sure moves onto final children block//
                    search = search->children[i+1];
                }
            }
        }
        if(search->size < this->maxNumChildren-1){
            BlockInsertion(search->block, car);
            search->size++;
            //                //edit pointer(next node)
            //                cursor->children[cursor->size] = cursor->children[cursor->size-1];
            //                cursor->children[cursor->size-1] = nullptr;

        }
        else{
            //Copying//
            Node* splitNode;
            splitNode->size = 0;
            splitNode->leaf = true;
            splitNode->parent = search->parent;

            vector<Car*> copyBlock;
            for(int i = 0; i< search->size; i++){
                copyBlock[i] = search->block[i];
            }
            //Inserting into copy//
            BlockInsertion(copyBlock, car);

            //Resizing//
            search->size = this->maxNumChildren/2;
            if(this->maxNumChildren % 2 == 0){
                splitNode->size = this->maxNumChildren;
            }
            else{
                splitNode->size = this->maxNumChildren + 1;
            }
            //CHECK IF OTHER CARS IN BLOCK R DELETED
            for(int i = 0; i< search->size; i++){
                search->block[i] = copyBlock[i];
            }
            for(int i = 0; i< splitNode->size; i++){
                splitNode->block[i] = copyBlock[search->size+i];
            }
            //WHAT DOES THIS EVEN DO//
            search->children[search->block.size()] = splitNode;
            splitNode->children[splitNode->block.size()] = search->children[this->maxNumChildren-1];
            search->children[this->maxNumChildren-1] = nullptr;

            //Something with parent//
            Car* c = splitNode->block[0];
            //Root case
            if(search->parent == nullptr){
                Node* rootBlock = new Node(c);
                search->parent = rootBlock;
                splitNode->parent = rootBlock;
                rootBlock->children[0] = search;
                rootBlock->children[1] = splitNode;
                this->root = rootBlock;
            }
            else{
            }
        }
    }
}