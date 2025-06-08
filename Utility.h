#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <iostream>
#include <climits>
using namespace std;

namespace Utility {
    // String manipulation helpers
    string trim(const string& str);
    vector<string> split(const string& str, char delimiter);
    bool isNumber(const string& str);
    
    // Console helpers
    void clearScreen();
    void pauseForInput();
    
    // File helpers
    bool fileExists(const string& filename);
    string getFileExtension(const string& filename);
    
    // Input validation helpers
    bool getYesNoInput(const string& prompt);
    int getIntegerInput(const string& prompt, int min = INT_MIN, int max = INT_MAX);
}

#endif