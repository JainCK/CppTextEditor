#include "TextEditor.h"
#include "UI.h"
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
    UI::loadingAnimation("Loading file: ", 2000);
    ifstream file(filename);

    if(!file.is_open()){
        UI::showError("Could not open file '" + filename + "'");
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

    UI::showSuccess("File '" + filename + "' loaded successfully! " + to_string(lines.size()) + " lines read.");

    return true;
}

bool TextEditor::saveFile() {
    if(currentFileName.empty()) {
        UI::showError("No filename specified. Use 'saveas' command.");
        return false;
    }

    return saveFileAs(currentFileName);

    
}

bool TextEditor::saveFileAs(const string& filename) {
    UI::loadingAnimation("Saving file", 800);
    ofstream file(filename);

    if(!file.is_open()) {
        UI::showError("Could not create/write to file '" + filename + "'");
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

    UI::showSuccess("File saved as '" + filename + "'! " + to_string(lines.size()) + " lines written.");

    return true;
}

void TextEditor::displayContent() const {
    if (lines.empty()) {
        UI::showBox("📝 Empty file - start typing to add content!", UI::Colors::YELLOW);
        return;
    }

    UI::showLineNumbers(lines, 1);
}

void TextEditor::displayLine(int lineNumber) const {
    if(!isValidLineNumber(lineNumber)) {
        UI::showError("Invalid line number '" + to_string(lineNumber)+ "'");
        
        return;
    }

    int index = lineNumber - 1;
    cout << UI::Colors::BRIGHT_BLUE << "Line " << lineNumber << ": " 
         << UI::Colors::BRIGHT_WHITE << lines[index] << UI::Colors::RESET << endl;
}

void TextEditor::displayStats() const {
    UI::showFileStats(currentFileName, lines.size(), isModified);
}

void TextEditor::insertLine(int position, const string& content) {
    if(position < 1 || position > static_cast<int>(lines.size()) + 1) {
        UI::showError("Invalid position " + to_string(position) + ". Valid range: 1-" + to_string(lines.size() + 1));
        return;
    }

    int index = position - 1; // Convert to zero-based index

    lines.insert(lines.begin() + index, content);
    isModified = true;

    UI::showSuccess("Line inserted at position " + to_string(position));
}

void TextEditor::deleteLine(int lineNumber) {
    if(isValidLineNumber(lineNumber)) {
        UI::showError("Invalid line number " + to_string(lineNumber));
        return;
    }

    int index = lineNumber - 1; // Convert to zero-based index

    UI::showInfo("Deleting line " + to_string(lineNumber) + ": " + lines[index]);
    lines.erase(lines.begin() + index);

    isModified = true;
    UI::showSuccess("Line " + to_string(lineNumber) + " deleted successfully.");
}

void TextEditor::ModifyLine(int lineNumber, const string& newContent) {
    if(!isValidLineNumber(lineNumber)) {
        UI::showError("Invalid line number " + to_string(lineNumber));
        return;
    }

    int index = lineNumber - 1; // Convert to zero-based index

    UI::showInfo("Modifying line " + to_string(lineNumber) + ": " + lines[index]);
    lines[index] = newContent;

    isModified = true;
    UI::showSuccess("Line " + to_string(lineNumber) + " modified successfully.");
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
    UI::showSuccess("Buffer cleared successfully.");
}

bool TextEditor::isValidLineNumber(int lineNumber) const {
    return lineNumber > 0 && lineNumber <= static_cast<int>(lines.size());
}


