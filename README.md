| Branch | CI | Coverage |
|---|---|---|
| master | [![Build Status](https://travis-ci.org/ajze/vigenere-victory.png)](https://travis-ci.org/ajze/vigenere-victory) | [![Coverage Status](https://coveralls.io/repos/github/ajze/vigenere-victory/badge.svg?branch=master&service=github)](https://coveralls.io/github/ajze/vigenere-victory?branch=master) |

# vigenere-victory
The plan for this project is to experiment with some topics and technologies I've wanted to explore for some time whilst remaining enjoyable and educational. Cryptographical mathematics is a passion of mine and the core of this project will be centred around implementing the 'Kasiski's Analysis' technique for a cryptanalytic attack on a message enciphered using the Vigenere Cipher. Motivations for this decision include:
* The project lends itself well to the additional elements I want to embelish the core functionality with, such as some maching learning models, multithreading, and implementing cross stack API's.
* The project is expandable in scope, meaning I can add additional functionality and features to the project/final application as I should desire.
* An preliminary Github search revealed there was not an abundance of identical projects already in existence.

## High Level Plan and Priorities
* **C++** - Implement the core text decipherment functionality in using Kasiski's lead. **[Ongoing]**
  * Benchmark the code and discover the boundaries between and the conditions that lead to success or failure. For example, length of the ciphertext and key length.
* **Matlab/Python 3** - Implement and train a model to support the deciphering module with 'best guess' and 'fill in the blanks' capabilities. **[Testing stage]**
* **Matlab/Python 3** - Implement and train a model to read in the characters from a printed ciphertext message via webcam and deliver it to the decipherment module, with the potential to later include handwritten messages. 
  * I want to build this capability in both Matlab and Python 3 in an effort to contrast and compare. 
  * The Matlab implementation requires creation of a MEX files, the  Matlab-C/C++ API.
  * The Python 3 implementation will require the use of ctypes, the foreign function library for Python.
* Explore a means of augmenting the webcam view to project the deciphered text on top of the ciphertext.
* Experiment with deployment options
  * The options exist to package the application either as a Matlab program containing a C++ .dll, or a C++ application calling Matlab functions using the Matlab Engine API.
  * Explore AWS hosting options treating the application as a service.
* Ensure the supplementary tools are working as desired.
  * Travis CI, Jenkins, Coveralls, Doxygen and so on. 
* Create a walkthrough of the source detailing the implementation and design choices.

## Background
There are many decent histories and explanations of the the Vigenere cipher so it is not worth me creating another one. I will link to a selection of the best resources.


