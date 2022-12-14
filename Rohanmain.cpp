#include <iostream>
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
    Tree tree(3, 2);
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
        tree.Insert(car);
        numCars--;
    }
    vector<Car*> test = tree.Search(tree.getRoot(), 90, 2010);
    cout << "Cars within that year range:" << endl;
    for(auto iter = test.begin(); iter != test.end(); iter++){
        cout << (*iter)->getModel() << endl;
    }
    return 0;
}