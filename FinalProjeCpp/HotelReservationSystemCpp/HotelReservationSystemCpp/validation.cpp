#include "validation.h"
#include <iostream>
#include <stdexcept>
#include <string>

// if the year is divisible by 4, that year is a leap year
bool Validation::isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

//checks the number of days in the month
bool Validation::isValidDay(int day, int month, int year) {
    if (month == 2){
        if (isLeapYear(year)){
            return (day >= 1 && day <= 29); //when it's a leap year, it's 29
        }
        return (day >= 1 && day <= 28);
    }
    //For those who take 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return (day >= 1 && day <= 30);
    }

    return (day >= 1 && day <= 31);
}

// guarantees that there cannot be more or less than the number of months in a year
bool Validation::isValidMonth(int month){
    return (month >=1 && month <=12);
}

// restricts the entered year to certain intervals
bool Validation::isValidYear(int year){
    return (year >= 1950 && year <= 2060);
}

// Checks whether each character of an entered string value is a number or not
bool Validation::isNumeric(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return !input.empty();
}

//gets and checks the user's day entry for check-in and check-out dates
void Validation::getDay(int& day, int month, int year){
    string input;
    bool valid = false;

    while (!valid){  //loop continues until there is a correct input
        cout << "Please enter the day: ";
        cin >> input;

        if (isNumeric(input)) { // if input is numeric
            day = stoi(input); //convert string to integer
            valid = isValidDay(day, month, year); //do date checks
        }

        if (!valid){ //throw an error message if the input is not correct
            cout << "Invalid day. Please try again.\n";
        }
    }
}

//gets and checks the user's month input for check-in and check-out dates
void Validation::getMonth(int& month){
    string input;
    bool valid = false;
    while (!valid){ //loop continues until there is a correct input
        cout << "Please enter the month: ";
        cin >> input;

        if (isNumeric(input)) { // if input is numeric
            month = stoi(input); //convert string to integer
            valid = isValidMonth(month); //do month validation checks
        }

        if (!valid){ //throw an error message if the input is not correct
            cout << "Invalid month. Please try again.\n";
        }
    }
}

//gets and checks the year input from the user for check-in and check-out dates
void Validation::getYear(int& year) {
    string input;
    bool valid = false;

    while (!valid){ //loop continues until there is a correct input
        cout << "Please enter the year: ";
        cin >> input;

        if (isNumeric(input)) { // if input is numeric
            year = stoi(input); //convert string to integer
            valid = isValidYear(year); //do year validation checks
        }

        if (!valid){ //throw an error message if the input is not correct
            cout << "Invalid year. Please try again.\n";
        }
    }
}

// restricts the number of days in the current month according to general rules
int Validation::getDaysInMonth(int month, int year) {
    if (month == 2) { // if February
        return (isLeapYear(year)) ? 29 : 28; //check is it leap year if leap yerar 29 else 28
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) { // Months with 30 days
        return 30;
    }
    return 31; // Months with 31 days
}

//calculates the day difference between the entered check-in and check-out dates
int Validation::calculateDaysBtwDates(int day1, int month1, int year1, int day2, int month2, int year2){
    int totalDay1 = 0;
    int totalDay2 = 0;

    for (int i = 1; i < year1; i++){ //total number of days of the first date is calculated
        totalDay1 += (isLeapYear(i)) ? 366 : 365; // leap year control
    }
    
    for (int i = 1; i < month1; i++){ //number of days and months until the first date is added
        totalDay1 += getDaysInMonth(i, year1 );
    }
    totalDay1 += day1;

    for (int i = 1; i < year2; i++){ //total number of days of the second date is calculated
        totalDay2 += (isLeapYear(i)) ? 366 : 365; // leap year control
    }
    
    for (int i = 1; i < month2; i++){ //number of days and months until the second date is added
        totalDay2 += getDaysInMonth(i, year2 );
    }

    totalDay2 += day2;
    
    return totalDay2 - totalDay1; // the difference between two dates is calculated and returned in days

}

// checks whether the room number received from the user is available or not
int Validation::getValidRoomNumber(const string& prompt, int currentRoomNumber) { //The parameters are the message that will appear to the user and the current room number.
    int roomNumber = 0; //hold the room number
    bool validRoom = false; //checker flag
    while (!validRoom) { //loop continues until there is a correct input
        if (currentRoomNumber > 0) {
            cout << prompt << " (current: " << currentRoomNumber << "): ";
        } else {
            cout << prompt << ": ";
        }
        
        string input; //The value entered by the user is assigned to the input variable
        cin >> input;

        validRoom = !input.empty(); //check if there is an input
        for (char c : input) {
            if (!isdigit(c)) {
                validRoom = false; //If input characters are not digits
                break;
            }
        }

        if (validRoom) {
            try {
                roomNumber = stoi(input); //convert input string to integer
                if (roomNumber > 0) { //check if the room number positive
                    validRoom = true;
                } else {
                    throw invalid_argument("Room number must be positive!");
                }
            } catch (const exception&) { //if cant convert because an exception
                validRoom = false;
                cout << "Invalid input! Please enter a positive integer.\n";
            }
        }

        if (!validRoom) { // If it is not valid
            cout << "Invalid room number! Please enter a valid number.\n";
        }
    }
    return roomNumber; // Default return
}

//Checks if the cases are a valid reservation status
bool Validation::isValidStatement(const string& input) {
    // Check if input is not empty and all characters are digits
    if (input.empty()) {
        cout << "Invalid reservation status.\n";
        return false;
    }

    for (char c : input) {
        if (!isdigit(c)) {
            cout << "Invalid reservation status.\n";
            return false;
        }
    }

    // Convert the input to an integer and check if it's 0 or 1
    int status = stoi(input);
    if (status == 0 || status == 1) {
        return true;
    } 
    else {
        cout << "Invalid reservation status.\n";
        return false;
    }
}


