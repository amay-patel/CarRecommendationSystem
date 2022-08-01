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
}

void Tree::ChildBlockInsertion(Node *parent, Node *child, Car* car) {
//    int childBlockIndex = 0;
//    int parentBlockIndex = 0;
//    for(int i = 0; i < parent->size; i++){
//        if(car->getModel() < parent->block[i]->getModel()){
//            childBlockIndex = i+1;
//            parentBlockIndex = i;
//            break;
//        }
//        if(i == parent->size-1){
//            childBlockIndex = parent->size+1;
//            parentBlockIndex = parent->size;
//            break;
//        }
//    }
    int indexChecker = -1;
    for(auto iter = parent->block.begin(); iter < parent->block.end(); iter++){
        indexChecker++;
        if ((*iter)->getModel() > car->getModel()) {
            parent->block.insert(iter, car);
            break;
        }
        if(iter+1 == parent->block.end()){
            parent->block.insert(iter+1, car);
            indexChecker++;
            break;
        }
    }

    int checker = 0;
    for(auto iter = parent->children.begin(); iter< parent->children.end(); iter++){
        if(checker==indexChecker+1){
            parent->children.insert(iter, child);
            break;
        }
        if(iter+1 == parent->children.end()){
            parent->children.insert(iter+1, child);
            break;
        }
        checker++;
    }

//    Car* temp = parent->block[parent->size-1];
//    for(int i = parent->size; i> parentBlockIndex; i--){
//        parent->block[i] = parent->block[i-1];
//    }

//    Node* temp2 = parent->children[parent->children.size()-1];
//    for(int i = parent->size+1; i> childBlockIndex; i--){
//        parent->children[i] = parent->children[i-1];
//    }
//    parent->block[parentBlockIndex] = car;
//    parent->block.push_back(temp);
//    parent->children[childBlockIndex] = child;
//    parent->children.push_back(temp2);

}

void Tree::ParentalInsert(Node *parent, Node *child, Car* car) {
    if(parent->size < maxNumChildren-1){
        ChildBlockInsertion(parent, child, car);
        parent->size++;
    }
    else{
        Node* anotherNode = new Node();
        anotherNode->parent = parent->parent;

        vector<Car*> parentBlockCopy;
        for(int i = 0; i< parent->block.size(); i++){
            parentBlockCopy.push_back(parent->block[i]);
        }
        BlockInsertion(parentBlockCopy, car);

        vector<Node*> childrenOfParentCopy;
        for(int i = 0; i< parent->size+1; i++){
            childrenOfParentCopy.push_back(parent->children[i]);
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
        parent->block.clear();
        parent->children.clear();
        for(int i = 0; i< parent->size; i++){
            parent->block.push_back(parentBlockCopy[i]);
            parent->children.push_back(childrenOfParentCopy[i]);
        }
        //No idea why but okay//
        parent->children.push_back(childrenOfParentCopy[parent->size]);
//        parent->children[parent->size] = childrenOfParentCopy[parent->size];

        for(int i = 0; i< anotherNode->size; i++){
            anotherNode->block.push_back(parentBlockCopy[parent->size+i+1]);
            anotherNode->children.push_back(childrenOfParentCopy[i+1+parent->size]);
            anotherNode->children[i]->parent = anotherNode;
        }
        anotherNode->children.push_back(childrenOfParentCopy[anotherNode->size+parent->size+1]);
        //anotherNode->children[anotherNode->size] = childrenOfParentCopy[anotherNode->size+parent->size+1];
        anotherNode->children[anotherNode->size]->parent = anotherNode;

        //Handles pushing up to parent//

        //In case is root//
        Car* c = parentBlockCopy[maxNumChildren/2];
        if(parent->parent == nullptr){
            Node* newRoot = new Node(c);
            newRoot->size++;
            parent->parent = newRoot;
            anotherNode->parent = newRoot;
            newRoot->children.push_back(parent);
            newRoot->children.push_back(anotherNode);
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
                if(i == search->size-1){
                    //Makes sure moves onto final children block//
                    search = search->children[i+1];
                    break;
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
            Node* splitNode = new Node();
            splitNode->leaf = true;
            splitNode->parent = search->parent;
            //ADD NEW SPLITNODE AS CHILD//
            vector<Car*> copyBlock;
            for(int i = 0; i< search->size; i++){
                copyBlock.push_back(search->block[i]);
            }
            //Inserting into copy//
            BlockInsertion(copyBlock, car);

            //Resizing//
            search->size = this->maxNumChildren/2;
            if(this->maxNumChildren % 2 == 0){
                splitNode->size = this->maxNumChildren;
            }
            else{
                splitNode->size = this->maxNumChildren /2 + 1;
            }
            //CHECK IF OTHER CARS IN BLOCK R DELETED
            search->block.clear();
            for(int i = 0; i< search->size; i++){
                search->block.push_back(copyBlock[i]);
            }
            for(int i = 0; i< splitNode->size; i++){
                splitNode->block.push_back(copyBlock[search->size+i]);
            }
            //WHAT DOES THIS EVEN DO//
//            search->children[search->block.size()] = splitNode;
//            splitNode->children[splitNode->block.size()] = search->children[this->maxNumChildren-1];
//            search->children[this->maxNumChildren-1] = nullptr;

            //Something with parent//
            Car* c = splitNode->block[0];
            //Root case
            if(search->parent == nullptr){
                Node* rootBlock = new Node(c);
                rootBlock->size++;
                search->parent = rootBlock;
                splitNode->parent = rootBlock;
                rootBlock->children.push_back(search);
                rootBlock->children.push_back(splitNode);
                this->root = rootBlock;
            }
            else{
                ParentalInsert(search->parent, splitNode, c);
            }
        }
    }
}