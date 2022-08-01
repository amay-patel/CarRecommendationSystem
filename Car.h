//
// Created by Rohan Chander on 8/1/22.
//

#ifndef TREE_CAR_REC_SERVICE_CAR_H
#define TREE_CAR_REC_SERVICE_CAR_H
#include <iostream>
using namespace std;

class Car {
private:
    string model;
    string brand;
    int year;
    double horsepower;
    double cityMPG;
    double highwayMPG;
    string fuel;
    double price;
    double gears;
    //string classification;
    //string transmission;
    //string engine;

public:
    Car() {

    }

    Car(string carModel, string carBrand, int carYear, double carHP, double carCityMpg, double carHighwayMPG,
        string carFuel, double carPrice, double numGears) {
        this->model = carModel;
        this->brand = carBrand;
        this->year = carYear;
        this->horsepower = carHP;
        this->cityMPG = carCityMpg;
        this->highwayMPG = carHighwayMPG;
        this->fuel = carFuel;
        this->price = carPrice;
        this->gears = numGears;
    }

    const string &getModel() const {
        return model;
    }

    const string &getBrand() const {
        return brand;
    }

    int getYear() const {
        return year;
    }

    double getHorsepower() const {
        return horsepower;
    }

    double getCityMpg() const {
        return cityMPG;
    }

    double getHighwayMpg() const {
        return highwayMPG;
    }

    const string &getFuel() const {
        return fuel;
    }

    double getPrice() const {
        return price;
    }

    double getGears() const {
        return gears;
    }
};




#endif //TREE_CAR_REC_SERVICE_CAR_H