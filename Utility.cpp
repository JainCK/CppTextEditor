#include "Utility.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cctype>
#include <climits>
using namespace std;

namespace Utility {
    string trim(const string& str){
        size_t start = str.find_first_not_of(" \t\n\r");
        if(start == string::npos){
            return "";
        }
        size_t end = str.find_last_not_of(" \t\n\r");
        return str.substr(start, end - start + 1);
    }

    vector<string> split(const string& str, char delimiter){
        vector<string> tokens;
        stringstream ss(str);
        string token;

        while(getline(ss, token, delimiter)){
            tokens.push_back(token);
        }

        return tokens;
    }

    bool isNumber(const string& str){
        if(str.empty()) return false;

        istringstream iss(str);
        double d;
        iss >> noskipws >> d;
        return iss.eof() && !iss.fail();
    }

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
   
    void pauseForInput() {
        cout << "Press Enter to continue...";
        cin.ignore();
    }
    
    
    bool fileExists(const string& filename) {
        ifstream file(filename);
        return file.good();
    }
    
  
    string getFileExtension(const string& filename) {
        size_t pos = filename.find_last_of('.');
        if (pos != string::npos && pos < filename.length() - 1) {
            return filename.substr(pos + 1);
        }
        return "";
    }
    

    bool getYesNoInput(const string& prompt) {
        string input;
        while (true) {
            cout << prompt << " (y/n): ";
            getline(cin, input);
            transform(input.begin(), input.end(), input.begin(), ::tolower);
            
            if (input == "y" || input == "yes") {
                return true;
            } else if (input == "n" || input == "no") {
                return false;
            } else {
                cout << "Please enter 'y' or 'n'." << endl;
            }
        }
    }
    

    int getIntegerInput(const string& prompt, int min, int max) {
        string input;
        int value;
        while (true) {
            cout << prompt;
            if (min != INT_MIN || max != INT_MAX) {
                cout << " (" << min << "-" << max << ")";
            }
            cout << ": ";
            
            getline(cin, input);
            istringstream iss(input);
            if (iss >> value && iss.eof()) {
                if (value >= min && value <= max) {
                    return value;
                } else {
                    cout << "Value must be between " << min << " and " << max << endl;
                }
            } else {
                cout << "Please enter a valid integer." << endl;
            }
        }
    }
}