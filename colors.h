// Include this header only once, even if several files reference it.
#pragma once

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

// Compile the terminal setup for the operating system being used.
#ifdef _WIN32
// Prevent Windows macros from interfering with numeric_limits<int>::max().
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <unistd.h>
#endif

// These readable names are used with cout in the main program.
// They start empty and receive color codes only when the terminal supports them.
// RESET ends the current highlight so later text returns to the normal appearance.
inline const char* BLUE = "";
inline const char* CYAN = "";
inline const char* GREEN = "";
inline const char* YELLOW = "";
inline const char* BOLD = "";
inline const char* RESET = "";

// Groups the terminal setup and the shared menu display functions.
class TerminalStyle {
public:
    // The constructor runs when the style object is created in main.
    TerminalStyle() {
#ifdef _WIN32
        // Save the Windows console mode, then enable its terminal-control sequences.
        // If output is redirected to a file or pipe, console setup fails safely.
        output = GetStdHandle(STD_OUTPUT_HANDLE);
        terminalControl = GetConsoleMode(output, &originalMode)
            && SetConsoleMode(output, originalMode | ENABLE_PROCESSED_OUTPUT
                                       | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#else
        // On other systems, require an interactive terminal that supports control sequences.
        const char* terminal = std::getenv("TERM");
        terminalControl = isatty(STDOUT_FILENO) && terminal != nullptr
            && std::string(terminal) != "dumb";
#endif
        // NO_COLOR allows colors to be disabled while keeping menu clearing available.
        // The codes below set the text and background colors of each highlight.
        const bool useColors = terminalControl && std::getenv("NO_COLOR") == nullptr;
        BLUE = useColors ? "\x1b[1;38;2;243;248;255;48;2;22;54;94m" : "";
        CYAN = useColors ? "\x1b[1;38;2;14;60;71;48;2;205;239;247m" : "";
        GREEN = useColors ? "\x1b[1;38;2;13;66;43;48;2;209;250;229m" : "";
        YELLOW = useColors ? "\x1b[1;38;2;110;57;16;48;2;255;241;204m" : "";
        BOLD = useColors ? "\x1b[1m" : "";
        RESET = useColors ? "\x1b[0m" : "";
    }

    // The destructor runs as main ends and restores the original Windows console mode.
    ~TerminalStyle() {
#ifdef _WIN32
        if (terminalControl) {
            std::cout.flush();
            SetConsoleMode(output, originalMode);
        }
#endif
    }

    // Erase the visible screen and move the cursor to the top-left corner.
    // flush sends the command immediately. Redirected output receives no clearing codes.
    void clearScreen() const {
        if (terminalControl) {
            std::cout << "\x1b[2J\x1b[H" << std::flush;
        }
    }

    // Print a blue heading bar. With colors enabled, pad it to at least 46 characters.
    void heading(const std::string& title) const {
        std::cout << '\n' << BLUE;
        if (BLUE[0] != '\0') {
            std::cout << std::left << std::setw(46);
        }
        std::cout << ("  " + title) << RESET << "\n\n";
    }

    // Highlight only the option number, such as [1], then reset the text style.
    void optionNumber(int number) const {
        std::cout << CYAN << '[' << number << ']' << RESET << ' ';
    }

    // Print a complete menu option using its number and a normal-text label.
    void option(int number, const std::string& label) const {
        optionNumber(number);
        std::cout << label << '\n';
    }

private:
    // Remember whether control sequences can be sent to this output device.
    bool terminalControl = false;
#ifdef _WIN32
    HANDLE output = INVALID_HANDLE_VALUE;
    // Keep the previous Windows settings so the destructor can restore them.
    DWORD originalMode = 0;
#endif
};
