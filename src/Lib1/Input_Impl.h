#include <string>

using std::string;

class Input_Impl {
private:
    int test_data = 10;
    string input_data = "MATLAB_CONNECTION";

public:
    bool HasInput();
    int GetTestData();
    string GetInput();
};
