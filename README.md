| Branch | CI | Coverage | Website |
|---|---|---|---|
| master | [![Build Status](https://travis-ci.org/ajze/vigenere-victory.png)](https://travis-ci.org/ajze/vigenere-victory) | [![Coverage Status](https://coveralls.io/repos/github/ajze/vigenere-victory/badge.svg?branch=master&service=github)](https://coveralls.io/github/ajze/vigenere-victory?branch=master) | [work.jonze.uk](https://work.jonze.uk) |

# vigenere-victory
The plan for this project is to experiment with some topics and technologies I've wanted to explore for some time whilst remaining enjoyable and educational. Cryptographical mathematics is a passion of mine and the core of this project will be centred around implementing the 'Kasiski's Analysis' technique for a cryptanalytic attack on a message enciphered using the Vigenere Cipher. Motivations for this decision include:
* The project lends itself well to the additional elements I want to embelish the core functionality with, such as some maching learning models, multithreading, and implementing cross stack API's.
* The project is expandable in scope, meaning I can add additional functionality and features to the project/final application as I should desire.
* An preliminary Github search revealed there was not an abundance of identical projects already in existence.

A very basic outline likely to change: (Made using PlantUML)
![alt text](https://raw.githubusercontent.com/ajze/vigenere-victory/master/uml/prog.png)

### Updates
* **27/02/18** - Correctly returning the key length for keys of length 3, 4, 5, 6, and 7. All the test messages so far have been above 1000 characters and I still need to find a lower bound on message length where the accuracy begins to drop.
* **10/03/18** - Correctly returning the key length for keys of length 3, 4, 5, 6, and 7 down to messages of 800 characters. 
Below 800 characters keys of length 5 are being deduced as length 10 for a reason I still need to investigate.
* **21/03/18** - Correctly returning the encyption key and key length for keys of length 3, 4, 5, 6, and 7 down to messages of 800 characters. From detection of an input string to a successful cryptanalysis attack is taking between 2 and 5 milliseconds. The only thing left to do is implement the Vigenere tableau itself so the program can return the decrypted message.
* **23/03/18** - I need to put this project to bed for a while so I can focus on my freelancing as well as make a start with the project's accompying blog post. I have decided I also want to have the option to decouple the application from MATLAB, so the end user can choose to run with the MATLAB api, or simply paste ciphertexts into the command line. I have also started a Qt project for a rudimentary gui. In TravisCI I've also had to ditch building against g++5/6 and clang-3.6/3.7 because they were getting in the way of C++14/17 features I wanted to use like `constexpr` and `auto [first, second]` for tuple unpacking. I am struggling to get clang-5.0 working with Travis' Trusty (14.04) image, so I am only building with clang locally at the moment. 
* **27/03/18** - The application now defaults to accepting the ciphertext via the command line. This can be overridden by starting the application with `./VigenereVictory --matlab`. This won't be much use at all to anybody but me right now because the location where it searches for the Matlab output is currently hardcoded in for my ease. This will change when I ship the GUI. The decryption functionality is being tested and it will be added soon so the app can spit out the plaintext. Making a downloadable binary available.

## How to Use
* Build the project via Cmake (tested and working with GCC7 and Clang-5) or download the [Linux](https://work.jonze.uk/wp-content/uploads/2018/02/Linux.zip) or [macOS](https://work.jonze.uk/wp-content/uploads/2018/02/macOS.zip) binary.
* Run the application via the command line with `./VigenereVictory`
* To prep a test message I have been using:
  * [This](https://www.browserling.com/tools/remove-punctuation) to remove all punctuation from a message.
  * [This](https://www.browserling.com/tools/remove-all-whitespace) to remove all the whitespace from a message.
  * [This](https://convertcase.net/) to convert the message to upper case.
  * And finally, [this](https://www.dcode.fr/vigenere-cipher) to encode the message with a key.
  * (I am going to write a script to perform all of the above during my next session.)
* Paste the ciphertext string in at the prompt and, (until I implement the decoder) you should finish with something like this:

![alt text](https://work.jonze.uk/wp-content/uploads/2018/02/Screenshot-from-2018-03-27-22-56-06.png)

* The reason for enforcing monocase strings with no numbers at this time is that I wanted to authentically replicate the types of messages that the Vigenere Cipher and other polyalphabetic ciphers would have been used for in the times of Giovan Battista Bellaso, the cipher's originator, (and not Blaise de Vigenère!). Numbers and whitespace were considered to convey too much derivable context to an informed interceptor, even before cryptanalysis on the message had begun. 
  

## High Level Plan and Priorities
* **C++** - Implement the core text decipherment functionality in using Kasiski's lead. **[V.1 Finished]**
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


