#ifndef VALIDATION_H
#define VALIDATION_H
#include <string>
using namespace std;

class Validation {
public:
    static bool isLeapYear(int year); //Checking whether a year is a leap year
    static bool isValidDay(int day, int month, int year); //checks the number of days in the month
    static bool isValidMonth(int month); //Checks if a month is between 1 and 12
    static bool isValidYear(int year); //Restricts the entered year to certain intervals
    static bool isNumeric(const string& input); // Checks whether each character of an entered string value is a number or not
    static void getDay(int& day, int month, int year); //Gets and checks the user's day entry for check-in and check-out dates
    static void getMonth(int& month); //Gets and checks the user's month input for check-in and check-out dates
    static void getYear(int& year); //Gets and checks the year input from the user for check-in and check-out dates
    static int getDaysInMonth(int month, int year); // restricts the number of days in the current month according to general rules
    static int calculateDaysBtwDates(int day1, int month1, int year1, int day2, int month2, int year2); //calculates the day difference between the entered check-in and check-out dates
    static int getValidRoomNumber(const std::string& prompt, int currentRoomNumber = 0); // checks whether the room number received from the user is available or not
    static bool isValidStatement(const std::string& input); //Checks if the cases are a valid reservation status
};

#endif