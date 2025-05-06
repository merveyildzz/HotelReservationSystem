#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "validation.h" 
#include "reservation.h"

using namespace std;
int reservationCount=0; // keeps track of the number of existing reservations entered up to the maximum value
int capacity = 6;

int* reservationNumber = new int[capacity];
string* guestName = new string[capacity];
int* roomNumber = new int[capacity];
string* checkInDate = new string[capacity];
string* checkOutDate = new string[capacity];
int* totalNightStay = new int[capacity];
bool* reservationStatus = new bool[capacity];

void printRow(const string& col1, const string& col2, const string& col3, const string& col4,
              const string& col5, const string& col6, const string& col7) {
    cout << left
         << setw(20) << col1
         << setw(30) << col2
         << setw(15) << col3
         << setw(20) << col4
         << setw(20) << col5
         << setw(15) << col6
         << setw(20) << col7
         << endl;
}


//assigns an automatic and sequential reservation number to the user, then takes the user's name, surname, room number, check-in date, check-out date information, calculates the total number of nights stay by processing the received check-in and check-out dates, and finally checks the reservation status. offers the opportunity. For all these input operations, the entered answers are checked for accuracy.
void insertNewReservation(int*& reservationNumber, string*& guestName, int*& roomNumber, 
                          string*& checkInDate, string*& checkOutDate, int*& totalNightStay, 
                          bool*& reservationStatus, int& capacity){
    cout << "Reservation Count: " << reservationCount << ", Capacity: " << capacity << endl;

    if (reservationCount >= capacity) {
        cout << "Expanding table..." << endl; // Test mesajı
        expandTable(reservationNumber, guestName, roomNumber, checkInDate, checkOutDate, 
                    totalNightStay, reservationStatus, capacity);
    }
    
    //If the reservation number is 0, it becomes 1. If it is another number, 1 is added to it and the result is assigned to the reservationNumber array.
    int newReservationNumber = (reservationCount == 0) ? 1 : reservationNumber[reservationCount - 1] + 1;
    reservationNumber[reservationCount] = newReservationNumber;

    cout << "Reservation Number (Auto-Generated): " << newReservationNumber << endl;
    
    //The name and surname are taken separately from the user and added to the guestName array after adding a space between them.
    string name, surname;
    cout << "Please Enter Guest Name: ";
    cin >> name;
    cout << "Please Enter Guest Surname: ";
    cin >> surname;
    guestName[reservationCount] = name + " " + surname;

    //After checking whether the entered value is valid or not, it is thrown into the roomNumber array
    roomNumber[reservationCount] = Validation::getValidRoomNumber("Please Enter Room Number ");

    //The month, year and day are taken and after their suitability is checked, they are thrown into the checkInDate array.
    cout << "Hotel Check-In Date: \n";
    int day1, month1, year1;
    Validation::getMonth(month1);
    Validation::getYear(year1);
    Validation::getDay(day1, month1, year1);
    checkInDate[reservationCount] = to_string(day1) + "/" + to_string(month1) + "/" + to_string(year1);
    
    //it is guaranteed that the exit date is after the entry date by looking at the difference in days
    int day2, month2, year2;
    cout << "Hotel Check-Out Date: \n";
    while (true) {
        Validation::getMonth(month2);
        Validation::getYear(year2);
        Validation::getDay(day2, month2, year2);
        if (Validation::calculateDaysBtwDates(day1, month1, year1, day2, month2, year2) > 0){
            break;
        }
        else {
            cout << "Check-Out date must be after Check-In date. Please enter a valid date.\n";
        }
    }
    
    //The exit date is formatted and placed in the checkOutDate array
    checkOutDate[reservationCount] = to_string(day2) + "/" + to_string(month2) + "/" + to_string(year2);

    //The difference between check-in and check-out dates is calculated and added to the totalNightStay array
    totalNightStay[reservationCount] = Validation::calculateDaysBtwDates(day1, month1, year1, day2, month2, year2);
    cout << "Total Number of Nights: " << totalNightStay[reservationCount] << endl;

    //The user is asked for reservation status as string input
   int status;
    while (true) {
        cout << "Please Enter Reservation Status (1 = Confirmed, 0 = Rejected): ";
        string input;
        cin >> input;

        if (Validation::isValidStatement(input)) { // Use Validation:: prefix for static method
            status = stoi(input);
            reservationStatus[reservationCount] = status;
            break;
        } else {
            cout << "Please try again.\n";
        }
    }

    // After the user logs in, the remaining \n character is deleted and prevents the next login from being made automatically.
    cin.ignore();
    reservationCount++; // number of reservations is increased
    cout << "Your reservation has been added successfully!\n";
}

void listReservations() {
    //If there is no reservation, the user is informed and the function ends
    if (reservationCount == 0) {
        cout << "No reservations found!" << endl;
        return;
    }

    cout << string(140, '=') << endl; //Starts the table by drawing a line 140 characters long
    const int lineWidth = 140; //A width of 140 characters is specified
    string title = "RESERVATION LIST";
    int padding = (lineWidth - title.length()) / 2; //Calculating the amount of space to fill the left side
    if (padding > 0) {
        cout << string(padding, ' '); // Add padding spaces. This ensures that the title is perfectly centered.
    }
    cout << title << endl;
    cout << string(140, '=') << endl; //Adds a 140 character long line (=) under the title.
 
    // Prints table column headers
    printRow("Reservation Number", "Guest Name and Surname", "Room Number",
             "Check-In Date", "Check-Out Date", "Total Nights", "Reservation Status");

    //Adds a 140 character long line (=).
    cout << string(140, '=') << endl;

    //Prints the selected reservation information on the screen.
    for (int i = 0; i < reservationCount; i++) {
        printRow(
            to_string(reservationNumber[i]), guestName[i], to_string(roomNumber[i]),
            checkInDate[i], checkOutDate[i], to_string(totalNightStay[i]),
            (reservationStatus[i] ? "Confirmed" : "Rejected")
        );
    }

    //Adds a 140 character long line (=).
    cout << string(140, '=') << endl;
}

//With this function, all reservations that contain a key are listed by using the find function
void displayReservation(int index) {
    cout << string(140, '=') << endl; // Starts the table by drawing a line 140 characters long
    
    //Table headings are specified and alignment is set from left to right.
    printRow("Reservation Number", "Guest Name and Surname", "Room Number",
             "Check-In Date", "Check-Out Date", "Total Nights", "Reservation Status");
    
    cout << string(140, '=') << endl;
    //Prints the selected reservation information on the screen.
    printRow(
        to_string(reservationNumber[index]), guestName[index], to_string(roomNumber[index]),
        checkInDate[index], checkOutDate[index], to_string(totalNightStay[index]),
        (reservationStatus[index] ? "Confirmed" : "Rejected")
    );
    cout << string(140, '=') << endl;
}

//In the find reservation function, the user chooses the criteria by which he can search for a word, date or number. As a result, if one or more results are found, they appear; if no results are found, a message is returned. Editing and deleting operations on the results can be done by using the room number as a unique key.
void findReservation() {
    int searchOption; //criteria to search for
    string searchString; //text to search
    int searchInt; //number to search

    //opens a selection submenu, the selection made in this menu is assigned to the searchOption variable
    do {
        cout << "\nBy which criteria do you want to search?\n";
        cout << "1. Reservation number\n";
        cout << "2. Name or Surname\n";
        cout << "3. Room Number\n";
        cout << "4. Check In Date (DD/MM/YYYY)\n";
        cout << "5. Check Out Date (DD/MM/YYYY)\n";
        cout << "6. Total Night Stay\n";
        cout << "7. Reservation Status (1: Confirmed, 0: Rejected)\n";
        cout << "8. Return to Main Menu\n";
        cout << "Make a selection (1-8): ";
        cin >> searchOption;

        
       if (cin.fail()) { //if the input received from the user is incorrect
            cin.clear(); //clears any error condition
            cin.ignore(1000, '\n'); //If the user has entered up to 1000 characters in the terminal and pressed enter, it will be ignored for the new entry.
            cout << "Invalid input! Please enter a valid number.\n";
            continue; //For the program to request another input if there is an incorrect input
        }

        // if 8 is selected, this menu is exited
        if (searchOption == 8) {
            cout << "Returning to Main Menu...\n";
            return;
        }
        //checks whether the inputs are between 1 and 8
        if (searchOption < 1 || searchOption > 8) {
            cout << "Invalid selection. Please try again.\n";
            continue;
        }

        //number is taken from the user and its validity is checked
        if (searchOption == 1 || searchOption == 3 || searchOption == 6 || searchOption == 7) {
            cout << "Enter a number for the search: ";
            string input;
            cin >> input;

       if (cin.fail()) { //if the input received from the user is incorrect
            cin.clear(); //clears any error condition
            cin.ignore(1000, '\n'); //If the user has entered up to 1000 characters in the terminal and pressed enter, it will be ignored for the new entry.
            cout << "Invalid input! Please enter a valid number.\n";
            continue; //For the program to request another input if there is an incorrect input
        }
            //if it is numeric, the string is converted to integer and the message is returned to the value
            if (Validation::isNumeric(input)) {
                searchInt = stoi(input);
            } else {
                cout << "Invalid input. Please enter a valid number.\n";
                continue;
            }
            //gets date for check in and check out from user
        } else if (searchOption == 4 || searchOption == 5) {
            int day, month, year;
            cout << "Enter the date (DD/MM/YYYY):\n";

            Validation::getMonth(month);
            Validation::getYear(year);
            Validation::getDay(day, month, year);

        if (cin.fail()) { //if the input received from the user is incorrect
            cin.clear(); //clears any error condition
            cin.ignore(1000, '\n'); //If the user has entered up to 1000 characters in the terminal and pressed enter, it will be ignored for the new entry.
            cout << "Invalid input! Please enter a valid number.\n";
            continue; //For the program to request another input if there is an incorrect input
        }
            //converted into a string in the correct format
            searchString = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
        } else {
            //user is asked for first or last name
            cout << "Enter a Name or Surname: ";
            cin.ignore(); //If there is a space or \n character left from the previous entry, that character is cleared to prevent the question from automatically passing.
            getline(cin, searchString); //takes the entire line and assigns it to the searchString variable

       if (cin.fail()) { //if the input received from the user is incorrect
            cin.clear(); //clears any error condition
            cin.ignore(1000, '\n'); //If the user has entered up to 1000 characters in the terminal and pressed enter, it will be ignored for the new entry.
            cout << "Invalid input! Please enter a valid number.\n";
            continue; //For the program to request another input if there is an incorrect input
        }

        }

        // Starts the search process
                bool found = false;
                for (int i = 0; i < reservationCount; i++) {
                    bool match = false;

                    // Compares based on the selected search option
                    switch (searchOption) {
                        case 1:
                            if (reservationNumber[i] == searchInt) match = true; //If the reservation number matches
                            break;
                        case 2:
                            if (guestName[i].find(searchString) != string::npos) match = true; // If the guest name matches
                            break;
                        case 3:
                            if (roomNumber[i] == searchInt) match = true; // If the room number matches
                            break;
                        case 4:
                            if (checkInDate[i] == searchString) match = true; // If the check in date matches
                            break;
                        case 5:
                            if (checkOutDate[i] == searchString) match = true;
                            break;
                        case 6:
                            if (totalNightStay[i] == searchInt) match = true;
                            break;
                        case 7:
                            if (reservationStatus[i] == searchInt) match = true;
                            break;
                    }
                    
                    // If a match is found, it displays the relevant reservation information
                    if (match) {
                        found = true; // Match found, set 'found' variable to true.
                        displayReservation(i); //Display matching reservation.
                    }
                }

                // If no match is found, notify the user
                if (!found) {
                    cout << "No matching results found. Returning to search menu.\n";
                    continue;
                }

                //After showing the reservations, get the reservation number from the user to take action
                cout << "\nEnter the Reservation Number for further actions: ";
                cin >> searchInt;

                // Checks the validity of the reservation number received from the user
               if (cin.fail()) { //if the input received from the user is incorrect
            cin.clear(); //clears any error condition
            cin.ignore(1000, '\n'); //If the user has entered up to 1000 characters in the terminal and pressed enter, it will be ignored for the new entry.
            cout << "Invalid input! Please enter a valid number.\n";
            continue; //For the program to request another input if there is an incorrect input
        }

                // The index of the reservation corresponding to the selected reservation number is found
                int index = -1; // Initially, it is assumed that there is no valid index
                for (int i = 0; i < reservationCount; i++) {
                    if (reservationNumber[i] == searchInt) { //If the reservation number matches
                        index = i; //Index is found
                        break;
                    }
                }

                // If the reservation corresponding to the reservation number is not found
                if (index == -1) {
                    cout << "No reservation found with the entered number. Returning to search menu...\n";
                    continue; // Returns to the search menu
                }

                //The user is asked to select an action
                int action;
                do {
                    cout << "\n1. Edit\n2. Delete\n3. Exit\nChoose an action: ";
                    cin >> action;

                    //Checks if the value entered by the user is a number between 1 and 3
                    if (cin.fail() || action < 1 || action > 3) { //if the input received from the user is incorrect
                        cin.clear(); //clears any error condition
                        cin.ignore(1000, '\n'); //If the user has entered up to 1000 characters in the terminal and pressed enter, it will be ignored for the new entry.
                        cout << "Invalid action! Please try again.\n";
                        continue;
                    }

                    // The action is performed according to the user's selection
                    switch (action) {
                        case 1:
                            editReservation(index); //To edit the reservation, the edit function is called.
                            break;
                        case 2:
                            deleteReservation(index); // To delete the reservation, the delete function is called.
                            action = 3; // After the delete operation, the loop is exited.
                            break;
                        case 3:
                            cout << "Returning to Main Menu...\n"; // The loop is exited and the main menu is returned.
                            break;
                    }
                } while (action != 3); // The loop continues until the user selects 'Exit'
            } while (true);
        }

/* With this function, all titles of a selected reservation, except the automatically assigned reservation number
and the automatically calculated total night stay,
can be edited and all rules are taken into account during editing. */
void editReservation(int index) {
    cout << "Editing Reservation ID: " << reservationNumber[index] << "\n";

    string firstName, lastName;
    //It takes the part starting from 0 to the space to separate the first name and last name.
    //Thus, it returns only the first name.
    cout << "Enter new First Name (current: " << guestName[index].substr(0, guestName[index].find(' ')) << "): ";
    cin >> firstName;

    //Returns only the last name, removing all characters after the space.
    cout << "Enter new Last Name (current: " << guestName[index].substr(guestName[index].find(' ') + 1) << "): ";
    cin >> lastName;

    // Updates the guest name
    guestName[index] = firstName + " " + lastName;

    //The user is prompted to enter a new value with the message "Please enter a new Room Number".
    //The user is guided until they enter a valid room number.
    //The newly entered valid room number is assigned to the roomNumber[index] variable.
    roomNumber[index] = Validation::getValidRoomNumber("Please Enter a new Room Number", roomNumber[index]);


    //The user is asked to enter the new check-in date
    int day1, month1, year1;
    cout << "Enter new Check-In Date (current: " << checkInDate[index] << "):\n";
    Validation::getMonth(month1);
    Validation::getYear(year1);
    Validation::getDay(day1, month1, year1);
    checkInDate[index] = to_string(day1) + "/" + to_string(month1) + "/" + to_string(year1);

    //The user is asked to enter the new check-out date
    int day2, month2, year2;
    while (true) {
        cout << "Enter new Check-Out Date (current: " << checkOutDate[index] << "):\n";
        Validation::getMonth(month2);
        Validation::getYear(year2);
        Validation::getDay(day2, month2, year2);

        // Checks if the check-out date is after the check-in date
        if (Validation::calculateDaysBtwDates(day1, month1, year1, day2, month2, year2) > 0){
            break; //End loop when a valid date is entered.
        }
        else {
            cout << "Error: Check-out date must be after check-in date.\n";
        }
    }
    checkOutDate[index] = to_string(day2) + "/" + to_string(month2) + "/" + to_string(year2);
    
    //Automatically calculates and updates the total number of days between check-in and check-out dates
    totalNightStay[index] = Validation::calculateDaysBtwDates(day1, month1, year1, day2, month2, year2 );
    cout << "Total Night of Stay: " << totalNightStay[index] << endl;
   
    // Reservation Status
    int status;
    while (true) {
        cout << "Please Enter Reservation Status (1 = Confirmed, 0 = Rejected): ";
        string input;
        cin >> input;

        if (Validation::isValidStatement(input)) { // Use Validation:: prefix for static method
            status = stoi(input);
            reservationStatus[reservationCount] = status;
            break;
        } else {
            cout << "Please try again.\n";
        }
    }
}


//the selected reservation will be deleted, no index shift will occur during deletion
void deleteReservation(int index) {
    //If the entered index is negative or greater than the number of available reservations, a message is given.
    if (index < 0 || index >= reservationCount) {
        cout << "Invalid reservation index.\n";
        return;
    }

    //After the reservation is deleted, loop moves the index of other records one step to the left.
    for (int i = index; i < reservationCount - 1; i++) {
        reservationNumber[i] = reservationNumber[i + 1];
        guestName[i] = guestName[i + 1];
        roomNumber[i] = roomNumber[i + 1];
        checkInDate[i] = checkInDate[i + 1];
        checkOutDate[i] = checkOutDate[i + 1];
        totalNightStay[i] = totalNightStay[i + 1];
        reservationStatus[i] = reservationStatus[i + 1];
    }
    //Since a reservation is deleted, the total number of reservations is reduced.
    reservationCount--;

    //After the reservation is deleted, the remaining reservations are re-ordered and their numbers are updated
    for (int i = 0; i < reservationCount; i++) {
        reservationNumber[i] = i + 1;
    }

    cout << "Reservation deleted and numbers updated successfully.\n";
}

void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for reading.\n";
        return;
    }

    string line;
    reservationCount = 0;

    while (getline(file, line)) {
        if (reservationCount >= capacity) break;

        stringstream ss(line);
        ss >> reservationNumber[reservationCount];
        ss.ignore();

        getline(ss, guestName[reservationCount], ',');
        ss >> roomNumber[reservationCount];
        ss.ignore();

        getline(ss, checkInDate[reservationCount], ',');
        getline(ss, checkOutDate[reservationCount], ',');

        ss >> totalNightStay[reservationCount];
        ss.ignore();

        // Temporary string to read status
        string status;
        getline(ss, status, ','); // Read as string
        reservationStatus[reservationCount] = (status == "Confirmed"); // Convert to bool

        reservationCount++;
    }

    file.close();
    cout << "Data loaded successfully from file!\n";
}



void saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < reservationCount; i++) {
        file << reservationNumber[i] << ","
             << guestName[i] << ","
             << roomNumber[i] << ","
             << checkInDate[i] << ","
             << checkOutDate[i] << ","
             << totalNightStay[i] << ","
             << (reservationStatus[i] ? "Confirmed" : "Rejected") << "\n"; // Write as string
    }

    file.close();
    cout << "Data saved successfully to file!\n";
}


// Custom function to swap two elements
template <typename T>
void swap_(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Tarihleri karşılaştıran fonksiyon
bool isEarlierDate(const string& date1, const string& date2) {
    stringstream ss1(date1);
    stringstream ss2(date2);

    int year1, month1, day1, year2, month2, day2;
    char delimiter;

    // Tarihleri yıl, ay ve gün olarak ayıralım
    ss1 >> day1 >> delimiter >> month1 >> delimiter >> year1;
    ss2 >> day2 >> delimiter >> month2 >> delimiter >> year2;

    // Yıl, ay ve günü sırasıyla karşılaştıralım
    if (year1 != year2) return year1 > year2;  // Yıl küçükse, date1 daha önce
    if (month1 != month2) return month1 > month2;  // Ay küçükse, date1 daha önce
    return day1 > day2;  // Gün küçükse, date1 daha önce
}

// Helper function to compare based on different fields
bool compareReservations(int i, int j, const string& field) {
    if (field == "reservationNumber")
        return reservationNumber[i] > reservationNumber[j];
    else if (field == "guestName")
        return guestName[i] > guestName[j];
    else if (field == "roomNumber")
        return roomNumber[i] > roomNumber[j];
    else if (field == "checkInDate")
        return isEarlierDate(checkInDate[i], checkInDate[j]);  // Tarih karşılaştırma
    else if (field == "checkOutDate")
        return isEarlierDate(checkOutDate[i], checkOutDate[j]);  // Tarih karşılaştırma
    else if (field == "totalNightStay")
        return totalNightStay[i] > totalNightStay[j];
    else if (field == "reservationStatus")
        return reservationStatus[i] < reservationStatus[j];
    return false; // Default case (should not reach here)
}

// Custom sort function
void customSort(int* indices, int size, const string& field) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compareReservations(indices[j], indices[j + 1], field)) {
                swap_(indices[j], indices[j + 1]);
            }
        }
    }
}


// Sort function
void sortable() {
    // Display sorting options to the user
    cout << "1. Reservation Number" << endl;
    cout << "2. Guest Name" << endl;
    cout << "3. Room Number" << endl;
    cout << "4. Check-in Date" << endl;
    cout << "5. Check-out Date" << endl;
    cout << "6. Total Night Stay" << endl;
    cout << "7. Reservation Status" << endl;
    cout << "Select the field to sort by:" << endl;
    
    int choice;
    cin >> choice;

    string field;
    switch (choice) {
        case 1: field = "reservationNumber"; break;
        case 2: field = "guestName"; break;
        case 3: field = "roomNumber"; break;
        case 4: field = "checkInDate"; break;
        case 5: field = "checkOutDate"; break;
        case 6: field = "totalNightStay"; break;
        case 7: field = "reservationStatus"; break;
        default:
            cout << "Invalid choice!" << endl;
            return;
    }

    // Temporary array to store indices for sorting
    int indices[capacity];
    for (int i = 0; i < reservationCount; i++) {
        indices[i] = i;
    }

    // Sort indices based on the selected field
    customSort(indices, reservationCount, field);

    cout << string(140, '=') << endl;
    printRow("Reservation Number", "Guest Name and Surname", "Room Number",
         "Check-In Date", "Check-Out Date", "Total Nights", "Reservation Status");
    cout << string(140, '=') << endl;

    for (int i = 0; i < reservationCount; i++) {
        int idx = indices[i];

        
        string reservationStatusText = reservationStatus[idx] ? "Confirmed" : "Rejected";

        // Print row without formatting
        printRow(
            to_string(reservationNumber[idx]),  // Reservation number
            guestName[idx],                      // Guest name
            to_string(roomNumber[idx]),          // Room number
            checkInDate[idx],                    // Check-in date
            checkOutDate[idx],                   // Check-out date
            to_string(totalNightStay[idx]),      // Total nights
            reservationStatusText                // Reservation status
        );
    }

    cout << string(140, '=') << endl;
    cout << "Reservations sorted by " << field << " successfully!\n" << endl;
}

void expandTable(int*& reservationNumber, string*& guestName, int*& roomNumber, 
                 string*& checkInDate, string*& checkOutDate, int*& totalNightStay, 
                 bool*& reservationStatus, int& capacity) {
    int newCapacity = capacity + 1; // Double the current capacity

    //Dynamically allocates arrays for operations to take place
    int* newReservationNumber = new int[newCapacity];
    string* newGuestName = new string[newCapacity];
    int* newRoomNumber = new int[newCapacity];
    string* newCheckInDate = new string[newCapacity];
    string* newCheckOutDate = new string[newCapacity];
    int* newTotalNightStay = new int[newCapacity];
    bool* newReservationStatus = new bool[newCapacity];

    // copies information held in previous arrays to new ones
    for (int i = 0; i < capacity; i++) {
        newReservationNumber[i] = reservationNumber[i];
        newGuestName[i] = guestName[i];
        newRoomNumber[i] = roomNumber[i];
        newCheckInDate[i] = checkInDate[i];
        newCheckOutDate[i] = checkOutDate[i];
        newTotalNightStay[i] = totalNightStay[i];
        newReservationStatus[i] = reservationStatus[i];
    }

    //Allows deletion of previously created arrays
    delete[] reservationNumber;
    delete[] guestName;
    delete[] roomNumber;
    delete[] checkInDate;
    delete[] checkOutDate;
    delete[] totalNightStay;
    delete[] reservationStatus;

    //Updates and assigns pointers and arrays' capacity
    reservationNumber = newReservationNumber;
    guestName = newGuestName;
    roomNumber = newRoomNumber;
    checkInDate = newCheckInDate;
    checkOutDate = newCheckOutDate;
    totalNightStay = newTotalNightStay;
    reservationStatus = newReservationStatus;

    capacity = newCapacity;
    cout << "Table capacity expanded to: " << newCapacity << endl;

}
