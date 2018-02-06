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

// ===================================================
// PUBLIC MEMBER FUNCS

void Vigenere_Impl::Start() {

    // Start listening for MATLAB inputs
    input_manager_->Start();

    // for CI testing
    int count = 0;

    while (true) {
        cout << "Listening for MATLAB inputs" << endl;
        if (input_manager_->HasCiphertext()) {
            /*
             * Do the things
             */

            string cipher_text = input_manager_->GetCiphertext();
            //cout << "CIPHERTEXT RECEIVED: " << cipher_text << '\n';
            vigenere_decipherer_->Decipher(cipher_text);
            /*
             * returns key length and suggestions, other meta data
             */
            cout << "SUGGESTION UNIT" << '\n';
            std::this_thread::sleep_for(std::chrono::seconds(5));
            /*
             * Best Guess, text analysis etc
             */
            cout << "AR UNIT" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            /*
             * output text then AR to screen
             */
            input_manager_->SetHasCiphertext(false);
        }
        else {
           std::this_thread::sleep_for(std::chrono::seconds(5));
        }


        ++count;
        if (count >= 10) {
            break;
        }
    }
}
// ===================================================

// ===================================================
// CTORS DTORS OPTORS

Vigenere_Impl::Vigenere_Impl()
        : input_manager_{ make_unique<Input>() },
          vigenere_decipherer_{ make_unique<VigenereDecipherer>() } {
}

Vigenere_Impl::~Vigenere_Impl() = default;