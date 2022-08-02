# CarRecommendationSystem
Car Recommendation System for Data Structures and Algorithms Project
Created by Amay Patel, Rohan Chander, and Saurabh Anand for COP3530 - Data Structures & Algorithms on 08/02/2022

The Car Recommendation System recommends cars to a user based on certain criteria that they are asked once starting the program
The car data is retrieved from a database and read into a B+ Tree data structure
Next, user input for certain criteria is requested
Then, the program searches through the B+ Tree for the most relevant cars
Finally, the relevant cars are outputted to the user

A B+ Tree is defined by a few criteria
- Every node has at most l children.
- Every non-leaf node (except root) has at least ⌈l/2⌉ child nodes.
- The root has at least two children if it is not a leaf node.
- A non-leaf node with k children contains k − 1 keys.
- All leaves appear in the same level and carry no information.
