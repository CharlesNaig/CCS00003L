#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>
// This header handles the highlight colors, menu labels, and terminal clearing.
#include "colors.h"

using namespace std;

// Reads one whole number between minimum and maximum, including both limits.
// Invalid entries repeat the same prompt. The default maximum accepts any int
// above the minimum. A return value of -1 tells the caller that input has ended.
int readNumber(const char* prompt, int minimum,
               int maximum = numeric_limits<int>::max()) {
    string line;
    while (true) {
        cout << prompt;
        // Read the complete line so invalid text cannot spill into the next prompt.
        if (!getline(cin, line)) {
            return -1;
        }

        // Try to read an integer, then reject any extra non-space characters.
        // For example, "2" is valid, while "2abc" and "2.5" are rejected.
        istringstream input(line);
        int number;
        char extra;
        if (input >> number && !(input >> extra) && number >= minimum && number <= maximum) {
            return number;
        }

        // A Back-only screen passes 0 for both limits, so only 0 is accepted.
        if (minimum == maximum) {
            cout << YELLOW << "Invalid choice." << RESET
                 << " Enter " << minimum << " to go back.\n";
        } else if (maximum == numeric_limits<int>::max()) {
            cout << YELLOW << "Invalid input." << RESET
                 << " Enter a whole number of at least " << minimum << ".\n";
        } else {
            cout << YELLOW << "Invalid choice." << RESET
                 << " Enter a whole number from " << minimum << " to " << maximum << ".\n";
        }
    }
}

// Program entry point. The active screen controls which menu is displayed.
int main() {
    // Set up terminal features once and restore the console settings when main ends.
    const TerminalStyle style;

    // These sizes match the number of entries stored in the arrays below.
    const int CATEGORY_COUNT = 5;
    const int SHOW_COUNT = 3;
    const int CUSTOMER_TYPE_COUNT = 4;

    // A one-dimensional array holds the labels used by both browsing and booking.
    const string categories[CATEGORY_COUNT] = {
        "Concert", "Movies", "Theatre", "Sport Venues", "Attractions"
    };

    // In this two-dimensional array, each row is a category and each column is an event.
    // The order of the rows matches the categories array.
    const string shows[CATEGORY_COUNT][SHOW_COUNT] = {
        {"Eraserheads Reunion", "SB19 Pagtatag Finale", "Ben&Ben Acoustic Night"},
        {"Final Hour", "The Last Signal", "Campus Haunt"},
        {"Ang Huling El Bimbo", "Rak of Aegis", "Mula sa Buwan"},
        {"PBA Finals Game 7", "UAAP Mens Basketball", "Gilas Pilipinas Qualifier"},
        {"Enchanted Kingdom", "Manila Ocean Park", "National Museum Tour"}
    };

    // The same row and column in shows and prices refer to the same event.
    const double prices[CATEGORY_COUNT][SHOW_COUNT] = {
        {2500.00, 1800.00, 1500.00},
        {300.00, 280.00, 250.00},
        {1200.00, 1000.00, 1100.00},
        {800.00, 500.00, 1000.00},
        {900.00, 700.00, 150.00}
    };

    // Matching indexes connect a customer label, its decimal rate, and its display text.
    // These discounts are preset values for the ticket kiosk simulation.
    const string customerTypes[CUSTOMER_TYPE_COUNT] = {
        "Student", "Senior Citizen", "PWD", "None"
    };
    const double discountRates[CUSTOMER_TYPE_COUNT] = {
        0.10, 0.15, 0.10, 0.00
    };
    const string discountNames[CUSTOMER_TYPE_COUNT] = {
        "10%", "15%", "10%", "0%"
    };

    // Sales totals and booking numbers exist only during this program run.
    // They reset when the program starts again because no records are saved to a file.
    int totalTransactions = 0;
    int totalTicketsSold = 0;
    int currentID = 1000;
    double totalRevenue = 0.0;
    // Screen names make it clear which menu the next loop iteration should open.
    enum class Screen { MainMenu, Categories, Events, CustomerInformation, SalesReport };
    Screen screen = Screen::MainMenu;
    // The same category and event screens support browsing and ticket booking.
    // In Browse mode, the user can view prices but cannot select an event to purchase.
    bool booking = false;
    // Keep the selected array positions while moving between booking screens.
    int categoryIndex = 0;
    int showIndex = 0;

    // Display money with two decimal places, such as PHP 300.00.
    cout << fixed << setprecision(2);

    // Keep the kiosk open until Exit is chosen or the input stream ends.
    while (true) {
        // Clear the previous menu before displaying the current screen.
        style.clearScreen();
        // MAIN MENU: choose whether to browse, book, view sales, or exit.
        if (screen == Screen::MainMenu) {
            style.heading("TICKETMACHINE CLI");
            cout << "  Ticket Kiosk Simulator\n\n";
            style.option(1, "View Available Ticket Categories");
            style.option(2, "Book Tickets");
            style.option(3, "Daily Sales Report");
            style.option(0, "Exit");
            cout << '\n';

            // Valid main-menu choices are 0 through 3. Here, 0 exits the program.
            int menuOption = readNumber("Enter Choice: ", 0, 3);
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
                // Option 2 starts Booking mode. Option 1 starts Browse mode.
                booking = menuOption == 2;
                screen = Screen::Categories;
            }
        // CATEGORY MENU: show all categories and allow 0 to return to the main menu.
        } else if (screen == Screen::Categories) {
            style.heading(booking ? "BOOK TICKETS" : "AVAILABLE TICKET CATEGORIES");

            for (int i = 0; i < CATEGORY_COUNT; i++) {
                style.option(i + 1, categories[i]);
            }
            style.option(0, "Back to Main Menu");
            cout << '\n';

            int catChoice = readNumber("Select Ticket Category: ", 0, CATEGORY_COUNT);
            if (catChoice == -1) {
                break;
            }
            if (catChoice == 0) {
                screen = Screen::MainMenu;
            } else {
                // Choices start at 1, while array positions start at 0.
                categoryIndex = catChoice - 1;
                screen = Screen::Events;
            }
        // EVENT MENU: list only the events and prices in the selected category.
        } else if (screen == Screen::Events) {
            style.heading(categories[categoryIndex] + " LIST");

            for (int i = 0; i < SHOW_COUNT; i++) {
                if (booking) {
                    style.optionNumber(i + 1);
                }
                // Reserve 28 characters for each title to align the price column.
                cout << left << setw(28) << shows[categoryIndex][i]
                     << "PHP " << prices[categoryIndex][i] << "\n";
            }
            style.option(0, "Back to Ticket Categories");
            cout << '\n';

            // Booking mode accepts an event number or Back. Browse mode accepts only Back.
            int showChoice = booking
                ? readNumber("Select Show / Event: ", 0, SHOW_COUNT)
                : readNumber("Enter Choice: ", 0, 0);
            if (showChoice == -1) {
                break;
            }
            if (showChoice == 0) {
                screen = Screen::Categories;
            } else {
                showIndex = showChoice - 1;
                screen = Screen::CustomerInformation;
            }
        // CUSTOMER INFORMATION: collect the details needed for the selected booking.
        } else if (screen == Screen::CustomerInformation) {
            // Read the selected event and price using the positions saved in the previous menus.
            string category = categories[categoryIndex];
            string show = shows[categoryIndex][showIndex];
            double price = prices[categoryIndex][showIndex];

            style.heading("CUSTOMER INFORMATION");
            style.option(0, "Back to Event List");
            cout << "Enter Customer Name (or 0 to go back): ";

            string cName;
            // getline accepts names with spaces. ws skips leading whitespace before the name.
            if (!getline(cin >> ws, cName)) {
                break;
            }
            // Back returns to the event list before any sale or booking ID is recorded.
            if (cName == "0") {
                screen = Screen::Events;
                continue;
            }

            // Age must be zero or greater. The chosen customer type determines the discount.
            int cAge = readNumber("Enter Age: ", 0);
            if (cAge == -1) {
                break;
            }

            cout << "\nAre you a student, senior citizen, or PWD?\n";
            for (int i = 0; i < CUSTOMER_TYPE_COUNT; i++) {
                style.option(i + 1, customerTypes[i]);
            }
            style.option(0, "Back to Event List");
            cout << '\n';

            int typeChoice = readNumber("Enter Choice: ", 0, CUSTOMER_TYPE_COUNT);
            if (typeChoice == -1) {
                break;
            }
            // Returning here discards these customer details and opens the event list again.
            if (typeChoice == 0) {
                screen = Screen::Events;
                continue;
            }

            // Use one matching index to retrieve the customer type and discount information.
            int typeIndex = typeChoice - 1;
            string cType = customerTypes[typeIndex];
            double discountRate = discountRates[typeIndex];
            string discountName = discountNames[typeIndex];

            // Require at least one ticket. Invalid quantities repeat this prompt.
            int qty = readNumber("\nEnter Number of Tickets: ", 1);
            if (qty == -1) {
                break;
            }

            // Calculate the booking cost before and after the customer discount.
            double sub = price * qty;
            double discAmt = sub * discountRate;
            double total = sub - discAmt;
            // VAT is displayed separately and is not added to the total.
            double vat = total * 0.12;
            // Convert the current number to text and add TM, producing IDs such as TM1000.
            string bID = "TM" + to_string(currentID);

            // Replace the input form with the cost breakdown and receipt.
            // Both remain available until the user chooses Back below.
            style.clearScreen();
            style.heading("TICKET COMPUTATION");
            cout << "Selected Show: " << show << "\n";
            cout << "Ticket Type: " << category << "\n";
            cout << "Ticket Price: PHP " << price << "\n";
            cout << "Quantity: " << qty << "\n\n";
            cout << "Subtotal: PHP " << sub << "\n";
            cout << "Discount: " << discountName << "\n";
            cout << "Discount Amount: PHP " << discAmt << "\n";
            cout << "Vat Amount: PHP " << vat << "\n\n";
            cout << BOLD << "TOTAL AMOUNT: PHP " << total << RESET << '\n';

            // RECEIPT: show the booking ID, customer, event, amount, and confirmation status.
            // GREEN highlights confirmation, and RESET returns later text to its normal appearance.
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
            cout << BOLD << "Total Amount: PHP " << total << RESET << "\n\n";
            cout << "Booking Status: " << GREEN << "CONFIRMED" << RESET << "\n\n";
            cout << "Thank you for using Ticket Machine!\n";
            cout << "----------------------------------------------\n";

            // Record this confirmed booking exactly once, then prepare the next booking number.
            // Backing out earlier never reaches this block, so it does not affect the sales totals.
            totalTransactions++;
            totalTicketsSold += qty;
            totalRevenue += total;
            currentID++;

            cout << '\n';
            style.option(0, "Back to Main Menu");
            if (readNumber("Enter Choice: ", 0, 0) == -1) {
                break;
            }
            screen = Screen::MainMenu;
        // SALES REPORT: display confirmed sales from the current run, then wait for Back.
        } else if (screen == Screen::SalesReport) {
            style.heading("DAILY SALES REPORT");
            cout << "Total Transactions : " << totalTransactions << "\n";
            cout << "Total Tickets Sold : " << totalTicketsSold << "\n";
            cout << BOLD << "Total Revenue      : PHP " << totalRevenue << RESET << '\n';
            cout << "----------------------------------------------\n";
            cout << '\n';
            style.option(0, "Back to Main Menu");
            if (readNumber("Enter Choice: ", 0, 0) == -1) {
                break;
            }
            screen = Screen::MainMenu;
        }
    }

    // Returning 0 tells the operating system that the program finished successfully.
    return 0;
}
