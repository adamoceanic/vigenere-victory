#include "Vigenere_Impl.h"

#include <memory>
using std::make_unique;

#include <thread>

#include <chrono>

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "src/Lib1/Input.h"
#include "src/Lib1/VigenereDecipherer.h"
#include "src/Lib1/MessageBorderer.h"
#include "src/Lib1/VigenereSquare.h"


using namespace std::chrono;

// ===================================================
// PUBLIC MEMBER FUNCS

void Vigenere_Impl::Start(string flag /*"= --cmd"*/) {

    if (flag == "--cmd") {
        MessageBorderer::print(welcome_message_);

        string cipher_text;

        while(true) {
            cout << "ciphertext (enter q to quit) >> ";
            getline(cin, cipher_text, '\n');
            if (cipher_text == string{'q'}) {
                break;
            }

            if (cipher_text.length() < 800) {
                cout << "ciphertexts of length less than 800 have not been fully tested yet!" << '\n';
            }
            else {

                auto t1 = std::chrono::high_resolution_clock::now();

                auto[key, key_length] = vigenere_decipherer_->Decipher(cipher_text);
                auto plain_text = VigenereSquare::decrypt(cipher_text, key);

                auto t2 = std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(t2 - t1).count();

                cout << "---------------------------------------------------" << '\n';
                cout << "Key: " << key << ", Key length: " << key_length << '\n'
                     << cipher_text.length() << " characters decrypted in " << duration << " ms" << '\n'
                     << '\n'
                     << "plaintext >>" << '\n'
                     << plain_text << '\n'
                     << "Incorrect? Please let me know!" << '\n'
                     << endl;
                cout << "---------------------------------------------------" << '\n';
            }
        }
    }
    else { // --matlab passed

        // Start listening for MATLAB inputs
        input_manager_->Start();

        // for CI testing
        int count = 0;

        while (true) {
            cout << "Listening for MATLAB inputs" << endl;

            if (input_manager_->HasCiphertext()) {

                auto t1 = high_resolution_clock::now();

                string cipher_text = input_manager_->GetCiphertext();

                if (cipher_text.size() < 500) {
                    cout << "CIPHERTEXT TOO SHORT" << '\n';
                    break;
                }

                cout << "CIPHERTEXT RECEIVED: " << '\n';

                auto [key, key_length] = vigenere_decipherer_->Decipher(cipher_text);
                auto plain_text = VigenereSquare::decrypt(cipher_text, key);

                auto t2 = high_resolution_clock::now();

                cout << "likely key: " << key << ", likely key length: " << key_length << '\n';

                auto duration = duration_cast<milliseconds>(t2 - t1).count();

                cout << "time: " << duration  << " ms: " << '\n';

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
}
// ===================================================

// ===================================================
// CTORS DTORS OPTORS

Vigenere_Impl::Vigenere_Impl()
        : input_manager_{ make_unique<Input>() },
          vigenere_decipherer_{ make_unique<VigenereDecipherer>() } {
}

Vigenere_Impl::~Vigenere_Impl() = default;
