[![Build Status](https://travis-ci.org/ajze/vigenere-victory.png)](https://travis-ci.org/ajze/vigenere-victory)
[![Coverage Status](https://coveralls.io/repos/github/ajze/vigenere-victory/badge.svg?branch=master)](https://coveralls.io/github/ajze/vigenere-victory?branch=master)

# vigenere-victory
The plan for this project is to experiment with some topics and technologies I've wanted to explore for some time whilst remaining enjoyable and educational. Cryptographical mathematics is a passion of mine and the core of this project will be centred around implementing the 'Kasiski's Analysis' technique for a cryptanalytic attack on a message enciphered using the Vigenere Cipher. Motivations for this decision include:
* The project lends itself well to the additional elements I want to embelish the core functionality with, such as some maching learning models, multithreading, and implementing cross stack API's.
* The project is expandable in scope, meaning I can add additional functionality and features to the project/final application as I should desire.
* An preliminary Github search revealed there was not an abundance of identical projects already in existence.

## High Level Plan and Priorities
* **C++** - Implement the core text dicipherment functionality in using Kasiski's lead. Benchmark the code and discover the boundaries between and the conditions that lead to success or failure. For example, length of the cyphertext and key length.
* **Matlab/Python** - Implement and train a model to support the diciphering module with 'best guess' and 'fill in the blanks' capabilities.
* **Matlab/Python** - Implement and train a model to read in the characters from a printed ciphertext message via webcam and deliver it to the dicypherment module, with the potential to later include handwritten messages. 

⋅⋅1. This is a sublist
