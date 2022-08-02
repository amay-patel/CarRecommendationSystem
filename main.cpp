#include <iostream>
#include <unordered_map>
#include "Tree.h"
#include "Car.h"
using namespace std;


int main() {
    int numCars;
    string model;
    string brand;
    int year;
    double horsepower;
    double cityMPG;
    double highwayMPG;
    string fuel;
    double price;
    // double gears;
    unordered_map <string, Tree*> carBrandTrees;
    cin >> numCars;
    while(numCars!=0){
        cin >> model;
        cin >> brand;
        cin >> year;
        cin >> horsepower;
        cin >> cityMPG;
        cin >> highwayMPG;
        cin >> fuel;
        cin >> price;
        // cin >> gears;
        Car* car = new Car(model, brand, year, horsepower, cityMPG, highwayMPG,
                fuel, price/*, gears*/);
        if (carBrandTrees.find(brand) == carBrandTrees.end()) {
            carBrandTrees[brand] = new Tree(3, 2);
        }
        carBrandTrees[brand]->Insert(car);
        numCars--;
    }
    return 0;
}