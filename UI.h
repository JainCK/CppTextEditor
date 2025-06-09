#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


namespace UI {
    // ANSI Color codes
    namespace Colors {
        const std::string RESET = "\033[0m";
        const std::string BOLD = "\033[1m";
        const std::string DIM = "\033[2m";
        const std::string UNDERLINE = "\033[4m";
        
        // Regular colors
        const std::string BLACK = "\033[30m";
        const std::string RED = "\033[31m";
        const std::string GREEN = "\033[32m";
        const std::string YELLOW = "\033[33m";
        const std::string BLUE = "\033[34m";
        const std::string MAGENTA = "\033[35m";
        const std::string CYAN = "\033[36m";
        const std::string WHITE = "\033[37m";
        
        // Bright colors
        const std::string BRIGHT_BLACK = "\033[90m";
        const std::string BRIGHT_RED = "\033[91m";
        const std::string BRIGHT_GREEN = "\033[92m";
        const std::string BRIGHT_YELLOW = "\033[93m";
        const std::string BRIGHT_BLUE = "\033[94m";
        const std::string BRIGHT_MAGENTA = "\033[95m";
        const std::string BRIGHT_CYAN = "\033[96m";
        const std::string BRIGHT_WHITE = "\033[97m";
        
        // Background colors
        const std::string BG_BLACK = "\033[40m";
        const std::string BG_RED = "\033[41m";
        const std::string BG_GREEN = "\033[42m";
        const std::string BG_YELLOW = "\033[43m";
        const std::string BG_BLUE = "\033[44m";
        const std::string BG_MAGENTA = "\033[45m";
        const std::string BG_CYAN = "\033[46m";
        const std::string BG_WHITE = "\033[47m";
    }
    
    // UI Components
    void showWelcomeScreen();
    void showGoodbyeScreen();
    void showHeader(const std::string& title);
    void showSeparator(char character = '=', int length = 60);
    void showBox(const std::string& content, const std::string& color = Colors::CYAN);
    void showProgressBar(int current, int total, const std::string& label = "Progress");
    
    // Interactive elements
    void showSpinner(int duration_ms = 1000);
    void typewriterEffect(const std::string& text, int delay_ms = 50);
    
    // Status and feedback
    void showSuccess(const std::string& message);
    void showError(const std::string& message);
    void showWarning(const std::string& message);
    void showInfo(const std::string& message);
    
    // Menu and help
    void showMainMenu();
    void showHelpMenu();
    void showCommandPrompt(const std::string& currentFile = "", bool hasChanges = false);
    
    // File operations UI
    void showFileStats(const std::string& filename, int lines, bool modified);
    void showLineNumbers(const std::vector<std::string>& lines, int startLine = 1);
    
    // Utility functions
    void clearScreen();
    void moveCursor(int row, int col);
    void hideCursor();
    void showCursor();
    bool getYesNoInput(const std::string& prompt);
    std::string centerText(const std::string& text, int width = 80);
    
    // Animation helpers
    void loadingAnimation(const std::string& message, int duration_ms = 2000);
}

#endif