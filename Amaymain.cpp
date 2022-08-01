#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "json-develop/single_include/nlohmann/json.hpp"
#include "Car.h"
#include "Tree.h"

using json = nlohmann::json;
using namespace std;


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

unordered_map<double, string> cosine_similarility(vector<double> idealCar, unordered_map<string, vector<double>>& goodCars) {
    unordered_map<double, string> cosCars;
    for(auto iter = goodCars.begin(); iter != goodCars.end(); ++iter) {
        double dotproduct = 0.0;
        double denom_idealCar = 0.0;
        double denom_currCar = 0.0;
        for(int i = 0; i < iter->second.size(); i++) {
            dotproduct += idealCar[i] * goodCars[iter->first].at(i);
            denom_idealCar += idealCar[i] * idealCar[i];
            denom_currCar += goodCars[iter->first].at(i) * goodCars[iter->first].at(i);
        }
        double cosSimilarilty = (dotproduct / (sqrt(denom_idealCar) * sqrt(denom_currCar)));
        cosCars[cosSimilarilty] = iter->first;
    }
    return cosCars;
}

vector<double> mapToVec(unordered_map<double, string> hashmap) {
    vector<double> vec;
    for(auto iter = hashmap.begin(); iter != hashmap.end(); ++iter) {
        vec.push_back(iter->first);
    }
    return vec;
}

int main() {
    vector<Car> cars;
    vector<double> idealCar;
    vector<Car> goodCars;
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
    brands = takeInput();
    cout << "What year of cars are you looking for?" << endl;
    years = takeYearInput();
    cout << "Enter in a range of horsepower you are looking for" << endl;
    rangeHP = takeRangeInput();
    cout << "Enter in a range of city MPG you are looking for" << endl;
    rangeCityMPG = takeRangeInput();
    cout << "Enter in a range of highway MPG you are looking for" << endl;
    rangeHighwayMPG = takeRangeInput();
    cout << "What type of fuel are you looking for" << endl;
    fuelTypes = takeInput();
    cout << "What is your price range?" << endl;
    priceRange = takeRangeInput();
    if(brands.size() == 0 && years.size() == 0 && rangeHP.size() == 0 && rangeCityMPG.size() == 0 &&
    rangeHighwayMPG.size() == 0 && fuelTypes.size() == 0) {
        string input;
        cout << "What type of sort do you want to use" << endl;
        cout << "Enter in either MergeSort or someothersort" << endl;
        while(true) {
            cin >> input;
            if(input == "MergeSort") {
                //TODO: MergeSort the whole Car vector
                break;
            }
            else if(input == "") {
                //TODO: sort the whole Car vector
                break;
            }
            else {
                input = "";
            }
        }
    }
    else {
        idealCar.push_back((rangeHP[0]+rangeHP[1])/2);
        idealCar.push_back((rangeCityMPG[0]+rangeCityMPG[1])/2);
        idealCar.push_back((rangeHighwayMPG[0]+rangeHighwayMPG[1])/2);
        idealCar.push_back((priceRange[0]+priceRange[1])/2);
        for(int i = 0; i < cars.size(); i++) {
            if(find(brands.begin(), brands.end(), cars.at(i).brand) != brands.end()) {
                if(find(years.begin(), years.end(), cars.at(i).year) != years.end()) {
                    if(cars.at(i).horsepower >= rangeHP[0] && cars.at(i).horsepower <= rangeHP[1]) {
                        if(cars.at(i).cityMPG >= rangeCityMPG[0] && cars.at(i).cityMPG <= rangeCityMPG[1]) {
                            if(cars.at(i).highwayMPG >= rangeHighwayMPG[0] && cars.at(i).highwayMPG <= rangeHighwayMPG[1]) {
                                if(cars.at(i).price >= priceRange[0] && cars.at(i).price <= priceRange[1]) {
                                    goodCars.push_back(cars.at(i));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}