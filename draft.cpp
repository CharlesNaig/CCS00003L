#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    int totalTransactions = 0;
    int totalTicketsSold = 0;
    int currentID = 1000;
    int catChoice, menuOption, showChoice, cAge, typeChoice, qty;
    double discountRate = 0.0;
    double totalRevenue = 0.0;
    double price = 0.0;
    
    bool running = true;

    while (running) {
        cout << "\n========================================\n";
        cout << "         TICKET MACHINE CLI\n";
        cout << "========================================\n";
        cout << "           Ticket Kiosk\n";
        cout << "========================================\n\n";
        cout << "[1] View Available Ticket Categories\n";
        cout << "[2] Book Tickets\n";
        cout << "[3] Daily Sales Report\n";
        cout << "[0] Exit\n\n";
        cout << "Select Option: 1-3 / 0\n";
        cout << "Enter Choice: ";
        
        cin >> menuOption;

        switch (menuOption) {
            case 1:
                cout << "\n========================================\n";
                cout << "       AVAILABLE TICKET CATEGORIE/S\n";
                cout << "========================================\n";
                cout << "[1] Concert\n[2] Movies\n[3] Theatre\n[4] Sport Venues\n[5] Attractions\n";
                break;

            case 2: {
                cout << "\n========================================\n";
                cout << "              BOOK TICKETS\n";
                cout << "========================================\n\n";
                cout << "Select Ticket Category:\n";
                cout << "[1] Concert\n[2] Movies\n[3] Theatre\n[4] Sport Venues\n[5] Attractions\n\n";
                cout << "Enter Choice: ";
                
                
                cin >> catChoice;

                string category = "";
                string show = "";
                

                switch (catChoice) {
                    case 1:
                        category = "Concert";
                        cout << "\n========================================\n";
                        cout << "              CONCERT LIST\n";
                        cout << "========================================\n\n";
                        cout << "[1] Eraserheads Reunion         PHP 2500.00\n";
                        cout << "[2] SB19 Pagtatag Finale        PHP 1800.00\n";
                        cout << "[3] Ben&Ben Acoustic Night      PHP 1500.00\n\n";
                        cout << "Select Concert: ";
                        cin >> showChoice;
                        switch (showChoice) {
                            case 1: show = "Eraserheads Reunion"; price = 2500.00; break;
                            case 2: show = "SB19 Pagtatag Finale"; price = 1800.00; break;
                            case 3: show = "Ben&Ben Acoustic Night"; price = 1500.00; break;
                            default: cout << "Invalid choice.\n"; category = "Invalid"; break;
                        }
                        break;
                    case 2:
                        category = "Movie";
                        cout << "\n========================================\n";
                        cout << "               MOVIE LIST\n";
                        cout << "========================================\n\n";
                        cout << "[1] Final Hour                  PHP 300.00\n";
                        cout << "[2] The Last Signal             PHP 280.00\n";
                        cout << "[3] Campus Haunt                PHP 250.00\n\n";
                        cout << "Select Movie: ";
                        cin >> showChoice;
                        switch (showChoice) {
                            case 1: show = "Final Hour"; price = 300.00; break;
                            case 2: show = "The Last Signal"; price = 280.00; break;
                            case 3: show = "Campus Haunt"; price = 250.00; break;
                            default: cout << "Invalid choice.\n"; category = "Invalid"; break;
                        }
                        break;
                    case 3:
                        category = "Theatre";
                        cout << "\n========================================\n";
                        cout << "              THEATRE LIST\n";
                        cout << "========================================\n\n";
                        cout << "[1] Ang Huling El Bimbo         PHP 1200.00\n";
                        cout << "[2] Rak of Aegis                PHP 1000.00\n";
                        cout << "[3] Mula sa Buwan               PHP 1100.00\n\n";
                        cout << "Select Theatre Show: ";
                        cin >> showChoice;
                        switch (showChoice) {
                            case 1: show = "Ang Huling El Bimbo"; price = 1200.00; break;
                            case 2: show = "Rak of Aegis"; price = 1000.00; break;
                            case 3: show = "Mula sa Buwan"; price = 1100.00; break;
                            default: cout << "Invalid choice.\n"; category = "Invalid"; break;
                        }
                        break;
                    case 4:
                        category = "Sport Venues";
                        cout << "\n========================================\n";
                        cout << "            SPORT VENUES LIST\n";
                        cout << "========================================\n\n";
                        cout << "[1] PBA Finals Game 7           PHP 800.00\n";
                        cout << "[2] UAAP Mens Basketball        PHP 500.00\n";
                        cout << "[3] Gilas Pilipinas Qualifier   PHP 1000.00\n\n";
                        cout << "Select Sport Event: ";
                        cin >> showChoice;
                        switch (showChoice) {
                            case 1: show = "PBA Finals Game 7"; price = 800.00; break;
                            case 2: show = "UAAP Mens Basketball"; price = 500.00; break;
                            case 3: show = "Gilas Pilipinas Qualifier"; price = 1000.00; break;
                            default: cout << "Invalid choice.\n"; category = "Invalid"; break;
                        }
                        break;
                    case 5:
                        category = "Attractions";
                        cout << "\n========================================\n";
                        cout << "            ATTRACTIONS LIST\n";
                        cout << "========================================\n\n";
                        cout << "[1] Enchanted Kingdom           PHP 900.00\n";
                        cout << "[2] Manila Ocean Park           PHP 700.00\n";
                        cout << "[3] National Museum Tour        PHP 150.00\n\n";
                        cout << "Select Attraction: ";
                        cin >> showChoice;
                        switch (showChoice) {
                            case 1: show = "Enchanted Kingdom"; price = 900.00; break;
                            case 2: show = "Manila Ocean Park"; price = 700.00; break;
                            case 3: show = "National Museum Tour"; price = 150.00; break;
                            default: cout << "Invalid choice.\n"; category = "Invalid"; break;
                        }
                        break;
                    default:
                        cout << "Invalid Category.\n";
                        category = "Invalid";
                        break;
                }

                if (category == "Invalid") break;

                cout << "\n========================================\n";
                cout << "          CUSTOMER INFORMATION\n";
                cout << "========================================\n\n";
                
                string cName;
                cout << "Enter Customer Name: ";
                getline(cin >> ws, cName);
                

                cout << "Enter Age: ";
                cin >> cAge;

                cout << "\nAre you a student, senior citizen, or PWD? (Enter the corresponding number)?:\n";
                cout << "[1] Student\n[2] Senior Citizen\n[3] PWD\n[4] None\n\n";
                cout << "Enter Choice: ";
                cin >> typeChoice;

                string cType = "None";
                string discountName = "0%";

                switch (typeChoice) {
                    case 1: cType = "Student"; discountRate = 0.10; discountName = "10%"; break;
                    case 2: cType = "Senior Citizen"; discountRate = 0.15; discountName = "15%"; break;
                    case 3: cType = "PWD"; discountRate = 0.10; discountName = "10%"; break;
                    case 4: cType = "None"; discountRate = 0.0; discountName = "0%"; break;
                    default: cType = "None"; discountRate = 0.0; discountName = "0%"; break;
                }

                cout << "\nEnter Number of Tickets: ";
                cin >> qty;

                // Math Computation
                double sub = price * qty;
                double discAmt = sub * discountRate;
                double total = sub - discAmt;
                double vat = total * 0.12; 
                string bID = "TM" + to_string(currentID);

                cout << "\n========================================\n";
                cout << "          TICKET COMPUTATION\n";
                cout << "========================================\n\n";
                cout << "Selected Show: " << show << "\n";
                cout << "Ticket Type: " << category << "\n";
                cout << fixed << setprecision(2);
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
                cout << "========================================\n\n";
                cout << "Ticket Category: " << category << "\n";
                cout << "Selected Show: " << show << "\n";
                cout << "Ticket Price: PHP " << price << "\n";
                cout << "Quantity: " << qty << "\n\n";
                cout << "Subtotal: PHP " << sub << "\n\n";
                cout << "Vat Amount: PHP " << vat << "\n";
                cout << "Discount Amount: PHP " << discAmt << "\n\n";
                cout << "========================================\n\n";
                cout << "Total Amount: PHP " << total << "\n\n";
                cout << "Booking Status: CONFIRMED\n\n";
                cout << "Thank you for using Ticket Machine!\n";
                cout << "========================================\n";

                totalTransactions++;
                totalTicketsSold += qty;
                totalRevenue += total;
                currentID++;
                
                break;
            }

            case 3: {
                cout << "\n========================================\n";
                cout << "           DAILY SALES REPORT\n";
                cout << "========================================\n";
                
                cout << "Total Transactions : " << totalTransactions << "\n";
                cout << "Total Tickets Sold : " << totalTicketsSold << "\n";
                cout << "Total Revenue      : PHP " << fixed << setprecision(2) << totalRevenue << "\n";
                cout << "========================================\n";
                break;
            }

            case 0:
                cout << "\nExiting Ticket Kiosk Simulator. Goodbye!\n";
                running = false;
                break;

            default:
                cout << "\nInvalid input. Please select a valid option.\n";
                break;
        }
    }

    return 0; 
}
