#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "json-develop/single_include/nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

class Car {
    private:
        string model;
        string brand;
        int year;
        int horsepower;
        int cityMPG;
        int highwayMPG;
        string fuel;
        int price;
        string classification;
        //string transmission;
        //int gears;
        //string engine;

    public:
        Car() {

        }

        Car(string carModel, string carBrand, int carYear, int carHP, int carCityMpg, int carHighwayMPG, string carFuel) {
            this->model = carModel;
            this->brand = carBrand;
            this->year = carYear;
            this->horsepower = carHP;
            this->cityMPG = carCityMpg;
            this->highwayMPG = carHighwayMPG;
            this->fuel = carFuel;
        }
};

int main() {
    vector<Car> cars;
    json list;
    unordered_set<string> hashset;
    ifstream fileOpener("cars.json");
    fileOpener >> list;
    for(int i = 0; i < list.size(); i++) {
        auto identification = list[i].at("Identification");
        auto engineInfo = list[i].at("Engine Information");
        auto engineStats = engineInfo.at("Engine Statistics");
        auto fuelInfo = list[i].at("Fuel Information");
        auto ID = identification.at("ID");
        if(hashset.find(ID) == hashset.end()) {
            hashset.insert(ID);
            auto model = identification.at("ID");
            auto brand = identification.at("Make");
            auto year = identification.at("Year");
            auto hp = engineStats.at("Horsepower");
            auto citympg = fuelInfo.at("City mpg");
            auto highwaympg = fuelInfo.at("Highway mpg");
            auto fuel = fuelInfo.at("Fuel Type");
            cars.push_back(Car(model, brand, year, hp, citympg, highwaympg, fuel));
        }
    }
}