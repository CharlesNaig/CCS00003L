#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <unistd.h>
#endif

// Use these names with cout. Redirected output uses plain text.
inline const char* BLUE = "";
inline const char* CYAN = "";
inline const char* GREEN = "";
inline const char* YELLOW = "";
inline const char* BOLD = "";
inline const char* RESET = "";

class TerminalStyle {
public:
    TerminalStyle() {
#ifdef _WIN32
        output = GetStdHandle(STD_OUTPUT_HANDLE);
        terminalControl = GetConsoleMode(output, &originalMode)
            && SetConsoleMode(output, originalMode | ENABLE_PROCESSED_OUTPUT
                                       | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#else
        const char* terminal = std::getenv("TERM");
        terminalControl = isatty(STDOUT_FILENO) && terminal != nullptr
            && std::string(terminal) != "dumb";
#endif
        const bool useColors = terminalControl && std::getenv("NO_COLOR") == nullptr;
        BLUE = useColors ? "\x1b[97;44m" : "";
        CYAN = useColors ? "\x1b[30;106m" : "";
        GREEN = useColors ? "\x1b[30;102m" : "";
        YELLOW = useColors ? "\x1b[30;103m" : "";
        BOLD = useColors ? "\x1b[1m" : "";
        RESET = useColors ? "\x1b[0m" : "";
    }

    ~TerminalStyle() {
#ifdef _WIN32
        if (terminalControl) {
            std::cout.flush();
            SetConsoleMode(output, originalMode);
        }
#endif
    }

    void clearScreen() const {
        if (terminalControl) {
            std::cout << "\x1b[2J\x1b[H" << std::flush;
        }
    }

    void heading(const std::string& title) const {
        std::cout << "\n" << BLUE << "  " << title << RESET << "\n\n";
    }

    void optionNumber(int number) const {
        std::cout << CYAN << '[' << number << ']' << RESET << ' ';
    }

    void option(int number, const std::string& label) const {
        optionNumber(number);
        std::cout << label << '\n';
    }

private:
    bool terminalControl = false;
#ifdef _WIN32
    HANDLE output = INVALID_HANDLE_VALUE;
    DWORD originalMode = 0;
#endif
};
