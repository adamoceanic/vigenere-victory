| Branch | CI | Coverage | Website | Development |
|---|---|---|---|---|
| master | [![Build Status](https://travis-ci.org/ajze/vigenere-victory.png)](https://travis-ci.org/ajze/vigenere-victory) | [![Coverage Status](https://coveralls.io/repos/github/ajze/vigenere-victory/badge.svg?branch=master&service=github)](https://coveralls.io/github/ajze/vigenere-victory?branch=master) | [vigenerevictory.ajze.co.uk](http://vigenerevictory.ajze.co.uk) | [work.jonze.uk](https://work.jonze.uk) |

# vigenere-victory
Cryptographical mathematics is a passion of mine and the core of this project will be centred around implementing the 'Kasiski's Analysis' technique for a cryptanalytic attack on a message enciphered using the Vigenere Cipher. 
A very basic outline likely to change: (Made using PlantUML)

### Updates
* **27/02/18** - Correctly returning the key length for keys of length 3, 4, 5, 6, and 7. All the test messages so far have been above 1000 characters and I still need to find a lower bound on message length where the accuracy begins to drop.
* **10/03/18** - Correctly returning the key length for keys of length 3, 4, 5, 6, and 7 down to messages of 800 characters. 
Below 800 characters keys of length 5 are being deduced as length 10 for a reason I still need to investigate.
* **21/03/18** - Correctly returning the encyption key and key length for keys of length 3, 4, 5, 6, and 7 down to messages of 800 characters. From detection of an input string to a successful cryptanalysis attack is taking between 2 and 5 milliseconds. The only thing left to do is implement the Vigenere tableau itself so the program can return the decrypted message.
* **23/03/18** - I have also started a Qt project for a rudimentary gui. In TravisCI I've also had to ditch building against g++5/6 and clang-3.6/3.7 because they were getting in the way of C++14/17 features I wanted to use like `constexpr`, and `auto [first, second]` for tuple unpacking. I am struggling to get clang-5.0 working with Travis' Trusty (14.04) image, so I am only building with Clang locally at the moment. 
* **27/03/18** - The application now defaults to accepting the ciphertext via the command line. This can be overridden by starting the application with `./VigenereVictory --matlab`. This won't be much use at all to anybody but me right now because the location where it searches for the Matlab output is currently hardcoded in for my ease. This will change when I ship the GUI. The decryption functionality is being tested and it will be added soon so the app can spit out the plaintext, also support for lowercase text. Making a downloadable binary available.
* **28/03/18** - Now printing the decrypted plaintext to the shell. I am going to try and implement a trained model that can take a string and insert spaces into the semantically correct positions. 
* **06/04/18** - After a small battle with PHP and Nginx I have deployed the application to AWS with a very basic web front end. Right now it's just hosted in an EC2 container [here](http://vigenerevictory.ajze.co.uk), but I am going to build it as a Node addon module tomorrow so it can be deployed to AWS Lambda and API Gateway for comparison. Basic source is in the `website` directory. I need to add some information and input checking to the page at some point but for now this will be all I am going to do on this hobby project for some time because I have real work to do! 
* **13/04/18** - I found myself with a free afternoon and ended up having a first try at the augmented reality addon to the project. It took a while but I finished with a very rough working prototype, laying the groundwork for if I decide to revisit this at some point in the future. One issue I have, (brought about by the terrible framerate the open source screen recorder left me with) was that the character recognition of the printout, subsequent cryptanalysis, and creation of a result image happens faster than the time needed to render an updated frame to the webcam window. This means until I add in a pause or loading animation of some description, you never actually see the ciphertext as it appears on the page before it gets cryptanalysed. I'm keeping the source for this AR element closed for the time being because although it's only mediocre right now, a future derivation of it has the potential to be commercially useful in upcoming professional project. If it transpires that isn't the case I will dump it into this repo.
[![VigenereVictoryARTest](https://raw.githubusercontent.com/ajze/vigenere-victory/master/uml/yt_link.png)](https://youtu.be/NQ-n_qV14PQ)

## How to Use
* You can either visit [this](http://vigenerevictory.ajze.co.uk) link or:
* Build the project via Cmake (tested and working with GCC7 and Clang-5) or:
* Download the [Linux](https://work.jonze.uk/wp-content/uploads/2018/02/Linux.zip) or [macOS](https://work.jonze.uk/wp-content/uploads/2018/02/macOS.zip) binary.
* Run the application via the command line with `./VigenereVictory`
* To prep a test message I have been using:
  * [This](https://www.browserling.com/tools/remove-punctuation) to remove all punctuation from a message.
  * [This](https://www.browserling.com/tools/remove-all-whitespace) to remove all the whitespace from a message.
  * [This](https://convertcase.net/) to convert the message to upper case.
  * And finally, [this](https://www.dcode.fr/vigenere-cipher) to encode the message with a key.
  * (I am going to write a script to perform all of the above during my next session.)
* Paste the ciphertext string in at the prompt and you should finish with something like this:

![alt text](https://work.jonze.uk/wp-content/uploads/2018/02/Screenshot-from-2018-03-28-18-50-31.png)

* The reason for enforcing monocase strings with no numbers at this time is that I wanted to authentically replicate the types of messages that the Vigenère Cipher and other polyalphabetic ciphers would have been used for in the times of Giovan Battista Bellaso, the cipher's originator, (and not Blaise de Vigenère!). Numbers and whitespace were considered to convey too much derivable context to an informed interceptor, even before cryptanalysis on the message had begun. To safely include them, it would have also necessitated revisions to Johannes Trithemius' widely accepted [tabula recta](https://en.wikipedia.org/wiki/Tabula_recta#Trithemius_cipher), from which the Vigenère cipher is based.
  

## High Level Plan and Priorities

## Background
There are many decent histories and explanations of the the Vigenere cipher so it is not worth me creating another one. I will link to a selection of the best resources.


