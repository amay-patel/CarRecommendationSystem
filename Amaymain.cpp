#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "json-develop/single_include/nlohmann/json.hpp"
#include <chrono>
#include "Car.h"
#define RUN 8

using namespace std::chrono;
using json = nlohmann::json;
using namespace std;

//This project would not be possible without the json-develop folder
//We used a guide on https://github.com/nlohmann/json to manipulate the cars.json file

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

unordered_map<double, string> cosine_similarity(vector<double> idealCar, unordered_map<string, vector<double>>& goodCars) {
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

//Helper method for mergeSort
//Code was used from Module 6 Slides
//Approved in 3a Proposal
void merge(vector<double>& cars, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<double> half(n1);
    vector<double> otherHalf(n2);
    for(int i = 0; i < n1; i++) {
        half[i] = cars[left + i];
    }
    for(int j = 0; j < n2; j++) {
        otherHalf[j] = cars[mid+1+j];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while(i < n1 && j < n2) {
        if(half[i] <= otherHalf[j]) {
            cars[k] = half[i];
            i++;
            k++;
        }
        else {
            cars[k] = otherHalf[j];
            j++;
            k++;
        }
    }
    while(i < n1) {
        cars[k] = half[i];
        i++;
        k++;
    }
    while(j < n2) {
        cars[k] = otherHalf[j];
        j++;
        k++;
    }
}

//mergeSort function to initiate the sorting
//Code was used from Module 6: Sorting Slides
//Approved in 3a Proposal
void mergeSort(vector<double>& cars, int left, int right) {
    if(left < right) {
        int mid = left + (right - left)/2;
        mergeSort(cars, left, mid);
        mergeSort(cars, mid + 1, right);
        merge(cars, left, mid, right);
    }
}

void insertionSort(vector<double>& cars, int left, int right) {
    for(int i = left + 1; i <= right; i++) {
        double key = cars[i];
        int j = i - 1;
        while(j >= left && cars[j] > key) {
            cars[j + 1] = cars[j];
            j--;
        }
        cars[j + 1] = key;
    }
}

void timSort(vector<double>& arr, int n)
{
    for(int i = 0; i < n; i += RUN) {
        insertionSort(arr, i, min((i + RUN - 1), (n - 1)));
    }
    for(int temp = RUN; temp < n; temp = 2 * temp) {
        for(int left = 0; left < n; left += 2 * temp) {
            int mid = left + temp - 1;
            int right = min((left + 2*temp - 1), (n-1));

            if(mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

int main() {
    vector<Car> cars;
    vector<double> idealCar;
    unordered_map<string, vector<double>> goodCars;
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
        for(int i = 0; i < 100; i++) {
            cout << cars.at(i).getModel() << endl;
        }
        return 0;
    }
    else {
        idealCar.push_back((rangeHP[0]+rangeHP[1])/2);
        idealCar.push_back((rangeCityMPG[0]+rangeCityMPG[1])/2);
        idealCar.push_back((rangeHighwayMPG[0]+rangeHighwayMPG[1])/2);
        idealCar.push_back((priceRange[0]+priceRange[1])/2);
        if(brands.empty()) {
            for(int i = 0; i < cars.size(); i++) {
                if(find(years.begin(), years.end(), cars.at(i).getYear()) != years.end()) {
                    if(cars.at(i).getHorsepower() >= rangeHP[0] && cars.at(i).getHorsepower() <= rangeHP[1]) {
                        if(cars.at(i).getCityMpg() >= rangeCityMPG[0] && cars.at(i).getCityMpg() <= rangeCityMPG[1]) {
                            if(cars.at(i).getHighwayMpg() >= rangeHighwayMPG[0] && cars.at(i).getHighwayMpg() <= rangeHighwayMPG[1]) {
                                if (find(fuelTypes.begin(), fuelTypes.end(), cars.at(i).getFuel()) != fuelTypes.end()) {
                                    if (cars.at(i).getPrice() >= priceRange[0] && cars.at(i).getPrice() <= priceRange[1]) {
                                        vector<double> temp;
                                        temp.push_back(cars.at(i).getHorsepower());
                                        temp.push_back(cars.at(i).getCityMpg());
                                        temp.push_back(cars.at(i).getHighwayMpg());
                                        temp.push_back(cars.at(i).getPrice());
                                        goodCars.insert({cars.at(i).getModel(), temp});
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else {
            for(int i = 0; i < cars.size(); i++) {
                if (find(brands.begin(), brands.end(), cars.at(i).getBrand()) != brands.end()) {
                    if (find(years.begin(), years.end(), cars.at(i).getYear()) != years.end()) {
                        if (cars.at(i).getHorsepower() >= rangeHP[0] && cars.at(i).getHorsepower() <= rangeHP[1]) {
                            if (cars.at(i).getCityMpg() >= rangeCityMPG[0] &&
                                cars.at(i).getCityMpg() <= rangeCityMPG[1]) {
                                if (cars.at(i).getHighwayMpg() >= rangeHighwayMPG[0] &&
                                    cars.at(i).getHighwayMpg() <= rangeHighwayMPG[1]) {
                                    if (find(fuelTypes.begin(), fuelTypes.end(), cars.at(i).getFuel()) !=
                                        fuelTypes.end()) {
                                        if (cars.at(i).getPrice() >= priceRange[0] &&
                                            cars.at(i).getPrice() <= priceRange[1]) {
                                            goodCars[cars.at(i).getModel()] = {cars.at(i).getHorsepower(),
                                                                               cars.at(i).getCityMpg(),
                                                                               cars.at(i).getHighwayMpg(),
                                                                               cars.at(i).getPrice()};
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    unordered_map<double, string> calc = cosine_similarity(idealCar, goodCars);
    vector<double> sortVec = mapToVec(calc);
    string input;
    cout << "What type of sort would you like to use: MergeSort or TimSort" << endl;
    while(true) {
        cin >> input;
        if(input == "MergeSort") {
            break;
        }
        else if(input == "TimSort") {
            break;
        }
        else {
            input = "";
        }
    }
    auto start = high_resolution_clock::now();
    if(input == "MergeSort") {
        mergeSort(sortVec, 0, sortVec.size() - 1);
    }
    else if(input == "TimSort") {
        timSort(sortVec, sortVec.size());
    }
    auto stop = high_resolution_clock::now();
    reverse(sortVec.begin(), sortVec.end());
    if(sortVec.size() < 50) {
        for(int i = 0; i < sortVec.size(); i++) {
            if(calc.find(sortVec.at(i)) != calc.end()) {
                cout << calc[sortVec.at(i)] << endl;
            }
        }
    }
    else {
        for(int i = 0; i < 50; i++) {
            if(calc.find(sortVec.at(i)) != calc.end()) {
                cout << calc[sortVec.at(i)] << endl;
            }
        }
    }
    cout << endl;
    if(input == "MergeSort") {
        cout << "MergeSort took " << duration_cast<microseconds>(stop - start).count() << " microseconds!" << endl;
    }
    else if(input == "TimSort") {
        cout << "TimSort took " << duration_cast<microseconds>(stop - start).count() << " microseconds!" << endl;
    }
    return 0;
}
