#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class TextEditor {
    private:
        vector<string> lines; // stores lines of text in a dynamic array
        string currentFileName;
        bool isModified;
    public:

    TextEditor();


    // file ops
    bool loadFile(const string& filename);
    bool saveFile();
    bool saveFileAs(const string& filename);

    // text Ops
    void displayContent() const;
    void displayLine(int lineNumber) const;
    void displayStats() const;

    // edit Ops
    void insertLine(int position, const string& content);
    void deleteLine(int lineNumber);
    void ModifyLine(int lineNumber, const string& newContent);

    // utility Ops
    int getTotalLines() const;
    bool hasUnsavedChanges() const;
    string getCurrentFileName() const;
    void clearBuffer();

    // validation 
    bool isValidLineNumber(int lineNumber) const;
};

#endif