#include "Vigenere_Impl.h"

#include <memory>
#include <thread>
#include <chrono>
#include <iostream>

#include "src/Lib1/Input.h"
#include "src/Lib1/VigenereDecipherer.h"

using std::make_unique;
using std::cout;
using std::endl;


void Vigenere_Impl::Start() {

    input_manager_->Start();

    // think of better control
    while (true) {
        cout << "Listening for MATLAB inputs" << endl;
        if (input_manager_->HasCiphertext()) {
            /*
             * Do the things
             */
            string cipher_text = input_manager_->GetCiphertext();
            vigenere_decipherer_->Decipher(cipher_text);
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        /*
         * returns key length and suggestions, other meta data
         */
        /*
         * Best Guess, text analysis etc
         */
        /*
         * output text then AR to screen
         */
    }


}

Vigenere_Impl::Vigenere_Impl()
        : input_manager_{ make_unique<Input>() },
          vigenere_decipherer_{ make_unique<VigenereDecipherer>() } {

}

Vigenere_Impl::~Vigenere_Impl() = default;