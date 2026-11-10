# TicketMachine: Ticket Kiosk Simulator

CCS00003L final project. TicketMachine is a C++ console program for browsing a sample event catalog, booking tickets, printing an on-screen receipt, and viewing sales totals for the current session.

## Build and run

**VS Code on Windows.** Install the Microsoft C/C++ extension and open the project folder. The included [build task](.vscode/tasks.json) uses MSYS2 UCRT64 GCC at `C:\msys64\ucrt64\bin\g++.exe`. Open `DRAFT2.cpp` and press **Ctrl+F5** to build and run it in the integrated terminal. **F5** uses the [debug configuration](.vscode/launch.json), which expects GDB in the same UCRT64 directory. Update those paths if MSYS2 is installed elsewhere.

**PowerShell.** From the project folder, with GCC installed at the default path:

```powershell
$env:PATH = "C:\msys64\ucrt64\bin;$env:PATH"
g++ -std=c++17 -Wall -Wextra DRAFT2.cpp -o ticketmachine.exe
.\ticketmachine.exe
```

Both C++ drafts define their own `main()`. Build one file at a time. Use `DRAFT2.cpp` to follow the walkthrough below.

## Main menu

| Option | What it does |
| --- | --- |
| `1` | Lists the five categories: concerts, movies, theatre, sports venues, and attractions. |
| `2` | Prompts for a category, event, customer name, age, customer type, and ticket quantity. Displays the calculation and a confirmed receipt. |
| `3` | Shows confirmed transactions, tickets sold, and total revenue in the current session. |
| `0` | Exits the simulator. |

## Source code guide

- [`draft.cpp`](draft.cpp) is the first working version. Its `main()` uses nested `switch` statements for the menus and stores event names and prices in the corresponding branches.
- [`DRAFT2.cpp`](DRAFT2.cpp) is the array-based draft used in this guide. Its `main()` organizes the program into the following blocks.

| Block | How it works in `DRAFT2.cpp` |
| --- | --- |
| Catalog and discounts | `categories` contains the category labels. The two-dimensional `shows` and `prices` arrays share the same row and column positions. `customerTypes`, `discountRates`, and `discountNames` use matching indexes for student (10%), senior citizen (15%), PWD (10%), and regular (0%) bookings. |
| Main menu | A `while` loop displays the menu. An `if`/`else if` chain handles the selected action. |
| Booking input | The program validates category, event, customer type, age, and quantity before confirming a booking. It converts numbered selections to zero-based array indexes and uses `getline` to accept a customer name with spaces. Invalid booking input returns to the main menu. |
| Calculation and receipt | `sub = price * qty`, `discAmt = sub * discountRate`, and `total = sub - discAmt`. The simulator displays `vat = total * 0.12` separately. The receipt starts at booking ID `TM1000` and shows the event, customer type, quantity, and amount. |
| Sales counters | After a receipt, the program increments the transaction count and booking ID, then adds the quantity and discounted amount to `totalTicketsSold` and `totalRevenue`. |

## Sample booking

On a fresh run, choose **2 → 2 → 1** for Book Tickets → Movies → Final Hour. Enter `Sample Customer`, age `18`, customer type `1` (Student), and quantity `2`. Then choose **3** for the report and **0** to exit.

| Output | Expected result |
| --- | --- |
| Subtotal | PHP 600.00 |
| Student discount | PHP 60.00 |
| Separately displayed VAT amount | PHP 64.80 |
| Confirmed booking | TM1000 |
| Total amount | PHP 540.00 |
| Sales report | 1 transaction, 2 tickets, PHP 540.00 revenue |

The catalog and rates are preset simulation values. Booking IDs and sales totals reset at restart. Search and booking history appear in the [CLI mockup](cli.txt) and are pending implementation.

## Project documents

- [Progress report](PROGRESS_REPORT.md)
- [Project paper](Paper-TicketMachine.docx)
- [CLI mockup](cli.txt) and [planning notes](notes.txt)
