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
};

vector<string> takeInput() {
    vector<string> responses;
    while(true) {
        string input;
        cin >> input;
        if(input == "None") {
            break;
        }
        else if(input == "Done") {
            break;
        }
        else {
            responses.push_back(input);
        }
    }
    return responses;
}

vector<int> takeYearInput() {
    vector<int> responses;
    while(true) {
        string input;
        cin >> input;
        if(input == "None") {
            break;
        }
        else if(input == "Done") {
            break;
        }
        else {
            if(responses.size() == 9) {
                return responses;
            }
            responses.push_back(stoi(input));
        }
    }
    return responses;
}

vector<int> takeRangeInput() {
    vector<int> responses;
    while(true) {
        string input;
        cin >> input;
        if(input == "None") {
            break;
        }
        else if(input == "Done") {
            break;
        }
        else {
            if(responses.size() >= 2) {
                return responses;
            }
            responses.push_back(stoi(input));
        }
    }
    return responses;
}

void cosine_similarility(vector<double> idealCar, vector<vector<double>> goodCars) {
    for(int i = 0; i < goodCars.size(); i++) {
        double dotproduct = 0.0;
        double denom_idealCar = 0.0;
        double denom_currCar = 0.0;
        for(int j = 0; j < goodCars[i].size(); j++) {
            dotproduct += idealCar[j] * goodCars.at(i).at(j);
            denom_idealCar += idealCar[j] * idealCar[j];
            denom_currCar += goodCars.at(i).at(j) * goodCars.at(i).at(j);
        }
        goodCars[i].push_back(dotproduct / (sqrt(denom_idealCar) * sqrt(denom_currCar)));
    }
}

int main() {
    vector<Car> cars;
    vector<vector<int>> info;
    json list;
    ifstream fileOpener("cars.json");
    if(!fileOpener.is_open()) {
        cout << "Whoops" << endl;
    }
    fileOpener >> list;
    //Create the cars vector. Temporary place to store
    for(int i = 0; i < list.size(); i++) {
        vector<int> carInfo;
        string model = list[i].at("Identification.ID");
        string brand = list[i].at("Identification.Make");
        int year = list[i].at("Identification.Year");
        int horsepower = list[i].at("Engine Information.Engine Statistics.Horsepower");
        int cityMPG = list[i].at("Fuel Information.City mpg");
        int highwayMPG = list[i].at("Fuel Information.Highway mpg");
        string fuel = list[i].at("Fuel Information.Fuel Type");
        int price = list[i].at("Price");
        int gears = list[i].at("Engine Information.Number of Forward Gears");
        cars.push_back(Car(model, brand, year, horsepower, cityMPG, highwayMPG, fuel, price, gears));
        carInfo.push_back(horsepower);
        carInfo.push_back(cityMPG);
        carInfo.push_back(highwayMPG);
        carInfo.push_back(price);
        carInfo.push_back(gears);
        info.push_back(carInfo);
    }
    vector<string> brands;
    vector<int> years;
    vector<int> rangeHP;
    vector<int> rangeCityMPG;
    vector<int> rangeHighwayMPG;
    vector<string> fuelTypes;
    vector<int> priceRange;
    cout << "Welcome to the Car Recommendation System!" << endl;
    cout << "-----------------------------------------" << endl;
    cout << endl;
    cout << "Which brand of cars are you looking for?" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    brands = takeInput();
    cout << "What year of cars are you looking for?" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    years = takeYearInput();
    cout << "Enter in a range of horsepower you are looking for" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    rangeHP = takeRangeInput();
    cout << "Enter in a range of city MPG you are looking for" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    rangeCityMPG = takeRangeInput();
    cout << "Enter in a range of highway MPG you are looking for" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    rangeHighwayMPG = takeRangeInput();
    cout << "What type of fuel are you looking for" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    fuelTypes = takeInput();
    cout << "What is your price range?" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    priceRange = takeRangeInput();
    if(brands.size() == 0 && years.size() == 0 && rangeHP.size() == 0 && rangeCityMPG.size() == 0 &&
    rangeHighwayMPG.size() == 0 && fuelTypes.size() == 0) {
        //TODO: Call MergeSort
        //TODO: Call Radix Sort (or some other non-trivial sorting method)
    }
    return 0;
}