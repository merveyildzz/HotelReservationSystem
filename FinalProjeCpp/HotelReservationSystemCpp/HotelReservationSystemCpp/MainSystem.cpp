#include <iostream>
#include "reservation.h"  
#include "validation.h" 
using namespace std;

int main() {
    int choice; //takes input for the operation to be selected from the menu
    const string filename = "reservation.txt"; //txt file that holds reservation data

    //The loop shows the user the options available from the menu.
    do {
        cout << "\n** HOTEL RESERVATION SYSTEM **\n";
        cout << "1. Load from file\n";
        cout << "2. Insert New Reservation\n";
        cout << "3. Find a Reservation\n";
        cout << "4. List of Reservations\n";
        cout << "5. Sort\n";
        cout << "6. Save to file\n";
        cout << "7. Exit\n";
        cout << "Make a selection (1-7): ";
        cin >> choice;

        //Checks for incorrect input in menu action selection
        if (cin.fail() || choice < 1 || choice > 7) {
            cin.clear();  // Clears the error condition (such as entering a letter instead of a number)
            cin.ignore(1000, '\n'); // Clears incorrectly entered data
            cout << "Invalid selection! Please enter a number between 1 and 7.\n";
            continue;
        }

        //The action is performed according to the entered selection
        switch (choice) {
            case 1:
                //Uploads the file of reservations
                loadFromFile(filename); 
                break;
            case 2:
                //A new reservation is added
                insertNewReservation(reservationNumber, guestName, roomNumber, 
                                     checkInDate, checkOutDate, totalNightStay, 
                                     reservationStatus, capacity);
                break;
            case 3:
                //Reservation search is performed
                findReservation();
                break;
            case 4:
                //All reservations are listed
                listReservations();
                break;
            case 5:
                //Sorts reservations according to a criterion
                sortable();
                break;
            case 6:
                //It saves the entered reservations to the reservation.txt
                saveToFile(filename); 
                break;
            case 7:
                 //Exit 
                cout << "Terminated...\n";
                break;
        }
    } while (choice != 7); //The loop continues until the "7" option (exit) is selected
    
    return 0;
}
