#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>
#include <cstdlib>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

class TerminalStyle {
public:
    TerminalStyle() {
        if (getenv("NO_COLOR") != nullptr) {
            return;
        }

#ifdef _WIN32
        output = GetStdHandle(STD_OUTPUT_HANDLE);
        enabled = GetConsoleMode(output, &originalMode)
            && SetConsoleMode(output, originalMode | ENABLE_PROCESSED_OUTPUT
                                       | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#else
        const char* terminal = getenv("TERM");
        enabled = isatty(STDOUT_FILENO) && terminal != nullptr && string(terminal) != "dumb";
#endif
    }

    ~TerminalStyle() {
#ifdef _WIN32
        if (enabled) {
            cout.flush();
            SetConsoleMode(output, originalMode);
        }
#endif
    }

    void heading(const string& title) const {
        cout << '\n' << color("\x1b[1;38;2;243;248;255;48;2;22;54;94m");
        if (enabled) {
            cout << left << setw(46);
        }
        cout << ("  " + title) << reset() << "\n\n";
    }

    void optionNumber(int number) const {
        cout << color("\x1b[1;38;2;14;60;71;48;2;205;239;247m")
             << '[' << number << ']' << reset() << ' ';
    }

    void option(int number, const string& label) const {
        optionNumber(number);
        cout << label << '\n';
    }

    const char* error() const { return color("\x1b[1;38;2;110;57;16;48;2;255;241;204m"); }
    const char* confirmed() const { return color("\x1b[1;38;2;13;66;43;48;2;209;250;229m"); }
    const char* emphasis() const { return color("\x1b[1m"); }
    const char* reset() const { return color("\x1b[0m"); }

private:
    const char* color(const char* sequence) const { return enabled ? sequence : ""; }

    bool enabled = false;
#ifdef _WIN32
    HANDLE output = INVALID_HANDLE_VALUE;
    DWORD originalMode = 0;
#endif
};

// Read one whole number per prompt. -1 signals end of input.
int readNumber(const TerminalStyle& style, const char* prompt, int minimum,
               int maximum = numeric_limits<int>::max()) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) {
            return -1;
        }

        istringstream input(line);
        int number;
        char extra;
        if (input >> number && !(input >> extra) && number >= minimum && number <= maximum) {
            return number;
        }

        if (minimum == maximum) {
            cout << style.error() << "Invalid choice." << style.reset()
                 << " Enter " << minimum << " to go back.\n";
        } else if (maximum == numeric_limits<int>::max()) {
            cout << style.error() << "Invalid input." << style.reset()
                 << " Enter a whole number of at least " << minimum << ".\n";
        } else {
            cout << style.error() << "Invalid choice." << style.reset()
                 << " Enter a whole number from " << minimum << " to " << maximum << ".\n";
        }
    }
}

int main() {
    const TerminalStyle style;

    const int CATEGORY_COUNT = 5;
    const int SHOW_COUNT = 3;
    const int CUSTOMER_TYPE_COUNT = 4;

    const string categories[CATEGORY_COUNT] = {
        "Concert", "Movies", "Theatre", "Sport Venues", "Attractions"
    };

    const string shows[CATEGORY_COUNT][SHOW_COUNT] = {
        {"Eraserheads Reunion", "SB19 Pagtatag Finale", "Ben&Ben Acoustic Night"},
        {"Final Hour", "The Last Signal", "Campus Haunt"},
        {"Ang Huling El Bimbo", "Rak of Aegis", "Mula sa Buwan"},
        {"PBA Finals Game 7", "UAAP Mens Basketball", "Gilas Pilipinas Qualifier"},
        {"Enchanted Kingdom", "Manila Ocean Park", "National Museum Tour"}
    };

    const double prices[CATEGORY_COUNT][SHOW_COUNT] = {
        {2500.00, 1800.00, 1500.00},
        {300.00, 280.00, 250.00},
        {1200.00, 1000.00, 1100.00},
        {800.00, 500.00, 1000.00},
        {900.00, 700.00, 150.00}
    };

    const string customerTypes[CUSTOMER_TYPE_COUNT] = {
        "Student", "Senior Citizen", "PWD", "None"
    };
    const double discountRates[CUSTOMER_TYPE_COUNT] = {
        0.10, 0.15, 0.10, 0.00
    };
    const string discountNames[CUSTOMER_TYPE_COUNT] = {
        "10%", "15%", "10%", "0%"
    };

    int totalTransactions = 0;
    int totalTicketsSold = 0;
    int currentID = 1000;
    double totalRevenue = 0.0;
    enum class Screen { MainMenu, Categories, Events, CustomerInformation, SalesReport };
    Screen screen = Screen::MainMenu;
    bool booking = false;
    int categoryIndex = 0;
    int showIndex = 0;

    cout << fixed << setprecision(2);

    while (true) {
        if (screen == Screen::MainMenu) {
            style.heading("TICKETMACHINE CLI");
            cout << "  Ticket Kiosk Simulator\n\n";
            style.option(1, "View Available Ticket Categories");
            style.option(2, "Book Tickets");
            style.option(3, "Daily Sales Report");
            style.option(0, "Exit");
            cout << '\n';

            int menuOption = readNumber(style, "Enter Choice: ", 0, 3);
            if (menuOption == -1) {
                break;
            }
            if (menuOption == 0) {
                cout << "\nExiting Ticket Kiosk Simulator. Goodbye!\n";
                break;
            }
            if (menuOption == 3) {
                screen = Screen::SalesReport;
            } else {
                booking = menuOption == 2;
                screen = Screen::Categories;
            }
        } else if (screen == Screen::Categories) {
            style.heading(booking ? "BOOK TICKETS" : "AVAILABLE TICKET CATEGORIES");

            for (int i = 0; i < CATEGORY_COUNT; i++) {
                style.option(i + 1, categories[i]);
            }
            style.option(0, "Back to Main Menu");
            cout << '\n';

            int catChoice = readNumber(style, "Select Ticket Category: ", 0, CATEGORY_COUNT);
            if (catChoice == -1) {
                break;
            }
            if (catChoice == 0) {
                screen = Screen::MainMenu;
            } else {
                categoryIndex = catChoice - 1;
                screen = Screen::Events;
            }
        } else if (screen == Screen::Events) {
            style.heading(categories[categoryIndex] + " LIST");

            for (int i = 0; i < SHOW_COUNT; i++) {
                if (booking) {
                    style.optionNumber(i + 1);
                }
                cout << left << setw(28) << shows[categoryIndex][i]
                     << "PHP " << prices[categoryIndex][i] << "\n";
            }
            style.option(0, "Back to Ticket Categories");
            cout << '\n';

            int showChoice = booking
                ? readNumber(style, "Select Show / Event: ", 0, SHOW_COUNT)
                : readNumber(style, "Enter Choice: ", 0, 0);
            if (showChoice == -1) {
                break;
            }
            if (showChoice == 0) {
                screen = Screen::Categories;
            } else {
                showIndex = showChoice - 1;
                screen = Screen::CustomerInformation;
            }
        } else if (screen == Screen::CustomerInformation) {
            string category = categories[categoryIndex];
            string show = shows[categoryIndex][showIndex];
            double price = prices[categoryIndex][showIndex];

            style.heading("CUSTOMER INFORMATION");
            style.option(0, "Back to Event List");
            cout << "Enter Customer Name (or 0 to go back): ";

            string cName;
            if (!getline(cin >> ws, cName)) {
                break;
            }
            if (cName == "0") {
                screen = Screen::Events;
                continue;
            }

            int cAge = readNumber(style, "Enter Age: ", 0);
            if (cAge == -1) {
                break;
            }

            cout << "\nAre you a student, senior citizen, or PWD?\n";
            for (int i = 0; i < CUSTOMER_TYPE_COUNT; i++) {
                style.option(i + 1, customerTypes[i]);
            }
            style.option(0, "Back to Event List");
            cout << '\n';

            int typeChoice = readNumber(style, "Enter Choice: ", 0, CUSTOMER_TYPE_COUNT);
            if (typeChoice == -1) {
                break;
            }
            if (typeChoice == 0) {
                screen = Screen::Events;
                continue;
            }

            int typeIndex = typeChoice - 1;
            string cType = customerTypes[typeIndex];
            double discountRate = discountRates[typeIndex];
            string discountName = discountNames[typeIndex];

            int qty = readNumber(style, "\nEnter Number of Tickets: ", 1);
            if (qty == -1) {
                break;
            }

            double sub = price * qty;
            double discAmt = sub * discountRate;
            double total = sub - discAmt;
            // VAT is displayed separately and is not added to the total.
            double vat = total * 0.12;
            string bID = "TM" + to_string(currentID);

            style.heading("TICKET COMPUTATION");
            cout << "Selected Show: " << show << "\n";
            cout << "Ticket Type: " << category << "\n";
            cout << "Ticket Price: PHP " << price << "\n";
            cout << "Quantity: " << qty << "\n\n";
            cout << "Subtotal: PHP " << sub << "\n";
            cout << "Discount: " << discountName << "\n";
            cout << "Discount Amount: PHP " << discAmt << "\n";
            cout << "Vat Amount: PHP " << vat << "\n\n";
            cout << style.emphasis() << "TOTAL AMOUNT: PHP " << total << style.reset() << '\n';

            style.heading("PURCHASE RECEIPT");
            cout << "Booking ID: " << bID << "\n";
            cout << "Customer Name: " << cName << "\n";
            cout << "Customer Type: " << cType << "\n\n";
            cout << "----------------------------------------------\n";
            cout << "Ticket Category: " << category << "\n";
            cout << "Selected Show: " << show << "\n";
            cout << "Ticket Price: PHP " << price << "\n";
            cout << "Quantity: " << qty << "\n\n";
            cout << "Subtotal: PHP " << sub << "\n\n";
            cout << "Vat Amount: PHP " << vat << "\n";
            cout << "Discount Amount: PHP " << discAmt << "\n";
            cout << "----------------------------------------------\n";
            cout << style.emphasis() << "Total Amount: PHP " << total << style.reset() << "\n\n";
            cout << "Booking Status: " << style.confirmed() << "CONFIRMED" << style.reset() << "\n\n";
            cout << "Thank you for using Ticket Machine!\n";
            cout << "----------------------------------------------\n";

            totalTransactions++;
            totalTicketsSold += qty;
            totalRevenue += total;
            currentID++;

            cout << '\n';
            style.option(0, "Back to Main Menu");
            if (readNumber(style, "Enter Choice: ", 0, 0) == -1) {
                break;
            }
            screen = Screen::MainMenu;
        } else if (screen == Screen::SalesReport) {
            style.heading("DAILY SALES REPORT");
            cout << "Total Transactions : " << totalTransactions << "\n";
            cout << "Total Tickets Sold : " << totalTicketsSold << "\n";
            cout << style.emphasis() << "Total Revenue      : PHP " << totalRevenue << style.reset() << '\n';
            cout << "----------------------------------------------\n";
            cout << '\n';
            style.option(0, "Back to Main Menu");
            if (readNumber(style, "Enter Choice: ", 0, 0) == -1) {
                break;
            }
            screen = Screen::MainMenu;
        }
    }

    return 0;
}