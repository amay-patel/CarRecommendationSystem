#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include "json-develop/single_include/nlohmann/json.hpp"
#include <chrono>
#include "Car.h"
#include "Tree.h"
#define RUN 8

using namespace std::chrono;
using json = nlohmann::json;
using namespace std;

//This project would not be possible without the json-develop folder
//We used a guide on https://github.com/nlohmann/json to manipulate the cars.json file

/*
 * Meant to take in input for brands
 * If user doesn't have any preference, they can enter in "None" to skip
 * When finished inputting, they can enter in "Done" to move on
 */

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

/*
 * Any questions that ask for a range will call this method
 * Must be answered if user wants a recommendation
 * If user doesn't have any preference, they can enter in "None" to skip
 * When finished inputting, they can enter in "Done" to move on
 */

vector<double> takeRangeInput() {
    vector<double> responses;
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

/*
 * idealCar was calculated back in main but it's the average of the ranges the user provided in main()
 * Cosine similarity will measure the similarity between the idealCar and the current car in goodCars
 * The higher the similarity the better the current car in goodCars is for the user
 * We return a hashmap where double represents the value of the cosine similarity and string represents the ID of car
 */

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

/*
 * Helper method to convert the keys in the map to a vector
 * Will be used to be sorted for keys with the biggest value
 */

vector<double> mapToVec(unordered_map<double, string> hashmap) {
    vector<double> vec;
    for(auto iter = hashmap.begin(); iter != hashmap.end(); ++iter) {
        vec.push_back(iter->first);
    }
    return vec;
}

/*
 * Helper method for mergeSort
 * Code was used from Module 6: Sorting Slides
 * Approved in 3a Proposal
 */

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

/*
 * Merge Sort function to initiate the sorting
 * Code was used from Module 6: Sorting Slides
 * Approved in 3a Proposal
 */

void mergeSort(vector<double>& cars, int left, int right) {
    if(left < right) {
        int mid = left + (right - left)/2;
        mergeSort(cars, left, mid);
        mergeSort(cars, mid + 1, right);
        merge(cars, left, mid, right);
    }
}

/*
 * Insertion Sort function for the Tim Sort function
 * Code was used from Module 6: Sorting Slides
 */

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

/*
 * Tim Sort function that is used in main() function
 * Citing https://www.geeksforgeeks.org/timsort/ for help with implementation
 */

void timSort(vector<double>& arr, int n)
{
    for(int i = 0; i < n; i += RUN) {
        insertionSort(arr, i, min((i + RUN - 1), (n - 1)));
    }
    for(int temp = RUN; temp < n; temp = 2 * temp) {
        for(int left = 0; left < n; left += 2 * temp) {
            int mid = left + temp - 1;
            int right = min((left + 2 * temp - 1), (n - 1));

            if(mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

int main() {
    /*
     * cars vector stores all of the cars from cars.json file
     * idealCar vector is used to calculate cosine similarity
     * goodCars hashmap is used to store cars that meet users requirements
     */
    vector<Car> cars;
//    Tree tree(3,2);
    vector<double> idealCar;
    unordered_map<string, Tree*> hashmap;
    unordered_map<string, vector<double>> goodCars;
    json list;
    ifstream fileOpener("cars.json");
    if(!fileOpener.is_open()) {
        cout << "Whoops" << endl;
        return 0;
    }
    fileOpener >> list;
    //this for loop will read in all of the statistics of the current car in the cars.json
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
        //part of tree
        Car* car = new Car(model, brand, year, horsepower,
                           cityMPG, highwayMPG, fuel, price);
        if(hashmap.find(brand) != hashmap.end()) {
            hashmap[brand].Insert(car);
        }
        else {
            Tree* temp = new Tree(3,2);
            hashmap.insert({brand,temp});
            temp.Insert(car);
        }
    }
    fileOpener.close();
    //bunch of vectors to store user inputs for each question
    vector<string> brands;
    vector<double> years;
    vector<double> rangeHP;
    vector<double> rangeCityMPG;
    vector<double> rangeHighwayMPG;
    vector<string> fuelTypes;
    vector<double> priceRange;
    cout << "Welcome to the Car Recommendation System!" << endl;
    cout << "-----------------------------------------" << endl;
    cout << endl;
    cout << "What is your price range?" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    priceRange = takeRangeInput();
    cout << "Which brand of cars are you looking for?" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    brands = takeInput();
    cout << "What year of cars are you looking for?" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    years = takeRangeInput();
    cout << "Enter in a range of city MPG you are looking for" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    rangeCityMPG = takeRangeInput();
    cout << "Enter in a range of highway MPG you are looking for" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    rangeHighwayMPG = takeRangeInput();
    cout << "What type of fuel are you looking for" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    fuelTypes = takeInput();
    cout << "Enter in a range of horsepower you are looking for" << endl;
    cout << "Enter in 'None' if you have no preference and enter in 'Done' when finished" << endl;
    rangeHP = takeRangeInput();
    //if there's no information from the questions, then just display the first 100 cars and terminate program
    //no recommendation can be made without sufficient information
    if(years.size() == 0 || fuelTypes.size() == 0) {
        cout << endl;
        for(int i = 0; i < 100; i++) {
            cout << cars.at(i).getModel() << endl;
        }
        return 0;
    }
    //there's sufficient information to determine recommendations
    else {
        //we must create the values for the idealCar vector
        //we do this by computing the mean of the values in each of the range vectors
        //then insert them into idealCar vector

        if (priceRange.size() == 0) {
            priceRange.push_back(4000);
            priceRange.push_back(840000);
            idealCar.push_back((priceRange[0] + priceRange[1]) / 2);
        } else {
            idealCar.push_back((priceRange[0] + priceRange[1]) / 2);
        }
        if (rangeCityMPG.size() == 0) {
            rangeCityMPG.push_back(22.4);
            rangeCityMPG.push_back(25.2);
            idealCar.push_back((rangeCityMPG[0] + rangeCityMPG[1]) / 2);
        } else {
            idealCar.push_back((rangeCityMPG[0] + rangeCityMPG[1]) / 2);
        }
        if (rangeHighwayMPG.size() == 0) {
            rangeHighwayMPG.push_back(23.9);
            rangeHighwayMPG.push_back(27.7);
            idealCar.push_back((rangeHighwayMPG[0] + rangeHighwayMPG[1]) / 2);
        } else {
            idealCar.push_back((rangeHighwayMPG[0] + rangeHighwayMPG[1]) / 2);
        }
        if (rangeHP.size() == 0) {
            rangeHP.push_back(100);
            rangeHP.push_back(638);
            idealCar.push_back((rangeHP[0] + rangeHP[1]) / 2);
        } else {
            idealCar.push_back((rangeHP[0] + rangeHP[1]) / 2);
        }
    }
        //bit confusing but it'll make sense
        //remember that user doesnt necessarily need to know what brand they're looking for
        //We are going through the entire cars vector and we need to check if the current car fits the criteria
        //listed out by the user
        //First we check the year, then we check if the current car's horsepower is in the range, then the
        //current car's city mpg, then the current car's highway mpg, then the current car's fuel type,
        //lastly the current car's price tag
        //The current car must fit all of the criteria listed by the user otherwise it will not be inserted into map
        //If all is satisfied, insert the car ID and then its horsepower, city mpg, highway mpg, and price into map
//        if(brands.empty()) {
//            // ****** Replace with Tree search method once implemented ******
//            for(int i = 0; i < cars.size(); i++) {
//                if(cars.at(i).getPrice() >= priceRange[0] && cars.at(i).getPrice() <= priceRange[1]) {
//                    if(cars.at(i).getYear() >= years[0] && cars.at(i).getYear() <= years[1]) {
//                        if(cars.at(i).getCityMpg() >= rangeCityMPG[0] && cars.at(i).getCityMpg() <= rangeCityMPG[1]) {
//                            if(cars.at(i).getHighwayMpg() >= rangeHighwayMPG[0] && cars.at(i).getHighwayMpg() <= rangeHighwayMPG[1]) {
//                                if (find(fuelTypes.begin(), fuelTypes.end(), cars.at(i).getFuel()) != fuelTypes.end()) {
//                                    if (cars.at(i).getHorsepower() >= rangeHP[0] && cars.at(i).getHorsepower() <= rangeHP[1]) {
//                                        goodCars[cars.at(i).getModel()] = {cars.at(i).getPrice(),
//                                                                           cars.at(i).getCityMpg(),
//                                                                           cars.at(i).getHighwayMpg(),
//                                                                           cars.at(i).getHorsepower()};
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        if(brands.empty()) {
//            vector<Car*> decent = tree.Search(tree.getRoot(), years[0], years[1]);
//            for (int i = 0; i < cars.size(); i++) {
//                if (decent.at(i)->getPrice() >= priceRange[0] && decent.at(i)->getPrice() <= priceRange[1]) {
//                    if (decent.at(i)->getCityMpg() >= rangeCityMPG[0] &&
//                        decent.at(i)->getCityMpg() <= rangeCityMPG[1]) {
//                        if (decent.at(i)->getHighwayMpg() >= rangeHighwayMPG[0] &&
//                            decent.at(i)->getHighwayMpg() <= rangeHighwayMPG[1]) {
//                            if (find(fuelTypes.begin(), fuelTypes.end(), decent.at(i)->getFuel()) != fuelTypes.end()) {
//                                if (decent.at(i)->getHorsepower() >= rangeHP[0] &&
//                                    decent.at(i)->getHorsepower() <= rangeHP[1]) {
//                                    goodCars[decent.at(i)->getModel()] = {decent.at(i)->getPrice(),
//                                                                          decent.at(i)->getCityMpg(),
//                                                                          decent.at(i)->getHighwayMpg(),
//                                                                          decent.at(i)->getHorsepower()};
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        else {
//            //This time if you the user specifies brands, we need to check if current car fits the list they provided in the question
//            //We are going through the entire cars vector and we need to check if the current car fits the criteria
//            //listed out by the user
//            //First we check the year, then we check if the current car's horsepower is in the range, then the
//            //current car's city mpg, then the current car's highway mpg, then the current car's fuel type,
//            //lastly the current car's price tag
//            //The current car must fit all of the criteria listed by the user otherwise it will not be inserted into map
//            //If all is satisfied, insert the car ID and then its price, city mpg, highway mpg, and horsepower into map
//            for(int i = 0; i < cars.size(); i++) {
//                if (cars.at(i).getPrice() >= priceRange[0] && cars.at(i).getPrice() <= priceRange[1]) {
//                    if (find(brands.begin(), brands.end(), cars.at(i).getBrand()) != brands.end()) {
//                        if (cars.at(i).getYear() >= years[0] && cars.at(i).getYear() <= years[1]) {
//                            if (cars.at(i).getCityMpg() >= rangeCityMPG[0] &&
//                                cars.at(i).getCityMpg() <= rangeCityMPG[1]) {
//                                if (cars.at(i).getHighwayMpg() >= rangeHighwayMPG[0] &&
//                                    cars.at(i).getHighwayMpg() <= rangeHighwayMPG[1]) {
//                                    if (find(fuelTypes.begin(), fuelTypes.end(), cars.at(i).getFuel()) !=
//                                        fuelTypes.end()) {
//                                        if (cars.at(i).getHorsepower() >= rangeHP[0] &&
//                                            cars.at(i).getHorsepower() <= rangeHP[1]) {
//                                            goodCars[cars.at(i).getModel()] = {cars.at(i).getPrice(),
//                                                                               cars.at(i).getCityMpg(),
//                                                                               cars.at(i).getHighwayMpg(),
//                                                                               cars.at(i).getHorsepower()};
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//    //then with the map that has all of the cars and stats that match user preferences,
//    //we compute cosine similarity for each car
//    unordered_map<double, string> calc = cosine_similarity(idealCar, goodCars);
//    //below method will obtain all of the keys in the calc map
//    //will be used in sorting methods
//    //no changing...we need this to satisfy project requirements for 2 non-trivial sorting methods
//    vector<double> sortVec = mapToVec(calc);
//    //user gets to decide what sorting they would like to use
//    //only selection is MergeSort or TimSort
//    string input;
//    cout << "What type of sort would you like to use: MergeSort or TimSort" << endl;
//    while(true) {
//        cin >> input;
//        if(input == "MergeSort") {
//            break;
//        }
//        else if(input == "TimSort") {
//            break;
//        }
//        else {
//            input = "";
//        }
//    }
//    //we need to compute the time it takes for sorting to work
//    //saw people in slack compute time for sorting methods...makes sense to do because
//    //project requirements says we need to compare performance of two sorting algos or DSs
//    //no changing
//    auto start = high_resolution_clock::now();
//    if(input == "MergeSort") {
//        mergeSort(sortVec, 0, sortVec.size() - 1);
//    }
//    else if(input == "TimSort") {
//        timSort(sortVec, sortVec.size());
//    }
//    //stop the clock. sorting is done
//    auto stop = high_resolution_clock::now();
//    //reverse the sortedVec to get the value with the highest cosine similarity
//    //now we want to display top 50 cars that match user preferences
//    //if there are not 50 cars, then just display the most that can be displayed
//    //we use calc map to output the cars that best match user preferences (remember how calc map's values are car ID's)
//    reverse(sortVec.begin(), sortVec.end());
//    if(sortVec.size() < 50) {
//        cout << endl;
//        for(int i = 0; i < sortVec.size(); i++) {
//            if(calc.find(sortVec.at(i)) != calc.end()) {
//                cout << calc[sortVec.at(i)] << endl;
//            }
//        }
//    }
//    else {
//        cout << endl;
//        for(int i = 0; i < 50; i++) {
//            if(calc.find(sortVec.at(i)) != calc.end()) {
//                cout << calc[sortVec.at(i)] << endl;
//            }
//        }
//    }
//    cout << endl;
//    //show how long it took for the sorting methods to do their thing
//    //no changing we need this for project requirements
//    if(input == "MergeSort") {
//        cout << "MergeSort took " << duration_cast<microseconds>(stop - start).count() << " microseconds!" << endl;
//    }
//    else if(input == "TimSort") {
//        cout << "TimSort took " << duration_cast<microseconds>(stop - start).count() << " microseconds!" << endl;
//    }
    return 0;
}
