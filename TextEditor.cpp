#include "TextEditor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

TextEditor::TextEditor() : isModified(false) {
    lines.clear();
    currentFileName = "";
}

bool TextEditor::loadFile(const string& filename) {
    ifstream file(filename);

    if(!file.is_open()){
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    lines.clear();

    string line;
    while(getline(file, line)){
        lines.push_back(line);
    }

    file.close();

    currentFileName = filename;
    isModified = false;

    cout << "File loaded successfully: " << filename << " " <<lines.size() << " lines read." << endl; 

    return true;
}

bool TextEditor::saveFile() {
    if(currentFileName.empty()) {
        cerr << "Error: No file loaded. Please use 'saveas' to specify a filename." << endl;
        return false;
    }

    return saveFileAs(currentFileName);

    
}

bool TextEditor::saveFileAs(const string& filename) {
    ofstream file(filename);
    if(!file.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return false;
    }

    for(size_t i = 0; i< lines.size(); i++) {
        file << lines[i];

        if(i <lines.size()-1){
            file <<endl;
        }
    }

    file.close();
    
    currentFileName = filename;
    isModified = false;

    cout << "File saved successfully: " << filename << " "<< lines.size() << " lines written." << endl;

    return true;
}

void TextEditor::displayContent() const {
    if (lines.empty()) {
        cout << "[Empty file]" << endl;
        return;
    }

    cout <<"\n======Content of " << currentFileName << "======\n";
    for(size_t i = 0; i < lines.size(); i++) {
        cout << setw(4) << (i+1) << ": " << lines[i] << endl;
    }

    cout << "========================\n";
}

void TextEditor::displayLine(int lineNumber) const {
    if(!isValidLineNumber(lineNumber)) {
        cerr << "Error: Invalid line number " << lineNumber << endl;
        return;
    }

    int index = lineNumber - 1;
    cout << "Line " << lineNumber << ": " << lines[index] << endl;
}

void TextEditor::displayStats() const {
    cout << "\n======Editor Statistics======\n" << endl;
    cout << "current File: " << (currentFileName.empty() ? "[New file]" : currentFileName) << endl;
    cout << "Total lines: " << lines.size() << endl;
    cout << "Nodified: " << (isModified ? "Yes" : "No") << endl;
    cout << "=============================\n" << endl;
}

void TextEditor::insertLine(int position, const string& content) {
    if(position < 1 || position > static_cast<int>(lines.size()) + 1) {
        cerr << "Error: Invalid position " << position << ". Valid range: 1-" << (lines.size() + 1) << endl;
        return;
    }

    int index = position - 1; // Convert to zero-based index

    lines.insert(lines.begin() + index, content);
    isModified = true;

    cout << "Line inserted at position " << position << endl;
}

void TextEditor::deleteLine(int lineNumber) {
    if(isValidLineNumber(lineNumber)) {
        cerr << "Error: Invalid line number " << lineNumber << endl;
        return;
    }

    int index = lineNumber - 1; // Convert to zero-based index

    cout << "Deleting line " << lineNumber << ": " << lines[index] << endl;
    lines.erase(lines.begin() + index);

    isModified = true;
    cout << "Line " << lineNumber << " deleted successfully." << endl;
}

void TextEditor::ModifyLine(int lineNumber, const string& newContent) {
    if(!isValidLineNumber(lineNumber)) {
        cerr << "Error: Invalid line number " << lineNumber << endl;
        return;
    }

    int index = lineNumber - 1; // Convert to zero-based index

    cout << "Modifying line " << lineNumber << ": " << lines[index] << endl;
    lines[index] = newContent;

    isModified = true;
    cout << "Line " << lineNumber << " modified successfully." << endl;
}

int TextEditor::getTotalLines() const {
    return static_cast<int>(lines.size());
}

bool TextEditor::hasUnsavedChanges() const {
    return isModified;
}

string TextEditor::getCurrentFileName() const {
    return currentFileName;
}

void TextEditor::clearBuffer() {
    lines.clear();
    currentFileName = "";
    isModified = false;
    cout << "Buffer cleared." << endl;
}

bool TextEditor::isValidLineNumber(int lineNumber) const {
    return lineNumber > 0 && lineNumber <= static_cast<int>(lines.size());
}
