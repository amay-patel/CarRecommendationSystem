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
        //string classification;
        //string transmission;
        //int gears;
        //string engine;

    public:
        Car() {

        }

        Car(string carModel, string carBrand, int carYear, int carHP, int carCityMpg, int carHighwayMPG, string carFuel, int carPrice) {
            this->model = carModel;
            this->brand = carBrand;
            this->year = carYear;
            this->horsepower = carHP;
            this->cityMPG = carCityMpg;
            this->highwayMPG = carHighwayMPG;
            this->fuel = carFuel;
            this->price = carPrice;
        }
};

int main() {
    vector<Car> cars;
    json list;
    ifstream fileOpener("cars.json");
    if(!fileOpener.is_open()) {
        cout << "Whoops" << endl;
    }
    fileOpener >> list;
    for(int i = 0; i < list.size(); i++) {
        string model = list[i].at("Identification.ID");
        string brand = list[i].at("Identification.Make");
        int year = list[i].at("Identification.Year");
        int horsepower = list[i].at("Engine Information.Engine Statistics.Horsepower");
        int cityMPG = list[i].at("Fuel Information.City mpg");
        int highwayMPG = list[i].at("Fuel Information.Highway mpg");
        string fuel = list[i].at("Fuel Information.Fuel Type");
        int price = list[i].at("Price");
        cars.push_back(Car(model, brand, year, horsepower, cityMPG, highwayMPG, fuel, price));
    }
    cout << cars.size() << endl;
    return 0;
}