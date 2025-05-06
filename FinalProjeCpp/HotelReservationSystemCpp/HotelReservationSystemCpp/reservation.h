#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>
#include <iostream>
#include <iomanip>

using namespace std; 
extern int capacity; 
extern int reservationCount;

extern int* reservationNumber; // Global dynamic array holding reservation numbers
extern string* guestName; // Global dynamic array holding guest names and surnames in the reservation
extern int* roomNumber; // Global dynamic array holding reservation room number
extern string* checkInDate; // Global dynamic array holding check-in dates.
extern string* checkOutDate; // Global dynamic array holding check-out dates.
extern int* totalNightStay; // Global dynamic array holding the total number of nights.
extern bool* reservationStatus; // Global dynamic array holding reservation statuses.

// Function prototypes

//Uploads the file of reservations
void loadFromFile(const string& filename); 
//A new reservation is added
void insertNewReservation(int*& reservationNumber, string*& guestName, int*& roomNumber, 
                          string*& checkInDate, string*& checkOutDate, int*& totalNightStay, 
                          bool*& reservationStatus, int& capacity); 
//Reservation search is performed
void findReservation(); 
//All reservations are listed
void listReservations(); 
//All reservations that contain a key are listed
void displayReservation(int index); 
//All titles of the selected reservation can be edited
void editReservation(int index); 
//The selected reservation will be deleted
void deleteReservation(int index); 
//It saves the entered reservations to the reservation.txt
void saveToFile(const string& filename); 
//Sorts reservations according to a criterion
void sortable(); 
//Increases the capacity of reservation arrays
void expandTable(int*& reservationNumber, string*& guestName, int*& roomNumber, 
                 string*& checkInDate, string*& checkOutDate, int*& totalNightStay, 
                 bool*& reservationStatus, int& capacity);

#endif