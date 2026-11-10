#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
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
    bool running = true;

    cout << fixed << setprecision(2);

    while (running) {
        int menuOption = 0;

        cout << "\n========================================\n";
        cout << "         TICKETMACHINE CLI\n";
        cout << "========================================\n";
        cout << "              Ticket Kiosk\n";
        cout << "========================================\n\n";
        cout << "[1] View Available Ticket Categories\n";
        cout << "[2] Book Tickets\n";
        cout << "[3] Daily Sales Report\n";
        cout << "[0] Exit\n\n";
        cout << "Enter Choice: ";

        if (!(cin >> menuOption)) {
            if (cin.eof()) {
                break;
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
        }

        // If-else statements handle the main menu.
        if (menuOption == 1) {
            cout << "\n========================================\n";
            cout << "       AVAILABLE TICKET CATEGORIES\n";
            cout << "========================================\n";

            for (int i = 0; i < CATEGORY_COUNT; i++) {
                cout << "[" << i + 1 << "] " << categories[i] << "\n";
            }
        } else if (menuOption == 2) {
            int catChoice = 0;
            int showChoice = 0;
            int cAge = 0;
            int typeChoice = 0;
            int qty = 0;
            string cName;

            cout << "\n========================================\n";
            cout << "              BOOK TICKETS\n";
            cout << "========================================\n\n";
            cout << "Select Ticket Category:\n";

            for (int i = 0; i < CATEGORY_COUNT; i++) {
                cout << "[" << i + 1 << "] " << categories[i] << "\n";
            }
            cout << "\nEnter Choice: ";

            if (!(cin >> catChoice) || catChoice < 1 || catChoice > CATEGORY_COUNT) {
                if (cin.eof()) {
                    break;
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid category. Returning to main menu.\n";
                    continue;
                }
            }

            int categoryIndex = catChoice - 1;

            cout << "\n========================================\n";
            cout << "              " << categories[categoryIndex] << " LIST\n";
            cout << "========================================\n\n";

            for (int i = 0; i < SHOW_COUNT; i++) {
                cout << "[" << i + 1 << "] "
                     << left << setw(28) << shows[categoryIndex][i]
                     << "PHP " << prices[categoryIndex][i] << "\n";
            }
            cout << "\nSelect Show / Event: ";

            if (!(cin >> showChoice) || showChoice < 1 || showChoice > SHOW_COUNT) {
                if (cin.eof()) {
                    break;
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid show. Returning to main menu.\n";
                    continue;
                }
            }

            int showIndex = showChoice - 1;
            string category = categories[categoryIndex];
            string show = shows[categoryIndex][showIndex];
            double price = prices[categoryIndex][showIndex];

            cout << "\n========================================\n";
            cout << "          CUSTOMER INFORMATION\n";
            cout << "========================================\n\n";
            cout << "Enter Customer Name: ";

            if (!getline(cin >> ws, cName)) {
                break;
            }

            cout << "Enter Age: ";
            if (!(cin >> cAge) || cAge < 0) {
                if (cin.eof()) {
                    break;
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid age. Returning to main menu.\n";
                    continue;
                }
            }

            cout << "\nAre you a student, senior citizen, or PWD?\n";
            for (int i = 0; i < CUSTOMER_TYPE_COUNT; i++) {
                cout << "[" << i + 1 << "] " << customerTypes[i] << "\n";
            }
            cout << "\nEnter Choice: ";

            if (!(cin >> typeChoice) || typeChoice < 1 || typeChoice > CUSTOMER_TYPE_COUNT) {
                if (cin.eof()) {
                    break;
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid customer type. Returning to main menu.\n";
                    continue;
                }
            }

            int typeIndex = typeChoice - 1;
            string cType = customerTypes[typeIndex];
            double discountRate = discountRates[typeIndex];
            string discountName = discountNames[typeIndex];

            cout << "\nEnter Number of Tickets: ";
            if (!(cin >> qty) || qty <= 0) {
                if (cin.eof()) {
                    break;
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid quantity. Enter a positive whole number.\n";
                    continue;
                }
            }

            double sub = price * qty;
            double discAmt = sub * discountRate;
            double total = sub - discAmt;
            // VAT is displayed separately and is not added to the total.
            double vat = total * 0.12;
            string bID = "TM" + to_string(currentID);

            cout << "\n========================================\n";
            cout << "          TICKET COMPUTATION\n";
            cout << "========================================\n\n";
            cout << "Selected Show: " << show << "\n";
            cout << "Ticket Type: " << category << "\n";
            cout << "Ticket Price: PHP " << price << "\n";
            cout << "Quantity: " << qty << "\n\n";
            cout << "Subtotal: PHP " << sub << "\n";
            cout << "Discount: " << discountName << "\n";
            cout << "Discount Amount: PHP " << discAmt << "\n";
            cout << "Vat Amount: PHP " << vat << "\n\n";
            cout << "TOTAL AMOUNT: PHP " << total << "\n";

            cout << "\n========================================\n";
            cout << "             PURCHASE RECEIPT\n";
            cout << "========================================\n\n";
            cout << "Booking ID: " << bID << "\n";
            cout << "Customer Name: " << cName << "\n";
            cout << "Customer Type: " << cType << "\n\n";
            cout << "========================================\n";
            cout << "Ticket Category: " << category << "\n";
            cout << "Selected Show: " << show << "\n";
            cout << "Ticket Price: PHP " << price << "\n";
            cout << "Quantity: " << qty << "\n\n";
            cout << "Subtotal: PHP " << sub << "\n\n";
            cout << "Vat Amount: PHP " << vat << "\n";
            cout << "Discount Amount: PHP " << discAmt << "\n";
            cout << "========================================\n";
            cout << "Total Amount: PHP " << total << "\n\n";
            cout << "Booking Status: CONFIRMED\n\n";
            cout << "Thank you for using Ticket Machine!\n";
            cout << "========================================\n";

            totalTransactions++;
            totalTicketsSold += qty;
            totalRevenue += total;
            currentID++;
        } else if (menuOption == 3) {
            cout << "\n========================================\n";
            cout << "           DAILY SALES REPORT\n";
            cout << "========================================\n";
            cout << "Total Transactions : " << totalTransactions << "\n";
            cout << "Total Tickets Sold : " << totalTicketsSold << "\n";
            cout << "Total Revenue      : PHP " << totalRevenue << "\n";
            cout << "========================================\n";
        } else if (menuOption == 0) {
            cout << "\nExiting Ticket Kiosk Simulator. Goodbye!\n";
            running = false;
        } else {
            cout << "\nInvalid input. Please select a valid option.\n";
        }
    }

    return 0;
}