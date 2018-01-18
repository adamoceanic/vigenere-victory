#include <string>

using std::string;

class Input_Impl {

    int test_data = 10;
    string input_data = "MATLAB_CONNECTION";

public:
    bool HasInput();
    int GetTestData();
    string GetInput();
};
