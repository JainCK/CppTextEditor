#include "TextEditor.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

void showHelp() {
    cout << "\n=== Text Editor Commands ===" << endl;
    cout << "load <filename>     - Load a file" << endl;
    cout << "save               - Save current file" << endl;
    cout << "saveas <filename>  - Save as new file" << endl;
    cout << "show               - Display all content" << endl;
    cout << "line <number>      - Display specific line" << endl;
    cout << "insert <pos> <text> - Insert line at position" << endl;
    cout << "delete <number>    - Delete line" << endl;
    cout << "modify <number>    - Modify existing line" << endl;
    cout << "stats              - Show editor statistics" << endl;
    cout << "clear              - Clear all content" << endl;
    cout << "help               - Show this help" << endl;
    cout << "quit               - Exit editor" << endl;
    cout << "===========================" << endl;
}

string getRestOFLine(const string& input, const string& command) {
    size_t pos = input.find(command);
    if(pos != string::npos) {
        pos += command.length();

        while (pos < input.length() && isspace(input[pos])){
            pos++;
        }
        return input.substr(pos);
    }
    return "";
}

void parseAndExecuteCommand(const string& input, TextEditor& editor){
    if(input.empty()){
        return;
    }

    istringstream iss(input);
    string command;
    iss >> command;

    transform(command.begin(), command.end(), command.begin(), ::tolower);

    if(command == "help" || command == "h") {
        showHelp();

    } 
    else if (command == "load") {
        string filename;
        iss >> filename;
        if(filename.empty()){
            cout << "Usage: load <filename>" << endl;
        } else {
            editor.loadFile(filename);
        }
    } 
    else if( command == "save"){
        editor.saveFile();
    }
    else if(command == "saveas"){
        string filename;
        iss >> filename;
        if(filename.empty()){
            cout << "Usage: saveas <filename>" << endl;
        } else {
            editor.saveFileAs(filename);
        }
    }
    else if(command == "show" || command == "display"){
        editor.displayContent();
    }
    else if (command == "line") {
        int lineNumber;
        if (iss >> lineNumber) {
            editor.displayLine(lineNumber);
        } else {
            cout << "Usage: line <number>" << endl;
        }
    }
    else if (command == "insert") {
        int position;
        if(iss >> position){
            string content = getRestOFLine(input, "insert");
            istringstream contentStream(content);
            string posStr;
            contentStream >> posStr;
            getline(contentStream, content);

            size_t start = content.find_first_not_of(" \t");
            if(start != string::npos) {
                content = content.substr(start);
            }

            editor.insertLine(position, content);

        } else {
            cout << "Usage: insert <pos> <text>" << endl;
        }
    }
    else if (command == "delete" || command == "del") {
        int lineNumber;
        if(iss >> lineNumber) {
            editor.deleteLine(lineNumber);
        } else {
            cout << "Usage: delete <number>" << endl;
        }
    }
    else if (command == "modify" || command == "mod") {
        int lineNumber;
        if (iss >> lineNumber) {
            cout << "Enter new content for line " << lineNumber << ": ";
            string newContent;
            getline(cin, newContent);
            editor.ModifyLine(lineNumber, newContent);
        } else {
            cout << "Usage: modify <line_number>" << endl;
        }
    }
    else if (command == "stats" || command == "info") {
        editor.displayStats();
    }
    else if (command == "clear") {
        editor.clearBuffer();
    }
    else if (command == "quit" || command == "exit" || command == "q") {
        if (editor.hasUnsavedChanges()) {
            cout << "Warning: You have unsaved changes!" << endl;
            cout << "Are you sure you want to quit? (y/n): ";
            string confirm;
            getline(cin, confirm);
            if (confirm == "y" || confirm == "Y" || confirm == "yes") {
                cout << "Goodbye!" << endl;
                exit(0);
            }
        } else {
            cout << "Goodbye!" << endl;
            exit(0);
        }
    }
    else {
        cout << "Unknown command: " << command << endl;
        cout << "Type 'help' for available commands." << endl;
    }
}

int main() {
    TextEditor editor;
    string input;

    cout << "=== Welcome to this simple text editor! ===" << endl;
    cout << "Type 'help' for available commands." << endl;

    while(true) {
        cout << "\nEditor> ";
        getline(cin, input);

        parseAndExecuteCommand(input, editor);
    }

    return 0;
}