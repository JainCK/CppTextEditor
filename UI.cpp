#include "UI.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ranges>
#include <algorithm>

namespace UI {
    
    void showWelcomeScreen() {
        clearScreen();
        std::cout << Colors::BRIGHT_CYAN << Colors::BOLD;
        
        // ASCII Art Title
        std::cout << R"(
    ████████╗███████╗██╗  ██╗████████╗    ███████╗██████╗ ██╗████████╗ ██████╗ ██████╗ 
    ╚══██╔══╝██╔════╝╚██╗██╔╝╚══██╔══╝    ██╔════╝██╔══██╗██║╚══██╔══╝██╔═══██╗██╔══██╗
       ██║   █████╗   ╚███╔╝    ██║       █████╗  ██║  ██║██║   ██║   ██║   ██║██████╔╝
       ██║   ██╔══╝   ██╔██╗    ██║       ██╔══╝  ██║  ██║██║   ██║   ██║   ██║██╔══██╗
       ██║   ███████╗██╔╝ ██╗   ██║       ███████╗██████╔╝██║   ██║   ╚██████╔╝██║  ██║
       ╚═╝   ╚══════╝╚═╝  ╚═╝   ╚═╝       ╚══════╝╚═════╝ ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝
)" << std::endl;
        
        std::cout << Colors::RESET;
        std::cout << Colors::BRIGHT_YELLOW << centerText("✨ Welcome to the Enhanced Text Editor! ✨") << Colors::RESET << std::endl;
        std::cout << Colors::DIM << centerText("A modern, colorful, and user-friendly terminal text editor") << Colors::RESET << std::endl;
        
        showSeparator('─', 80);
        
        std::cout << Colors::GREEN << "🚀 " << Colors::BOLD << "Getting Started:" << Colors::RESET << std::endl;
        std::cout << Colors::BRIGHT_WHITE << "  • Type " << Colors::CYAN << "'help'" << Colors::BRIGHT_WHITE 
                  << " to see all available commands" << std::endl;
        std::cout << Colors::BRIGHT_WHITE << "  • Type " << Colors::CYAN << "'load filename'" << Colors::BRIGHT_WHITE 
                  << " to open a file" << std::endl;
        std::cout << Colors::BRIGHT_WHITE << "  • Type " << Colors::CYAN << "'quit'" << Colors::BRIGHT_WHITE 
                  << " to exit the editor" << std::endl;
        
        showSeparator('─', 80);
        std::cout << std::endl;
    }
    
    void showGoodbyeScreen() {
        clearScreen();
        std::cout << Colors::BRIGHT_MAGENTA << Colors::BOLD;
        
        std::cout << R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                                                               ║
    ║    ████████╗██╗  ██╗ █████╗ ███╗   ██╗██╗  ██╗███████╗       ║
    ║    ╚══██╔══╝██║  ██║██╔══██╗████╗  ██║██║ ██╔╝██╔════╝       ║
    ║       ██║   ███████║███████║██╔██╗ ██║█████╔╝ ███████╗       ║
    ║       ██║   ██╔══██║██╔══██║██║╚██╗██║██╔═██╗ ╚════██║       ║
    ║       ██║   ██║  ██║██║  ██║██║ ╚████║██║  ██╗███████║       ║
    ║       ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝       ║
    ║                                                               ║
    ║           🎉 Thanks for using Text Editor! 🎉                 ║
    ║              Happy coding and writing! ✨                     ║
    ║                                                               ║
    ╚═══════════════════════════════════════════════════════════════╝
)" << std::endl;
        
        std::cout << Colors::RESET << std::endl;
    }
    
    void showHeader(const std::string& title) {
        showSeparator('═', 60);
        std::cout << Colors::BRIGHT_CYAN << Colors::BOLD << "📄 " << title << Colors::RESET << std::endl;
        showSeparator('═', 60);
    }
    
    void showSeparator(char character, int length) {
        std::cout << Colors::DIM;
        for (int i = 0; i < length; ++i) {
            std::cout << character;
        }
        std::cout << Colors::RESET << std::endl;
    }
    
    void showBox(const std::string& content, const std::string& color) {
        int contentLength = content.length();
        int boxWidth = contentLength + 4;
        
        std::cout << color;
        
        // Top border
        std::cout << "┌";
        for (int i = 0; i < boxWidth - 2; ++i) std::cout << "─";
        std::cout << "┐" << std::endl;
        
        // Content
        std::cout << "│ " << content << " │" << std::endl;
        
        // Bottom border
        std::cout << "└";
        for (int i = 0; i < boxWidth - 2; ++i) std::cout << "─";
        std::cout << "┘" << std::endl;
        
        std::cout << Colors::RESET;
    }
    
    void showProgressBar(int current, int total, const std::string& label) {
        const int barWidth = 40;
        float progress = (float)current / total;
        int pos = (int)(barWidth * progress);
        
        std::cout << Colors::BRIGHT_BLUE << label << ": [";
        std::cout << Colors::GREEN;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "█";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << Colors::BRIGHT_BLUE << "] " << (int)(progress * 100.0) << "%" << Colors::RESET << std::endl;
    }
    
    void showSpinner(int duration_ms) {
        const std::string spinChars = "|/-\\";
        auto start = std::chrono::steady_clock::now();
        
        while (std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now() - start).count() < duration_ms) {
            for (char c : spinChars) {
                std::cout << "\r" << Colors::BRIGHT_YELLOW << c << " Processing..." << Colors::RESET << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        std::cout << "\r" << Colors::GREEN << "✓ Complete!    " << Colors::RESET << std::endl;
    }
    
    void typewriterEffect(const std::string& text, int delay_ms) {
        for (char c : text) {
            std::cout << Colors::BRIGHT_GREEN << c << Colors::RESET << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        }
        std::cout << std::endl;
    }
    
    void showSuccess(const std::string& message) {
        std::cout << Colors::GREEN << "✅ " << Colors::BOLD << "SUCCESS: " 
                  << Colors::RESET << Colors::BRIGHT_GREEN << message << Colors::RESET << std::endl;
    }
    
    void showError(const std::string& message) {
        std::cout << Colors::RED << "❌ " << Colors::BOLD << "ERROR: " 
                  << Colors::RESET << Colors::BRIGHT_RED << message << Colors::RESET << std::endl;
    }
    
    void showWarning(const std::string& message) {
        std::cout << Colors::YELLOW << "⚠️  " << Colors::BOLD << "WARNING: " 
                  << Colors::RESET << Colors::BRIGHT_YELLOW << message << Colors::RESET << std::endl;
    }
    
    void showInfo(const std::string& message) {
        std::cout << Colors::BLUE << "ℹ️  " << Colors::BOLD << "INFO: " 
                  << Colors::RESET << Colors::BRIGHT_BLUE << message << Colors::RESET << std::endl;
    }
    
    void showMainMenu() {
        std::cout << Colors::BRIGHT_CYAN << Colors::BOLD << "\n🎯 Quick Actions:" << Colors::RESET << std::endl;
        std::cout << Colors::BRIGHT_WHITE << "┌─────────────────────────────────────────────┐" << std::endl;
        std::cout << "│ " << Colors::GREEN << "📁 load <file>  " << Colors::WHITE << "│ Open a text file        │" << std::endl;
        std::cout << "│ " << Colors::YELLOW << "👁️  show        " << Colors::WHITE << "│ Display all content     │" << std::endl;
        std::cout << "│ " << Colors::MAGENTA << "💾 save        " << Colors::WHITE << "│ Save current file       │" << std::endl;
        std::cout << "│ " << Colors::RED << "🚪 quit        " << Colors::WHITE << "│ Exit the editor         │" << std::endl;
        std::cout << "│ " << Colors::CYAN << "❓ help        " << Colors::WHITE << "│ Show all commands       │" << std::endl;
        std::cout << "└─────────────────────────────────────────────┘" << Colors::RESET << std::endl;
    }
    
    void showHelpMenu() {
        clearScreen();
        showHeader("📚 COMMAND REFERENCE GUIDE");
        
        std::cout << Colors::BRIGHT_YELLOW << "📂 " << Colors::BOLD << "FILE OPERATIONS:" << Colors::RESET << std::endl;
        std::cout << Colors::CYAN << "  load <filename>     " << Colors::WHITE << "- 📂 Load a file into the editor" << std::endl;
        std::cout << Colors::CYAN << "  save               " << Colors::WHITE << "- 💾 Save current file" << std::endl;
        std::cout << Colors::CYAN << "  saveas <filename>  " << Colors::WHITE << "- 📝 Save as new file" << std::endl;
        std::cout << Colors::CYAN << "  clear              " << Colors::WHITE << "- 🗑️  Clear all content" << std::endl;
        
        std::cout << std::endl << Colors::BRIGHT_GREEN << "👁️ " << Colors::BOLD << "DISPLAY OPERATIONS:" << Colors::RESET << std::endl;
        std::cout << Colors::CYAN << "  show               " << Colors::WHITE << "- 📄 Display all content with line numbers" << std::endl;
        std::cout << Colors::CYAN << "  line <number>      " << Colors::WHITE << "- 🔍 Display specific line" << std::endl;
        std::cout << Colors::CYAN << "  stats              " << Colors::WHITE << "- 📊 Show editor statistics" << std::endl;
        
        std::cout << std::endl << Colors::BRIGHT_MAGENTA << "✏️ " << Colors::BOLD << "EDIT OPERATIONS:" << Colors::RESET << std::endl;
        std::cout << Colors::CYAN << "  insert <pos> <text>" << Colors::WHITE << "- ➕ Insert line at position" << std::endl;
        std::cout << Colors::CYAN << "  delete <number>    " << Colors::WHITE << "- ❌ Delete line" << std::endl;
        std::cout << Colors::CYAN << "  modify <number>    " << Colors::WHITE << "- ✏️  Modify existing line" << std::endl;
        
        std::cout << std::endl << Colors::BRIGHT_BLUE << "🛠️ " << Colors::BOLD << "UTILITY:" << Colors::RESET << std::endl;
        std::cout << Colors::CYAN << "  help               " << Colors::WHITE << "- ❓ Show this help menu" << std::endl;
        std::cout << Colors::CYAN << "  quit               " << Colors::WHITE << "- 🚪 Exit the editor" << std::endl;
        
        showSeparator('─', 60);
        std::cout << Colors::BRIGHT_YELLOW << "💡 " << Colors::BOLD << "Tips:" << Colors::RESET << std::endl;
        std::cout << Colors::DIM << "  • Commands are case-insensitive" << std::endl;
        std::cout << Colors::DIM << "  • Line numbers start from 1" << std::endl;
        std::cout << Colors::DIM << "  • Use 'quit' to exit safely with unsaved changes warning" << Colors::RESET << std::endl;
        showSeparator('─', 60);
    }
    
    void showCommandPrompt(const std::string& currentFile, bool hasChanges) {
        std::cout << std::endl;
        std::cout << Colors::BRIGHT_BLUE << "┌─ " << Colors::BOLD << "Text Editor";
        
        if (!currentFile.empty()) {
            std::cout << Colors::RESET << Colors::BRIGHT_BLUE << " [" << Colors::CYAN << currentFile;
            if (hasChanges) {
                std::cout << Colors::RED << "*";
            }
            std::cout << Colors::BRIGHT_BLUE << "]";
        }
        
        std::cout << std::endl << Colors::BRIGHT_BLUE << "└─> " << Colors::BRIGHT_WHITE;
    }
    
    void showFileStats(const std::string& filename, int lines, bool modified) {
        std::cout << std::endl;
        std::cout << Colors::BRIGHT_CYAN << "📊 " << Colors::BOLD << "FILE STATISTICS" << Colors::RESET << std::endl;
        std::cout << Colors::BRIGHT_WHITE << "┌─────────────────────────────────────┐" << std::endl;
        std::cout << "│ " << Colors::YELLOW << "📁 File: " << Colors::WHITE << std::setw(23) << std::left 
                  << (filename.empty() ? "[New file]" : filename) << " │" << std::endl;
        std::cout << "│ " << Colors::GREEN << "📏 Lines: " << Colors::WHITE << std::setw(22) << std::left 
                  << lines << " │" << std::endl;
        std::cout << "│ " << Colors::MAGENTA << "💾 Status: " << Colors::WHITE << std::setw(21) << std::left 
                  << (modified ? "Modified ⚠️" : "Saved ✅") << " │" << std::endl;
        std::cout << "└─────────────────────────────────────┘" << Colors::RESET << std::endl;
    }
    
    void showLineNumbers(const std::vector<std::string>& lines, int startLine) {
        if (lines.empty()) {
            showBox("📝 Empty file - start typing to add content!", Colors::YELLOW);
            return;
        }
        
        std::cout << std::endl;
        showHeader("📄 FILE CONTENT");
        
        for (size_t i = 0; i < lines.size(); ++i) {
            int lineNum = startLine + i;
            
            // Alternate line background for better readability
            if (i % 2 == 0) {
                std::cout << Colors::DIM;
            }
            
            std::cout << Colors::BRIGHT_BLUE << std::setw(4) << std::right << lineNum << " │ " 
                      << Colors::RESET;
            
            if (i % 2 == 0) {
                std::cout << Colors::BRIGHT_WHITE;
            } else {
                std::cout << Colors::WHITE;
            }
            
            std::cout << lines[i] << Colors::RESET << std::endl;
        }
        
        showSeparator('─', 60);
        std::cout << Colors::DIM << "📝 Total lines: " << lines.size() << Colors::RESET << std::endl;
    }
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void moveCursor(int row, int col) {
        std::cout << "\033[" << row << ";" << col << "H";
    }
    
    void hideCursor() {
        std::cout << "\033[?25l";
    }
    
    void showCursor() {
        std::cout << "\033[?25h";
    }
    
    std::string centerText(const std::string& text, int width) {
        int padding = (width - text.length()) / 2;
        return std::string(padding, ' ') + text;
    }
    
    bool getYesNoInput(const std::string& prompt) {
        std::string input;
        while (true) {
            std::cout << prompt << " (y/n): ";
            std::getline(std::cin, input);
            std::transform(input.begin(), input.end(), input.begin(), ::tolower);

            if (input == "y" || input == "yes") {
                return true;
            } else if (input == "n" || input == "no") {
                return false;
            } else {
                std::cout << "Please enter 'y' or 'n'." << std::endl;
            }
        }
    }

    void loadingAnimation(const std::string& message, int duration_ms) {
        const std::vector<std::string> frames = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
        auto start = std::chrono::steady_clock::now();
        int frameIndex = 0;
        
        hideCursor();
        while (std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now() - start).count() < duration_ms) {
            std::cout << "\r" << Colors::BRIGHT_CYAN << frames[frameIndex] << " " 
                      << Colors::BRIGHT_WHITE << message << "..." << Colors::RESET << std::flush;
            
            frameIndex = (frameIndex + 1) % frames.size();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        std::cout << "\r" << Colors::GREEN << "✅ " << Colors::BRIGHT_GREEN 
                  << message << " complete!" << std::string(10, ' ') << Colors::RESET << std::endl;
        showCursor();
    }
}