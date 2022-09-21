#include <iostream>
#include <string>

using namespace std;

int main() {
    string input;
    while (cin >> input) {
        int i = 0;
        while (i < input.length()) {
            if (input[i] >= 48 && input[i] <= 58) {
                string num = "";
                while (input[i] >= 48 && input[i] <= 58) {
                    num += input[i];
                    i += 1;
                }
                cout << "NUM " << num << "\n";
            }
            else if (input[i] == 43) {
                cout << "PLUS\n";
                i += 1;
            }
            else if (input[i] == 45) {
                cout << "MINUS\n";
                i += 1;
            }
            else if (input[i] == 42) {
                cout << "MUL\n";
                i += 1;
            }
            else if (input[i] == 47) {
                cout << "DIV\n";
                i += 1;
            }
            else if (input[i] == 40) {
                cout << "LPR\n";
                i += 1;
            }
            else if (input[i] == 41) {
                cout << "RPR\n";
                i += 1;
            }
        }
    }
    return 0;
}