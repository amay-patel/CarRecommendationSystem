#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "Tree.h"
#include "Tree.cpp"
#include "Car.h"
using namespace std;

void parseInput (string filename, unordered_map <string, Tree*> &carBrandTrees) {
    ifstream file(filename);
    if (!file) {
        cout << "faulty file name";
        return;
    }

    vector<string> row;
    string line, word;
    getline (file,line); // header
    int debugLimit = 5; // limit the number of lines to parse for debugging purposes
    while (getline (file, line) && debugLimit) {
        row.clear();
        stringstream str(line);
        while (getline(str, word, ','))
            row.push_back(word);
        // make the current car a Car object
        Car* car = new Car(
            row[12], // model
            row[13], // brand
            stoi(row[15]), // year
            stoi(row[16]), // horsepower
            stoi(row[8]), // cityMPG
            stoi(row[10]), // highwayMPG
            row[9], // fuel
            stoi(row[18]) // price
        );
        // if the current brand does not exist as a key in the map, add it
        if (carBrandTrees.find(row[13]) == carBrandTrees.end()) {
            carBrandTrees[row[13]] = new Tree(3, 2);
        }
        // add the current car to its respective brand Tree
        carBrandTrees[row[13]]->Insert(car);
        
        // debugLimit--; // comment out line if not debugging
    }
}

int main() {
    unordered_map <string, Tree*> carBrandTrees;
    parseInput("cmake-build-debug/cars.csv", carBrandTrees);
    
    return 0;
}