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
int main() {
    vector<Car> cars;
    json list;
    ifstream fileOpener("cars.json");
    if(!fileOpener.is_open()) {
        cout << "Whoops" << endl;
    }
    fileOpener >> list;
    //Create the cars vector. Temporary place to store
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
    return 0;
}