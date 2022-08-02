# CarRecommendationSystem
The Car Recommendation System recommends cars to a user based on certain criteria that they input. The car data is retrieved from a [database](https://think.cs.vt.edu/corgis/json/cars/) and read into a B+ Tree data structure. Next, user input for certain criteria is requested. Then, the program searches through the B+ Tree for the most relevant cars. Finally, the relevant cars are outputted to the user

*Created by Amay Patel, Rohan Chander, and Saurabh Anand for COP3530 - Data Structures & Algorithms on 08/01/2022*
***

## User Process

The hierarchy of criteria that guides our insertion and searching algorithm for the B+ Tree is as follows (in other words, these are the parameters the user will be searching for in order of importance):
1. Price tag (Range)
2. Brand (Select values)
3. Year* (Range)
4. City MPG (Range)
5. Highway MPG (Range)
6. Fuel type* (Select values)
7. Horsepower (Range)

*\*Required*

The user can enter multiple values for a parameter or type *"None"* which searches for all values of the parameter. Once a list of cars that meet the user's criteria is complete, we will compute the cosine similarity on each car with the user's ideal car (the ideal car is created by averaging the values specified in price tag, city mpg, highway mpg, and horsepower). The 50 cars with the highest similarity will be returned with the first car in the output being the most similar to the user's preferences.

***

## Data Structures Used

A B+ Tree is defined by a few criteria:
- Every node has at most l children.
- Every non-leaf node (except root) has at least ⌈l/2⌉ child nodes.
- The root has at least two children if it is not a leaf node.
- A non-leaf node with k children contains k − 1 keys.
- All leaves appear in the same level and carry no information.

## Sorting Algorithms Used

When the user is done inputting their preferences for the car recommendation system, they will be asked whether they would like to use the MergeSort or TimSort algorithm for their recommended cars list.

### Mergesort

MergeSort is a divide-and-conquer sorting algorithm used to sort the vector in our program. The divide step divides the vector into multiple small vectors while the conquer step merges the small vectors a bigger and sorted vector. It has best, average, and worst case time complexity of O(nlogn). 

### TimSort
TimSort is a unique sorting algorithm that is derived from the InsertionSort and MergeSort algorithms. It has a best case time complexity of O(n) and an average and worst case time complexity of O(nlogn). 
