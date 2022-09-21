#include <iostream>
#include <string>
//#include <array>

using namespace std;

int program();
int stmts();
int stmt();
int primary();
int primary_tail();
string input;
int i = 0;
string array[100];
int ind = 0;

int main() {
    while (cin >> input) {
        int n = program();
        if (n == 0) {
        }
        else {
            for (int k = 0; k < ind; k++) {
                cout << array[k] << "\n";
            }
        }
        i = 0;
        ind = 0;
        string array[100];
    }
    return 0;
}

int program() {
    int n = stmts();
    if (n == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

int stmts() {
    if ((input[i] >= 65 && input[i] <= 90) ||
        (input[i] >= 97 && input[i] <= 122) || input[i] == 95 ||
        (input[i] >= 48 && input[i] <= 57) || input[i] == 46 ||
        input[i] == 40 || input[i] == 34) {
        int n = stmt();
        if (i >= input.length() && n == 1) {
            return 1;
        }
        else if (n == 0) {
            return 0;
        }
        int m = stmts();
        if (n == 0 || m == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        if (i >= input.length()) {
            return 1;
        }
        else {
            cout << "invalid input\n";
            return 0;
        }
    }
}

int stmt() {
    int len = input.length();
    if ((input[i] >= 65 && input[i] <= 90) ||
        (input[i] >= 97 && input[i] <= 122) ||
        (input[i] >= 48 && input[i] <= 57) || input[i] == 95) {
        int n = primary();
        if (n == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else if (input[i] == 34) {
        string strlit = "\"";
        i = i + 1;
        while (input[i] != 34) {
            if (i >= input.length()) {
                cout << "invalid input\n";
                return 0;
            }
            strlit += input[i];
            i += 1;
        }
        strlit += "\"";
        strlit = "STRLIT " + strlit;
        i += 1;
        array[ind] = strlit;
        ind += 1;
        return 1;
    }
    else {
        if (i >= input.length()) {
            return 1;
        }
        else {
            cout << "invalid input\n";
            return 0;
        }
    }
}

int primary() {
    string ID = "ID ";
    if (input[i] <= 48 || input[i] >= 57) {
        while (input[i] != 40 && input[i] != 46 && (i < input.length())) {
            if ((input[i] >= 65 && input[i] <= 90) ||
                (input[i] >= 97 && input[i] <= 122) ||
                (input[i] >= 48 && input[i] <= 57) || input[i] == 95) {
                ID += input[i];
                i += 1;
                // cout << i;
            }
            else {
                cout << "invalid input\n";
                return 0;
            }
        }
        // cout << i << input.length();
        array[ind] = ID;
        ind += 1;
        if (i >= input.length()) {
            return 1;
        }
        int n = primary_tail();
        if (n == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        cout << "invalid input\n";
        return 0;
    }
}

int primary_tail() {
    if (input[i] == 46) {
        array[ind] = "DOT .";
        ind += 1;
        i = i + 1;
        if (input[i] <= 65 ||
            (input[i] >= 90 && input[i] <= 97 && input[i] != 95) ||
            input[i] >= 122) {
            cout << "invalid input\n";
            return 0;
        }
        else {
            string ID = "ID ";
            if (input[i] <= 48 || input[i] >= 57) {
                while (input[i] != 40 && input[i] != 46 &&
                       (i < input.length())) {
                    if ((input[i] >= 65 && input[i] <= 90) ||
                        (input[i] >= 97 && input[i] <= 122) ||
                        (input[i] >= 48 && input[i] <= 57) || input[i] == 95) {
                        ID += input[i];
                        i += 1;
                        // cout << i;
                    }
                    else {
                        cout << "invalid input\n";
                        return 0;
                    }
                }
                // cout << i << input.length();
                array[ind] = ID;
                ind += 1;
                if (i >= input.length()) {
                    return 1;
                }
                int n = primary_tail();
                if (n == 0) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
        }
    }
    else if (input[i] == 40) {
        array[ind] = "LBR (";
        ind += 1;
        i += 1;
        if (input[i] != 41) {
            stmt();
        }
        array[ind] = "RBR )";
        ind += 1;
        i += 1;
        int n = primary_tail();
        if (n == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        if (i >= input.length()) {
            return 1;
        }
        else {
            cout << "invalid input\n";
            return 0;
        }
    }
}