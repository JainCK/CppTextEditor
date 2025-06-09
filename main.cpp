#include "TextEditor.h"
#include "UI.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

void showHelp() {
    UI::showHelpMenu();
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
            UI::showError("Usage: load <filename>");
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
            UI::showError("Usage: saveas <filename>");
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
            UI::showError("Usage: line <number>");
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
            UI::showError("Usage: insert <pos> <text>");
        }
    }
    else if (command == "delete" || command == "del") {
        int lineNumber;
        if(iss >> lineNumber) {
            editor.deleteLine(lineNumber);
        } else {
            UI::showError("Usage: delete <number>");
        }
    }
    else if (command == "modify" || command == "mod") {
        int lineNumber;
        if (iss >> lineNumber) {
            cout << UI::Colors::BRIGHT_YELLOW << "Enter new content for line " << lineNumber << ": " << UI::Colors::RESET;
            string newContent;
            getline(cin, newContent);
            editor.ModifyLine(lineNumber, newContent);
        } else {
            UI::showError("Usage: modify <line_number>");
        }
    }
    else if (command == "stats" || command == "info") {
        editor.displayStats();
    }
    else if (command == "clear") {
        if(UI::getYesNoInput("Are you sure you want to clear all content?")) {
            editor.clearBuffer();
        }
    }
    else if (command == "menu") {
        UI::showMainMenu();
    }
    else if (command == "quit" || command == "exit" || command == "q") {
        if (editor.hasUnsavedChanges()) {
            UI::showWarning("You have unsaved changes!");
            if(UI::getYesNoInput("Are you sure you want to quit?")) {
                UI::showGoodbyeScreen();
                exit(0);
            }
        } else {
            UI::showGoodbyeScreen();
            exit(0);
        }
    }
    else {
        UI::showError("Unknown command: " + command);
        UI::showInfo("Type 'help' for available commands");
    }
}

int main() {
    TextEditor editor;
    string input;

    // Show enhanced welcome screen
    UI::showWelcomeScreen();
    UI::showMainMenu();

    while(true) {
        UI::showCommandPrompt(editor.getCurrentFileName(), editor.hasUnsavedChanges());
        getline(cin, input);

        parseAndExecuteCommand(input, editor);
    }

    return 0;
}