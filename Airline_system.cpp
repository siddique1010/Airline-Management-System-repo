#include <iostream>
#include <string>
#include <conio.h>
#include <cctype>
#include <iomanip>
#include <windows.h>// system function like sleep , clear screen 
#include <fstream>
//#include <cstdio>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define MAGENTA "\033[35m"

string adminId = "a";
string adminPassword = "a";
int reservationCounter = 1000;

// Function prototypes
void mainMenu();
void adminMenu();
void passengerMenu(string userId);
bool adminLogin();
bool passengerLogin();
void passengerSignup();
void addFlight();
void viewFlights();
void searchFlight();
void updateFlight();
void deleteFlight();
void addPassengerAdmin();
void viewPassengers();
void searchPassenger();
void updatePassenger();
void deletePassenger();
void bookFlight(string userId);
void cancelReservation(string userId);
void viewAvailableFlights();
void personalReport(string userId);
void viewMyReservations(string userId);
void managePassengers();
void systemReports();

          // yaha sa validations functions ki prototype start ho rie hain
int integerInput();
string enterName();
string enterPhone();
string enterDate();
string enterTime();
string enterFlightNumber();
string enterCity();
string enterUserId();
double enterFare(string seatType);
bool validateDate(string date);
bool validateTime(string time);
bool validatePhone(string phone);

// ========== MAIN FUNCTION ==========
int main() {
    system("cls");
    // Create files if they don't exist
    ofstream f1("flights.txt", ios::app);
    f1.close();
    ofstream f2("passengers.txt", ios::app);
    f2.close();
    ofstream f3("reservations.txt", ios::app);
    f3.close();
    
    mainMenu();
    return 0;
}

// ========== MAIN MENU ==========
void mainMenu() {
    int choice;
    
    while (true) {
        system("cls");
        cout << YELLOW;
        cout << "\n\n";
        cout << "\t\t\t\t\t\t==================================\n";
        cout << "\t\t\t\t\t\t     AIRLINE RESERVATION SYSTEM\n";
        cout << "\t\t\t\t\t\t==================================\n\n";
        cout << RESET;
        
        cout << YELLOW << "\t\t\t\t\t[--- ADMINISTRATION ---]" << WHITE << "    " 
             << YELLOW << "[--- PASSENGER SERVICES ---]\n" << RESET;
        cout << YELLOW <<  "\t\t\t\t\t********************************************************\n\n" << RESET ;
        
        cout << "\t\t\t\t\t    " << "1. Admin Login" << "                " << "2. Passenger Login\n" ;
        cout << "\t\t\t\t\t    " << "3. Add Flight" << "                 " << "4. Book Flight (Guest)\n" ;
        cout << "\t\t\t\t\t    " << "5. View All Flights" << "           " << "6. View Available Flights\n" ;
        cout << "\t\t\t\t\t    " << "7. Manage Passengers" << "          " << "8. My Reservations\n" ;
        cout << "\t\t\t\t\t    " << "9. System Reports"  << "            " << "10. Passenger Sign Up\n" ;
        cout << "\t\t\t\t\t    " << "11. Search Flight" << "             "<< "0." << RED << "EXIT\n" << RESET;
        
        cout << "\n\t\t\t\t\t\t" << WHITE << "Enter choice: " << RESET;
        choice = integerInput();
        
        switch (choice) {
            case 1:
                if (adminLogin()) 
                    adminMenu();
                break;
            case 2:
                passengerLogin();
                break;
            case 3:
                addFlight();
                break;
            case 4:
                cout << RED << "\n\t\t\t\t\tPlease sign up or login to book.......\n" << RESET;
                Sleep(1500);
                break;
            case 5:
                viewFlights();
                break;
            case 6:
                viewAvailableFlights();
                break;
            case 7:
                managePassengers();
                break;
            case 8:
                cout << RED << "\n\t\t\t\t\tPlease login to view reservations!\n" << RESET;
                Sleep(1500);
                break;
            case 9:
                systemReports();
                break;
            case 10: 
                passengerSignup();
                break;
            case 11:
                searchFlight();
                break;
            case 0:
                cout << GREEN << "\n\n\t\t\t\t\t\tThank you! Goodbye!" << RESET << endl;
                Sleep(2000);
                return;
            default:
                cout << RED << "\n\t\t\t\t\t\tInvalid choice!" << RESET << endl;
                Sleep(1000);
        }
    }
}

// ========== ADMIN LOGIN ==========
bool adminLogin() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t  [------- ADMIN LOGIN -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 33; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    string id, pass;
    cout << "\t\t\t\t\t\tEnter Admin ID: ";
    cin >> id;
    cout << "\t\t\t\t\t\tEnter Password: ";
    cin >> pass;
    cin.ignore();
    
    if (id == adminId && pass == adminPassword) {
        cout << GREEN << "\n\t\t\t\t\t\tLogin successful!" << RESET << endl;
        Sleep(1000);
        return true;
    } else {
        cout << RED << "\n\t\t\t\t\t\tInvalid credentials!" << RESET << endl;
        Sleep(1500);
        return false;
    }
}

// ========== PASSENGER LOGIN ==========
bool passengerLogin() {
    system("cls");
    cout << YELLOW;
    cout << "\n\n\t\t\t\t\t\t[------- PASSENGER LOGIN -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 30; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    string userId, password;
    cout << "\t\t\t\t\t\tEnter User ID: ";
    userId = enterUserId();
    cout << "\t\t\t\t\t\tEnter Password: ";
    cin >> password;
    cin.ignore();
    
    ifstream file("passengers.txt");
    if (!file) {
        cout << RED << "\n\t\t\t\t\tNo passengers registered yet!\n" << RESET;
        Sleep(1500);
        return false;
    }
    
    string id, pass, name, phone;
    int bookings;
    double spent;
    bool found = false;
    
    while (file >> id >> pass >> name >> phone >> bookings >> spent) {
        if (id == userId && pass == password) {
            found = true;
            cout << GREEN << "\n\t\t\t\t\t\tWelcome " << name << "!" << RESET << endl;
            Sleep(1000);
            file.close();
            passengerMenu(userId);
            return true;
        }
    }
    
    file.close();
    
    if (!found) {
        cout << RED << "\n\t\t\t\t\t\tInvalid login!" << RESET << endl;
        Sleep(1500);
    }
    return false;
}

// ========== PASSENGER SIGNUP ==========
void passengerSignup() {
    system("cls");
    cout << BLUE;
    cout << "\n\n\t\t\t\t\t\t[------- PASSENGER SIGN UP -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 32; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    string userId, password, name, phone;
    
    cout << "\t\t\t\t\t\tEnter User ID (6-10 chars): ";
    userId = enterUserId();
    
    ifstream checkFile("passengers.txt");
    string existingId;
    bool exists = false;
    
    if (checkFile) {
        while (checkFile >> existingId) {
            if (existingId == userId) {
                exists = true;
                break;
            }
            string dummy;
            getline(checkFile, dummy);
        }
        checkFile.close();
    }
    
    if (exists) {
        cout << RED << "\n\t\t\t\t\tUser ID already exists!\n" << RESET;
        Sleep(1500);
        return;
    }
    
    cout << "\t\t\t\t\t\tEnter Password: ";
    cin >> password;
    cin.ignore();
    
    cout << "\t\t\t\t\t\tEnter Name: ";
    name = enterName();
    
    cout << "\t\t\t\t\t\tEnter Phone (03XX-XXXXXXX format): ";
    phone = enterPhone();
    
    ofstream file("passengers.txt", ios::app);
    file << userId << " " << password << " " << name << " " 
         << phone << " 0 0.00" << endl;
    file.close();
    
    cout << GREEN << "\n\t\t\t\t\t\tSignup successful!" << RESET << endl;
    Sleep(2000);
}

// ========== ADMIN MENU ==========
void adminMenu() {
    int choice;
    cout << RESET ;
    while (true) {
        system("cls");
        cout << YELLOW;
        cout << "\n\n\t\t\t\t\t\t     [------- ADMIN MENU -------]\n";
        cout << "\t\t\t\t\t         ***********************************";
        cout << "\n\n" << RESET;
        
        cout << GREEN << "\t\t\t\t\t[--- FLIGHT MANAGEMENT ---]" << WHITE << "    " 
             << GREEN << "[--- PASSENGER MANAGEMENT ---]\n" << RESET;
        cout << "\t\t\t\t\t*************************************************************\n\n";
        
        cout << "\t\t\t\t\t    " << "1. Add Flight" << "                " << "6. Add Passenger(s)\n" ;
        cout << "\t\t\t\t\t    " << "2. View All Flights"  << "          " << "7. View All Passengers\n" ;
        cout << "\t\t\t\t\t    " << "3. Search Flight"  << "             " << "8. Search Passenger\n" ;
        cout << "\t\t\t\t\t    " << "4. Update Flight"  << "             " << "9. Update Passenger\n" ;
        cout << "\t\t\t\t\t    " << "5. Delete Flight"  << "            " << "10. Delete Passenger\n" ;
        cout << "\t\t\t\t\t    " << "11. System Reports"<< "           " << "0." <<  RED << "Logout\n\n" ;
        
        cout << "\t\t\t\t\t\t    " << WHITE << "Enter choice: " << RESET;
        choice = integerInput();
        
        switch (choice) {
            case 1: addFlight(); break;
            case 2: viewFlights(); break;
            case 3: searchFlight(); break;
            case 4: updateFlight(); break;
            case 5: deleteFlight(); break;
            case 6: addPassengerAdmin(); break;
            case 7: viewPassengers(); break;
            case 8: searchPassenger(); break;
            case 9: updatePassenger(); break;
            case 10: deletePassenger(); break;
            case 11: systemReports(); break;
            case 0:
                cout << "\n\t\t\t\t\t\tLogging out..." << endl;
                Sleep(1000);
                return;
            default:
                cout << RED << "\n\t\t\t\t\t\tInvalid choice!" << RESET << endl;
                Sleep(1000);
        }
    }
}

// ========== PASSENGER MENU ==========
void passengerMenu(string userId) {
    int choice;
    
    while (true) {
        system("cls");
        cout << YELLOW;
        cout << "\n\n\t\t\t\t\t\t[------- PASSENGER MENU -------]\n";
        cout << "\t\t\t\t\t***************************************\n\n" << RESET;
        
        cout << "\t\t\t\t\t\t    " << BLUE << "1. Book Flight\n" << RESET;
        cout << "\t\t\t\t\t\t    " << BLUE << "2. Cancel Reservation\n" << RESET;
        cout << "\t\t\t\t\t\t    " << BLUE << "3. View Available Flights\n" << RESET;
        cout << "\t\t\t\t\t\t    " << BLUE << "4. My Report\n" << RESET;
        cout << "\t\t\t\t\t\t    " << BLUE << "5. View My Reservations\n" << RESET;
        cout << "\t\t\t\t\t\t    " << BLUE << "6. Search Flight\n" << RESET;
        cout << "\t\t\t\t\t\t    " << YELLOW << "0. Logout\n\n" << RESET;
        
        cout << "\t\t\t\t\t\t    " << WHITE << "Enter choice: " << RESET;
        choice = integerInput();
        
        switch (choice) {
            case 1: bookFlight(userId); break;
            case 2: cancelReservation(userId); break;
            case 3: viewAvailableFlights(); break;
            case 4: personalReport(userId); break;
            case 5: viewMyReservations(userId); break;
            case 6: searchFlight(); break;
            case 0:
                cout << "\n\t\t\t\t\t\tLogging out..." << endl;
                Sleep(1000);
                return;
            default:
                cout << RED << "\n\t\t\t\t\t\tInvalid choice!" << RESET << endl;
                Sleep(1000);
        }
    }
}

// ========== FLIGHT FUNCTIONS ==========
void addFlight() {
    system("cls");
    cout << CYAN;
    cout << "\n\n\t\t\t\t\t\t[------- ADD NEW FLIGHT -------]\n";
    cout << "\t\t\t\t\t\t***********************************";
    cout << "\n\n" << RESET;
    
    string flightNo, departure, destination, date, time;
    int economySeats, businessSeats;
    double economyFare, businessFare;
    
    cout << "\t\t\t\t\t\tFlight Number (AA123): ";
    flightNo = enterFlightNumber();
    
    cout << "\t\t\t\t\t\tDeparture City: ";
    departure = enterCity();
    
    cout << "\t\t\t\t\t\tDestination City: ";
    destination = enterCity();
    
    cout << "\t\t\t\t\t\tDate (DD-MM-YYYY): ";
    date = enterDate();
    
    cout << "\t\t\t\t\t\tTime (HH:MM): ";
    time = enterTime();
    
    cout << "\t\t\t\t\t\tEconomy Seats (1-500): ";
    economySeats = integerInput();
    while (economySeats < 1 || economySeats > 500) {
        cout << RED << "\t\t\t\t\t\tInvalid! Enter (1-500): " << RESET;
        economySeats = integerInput();
    }
    
    // Business seats can't be more than economy seats
    cout << "\t\t\t\t\t\tBusiness Seats (1-" << economySeats << "): ";
    businessSeats = integerInput();
    while (businessSeats < 1 || businessSeats > economySeats) {
        cout << RED << "\t\t\t\t\t\tInvalid! Must be ≤ " << economySeats << ": " << RESET;
        businessSeats = integerInput();
    }
    
    economyFare = enterFare("Economy");
    
    // Business fare must be higher than economy fare
    cout << "\t\t\t\t\t\tBusiness fare (must be > $" << (int)economyFare << "): $";
    businessFare = enterFare("Business");
    while (businessFare <= economyFare) {
        cout << RED << "\t\t\t\t\t\tBusiness fare must be higher than economy!\n" << RESET;
        cout << "\t\t\t\t\t\tEnter business fare (>$" << (int)economyFare << "): $";
        businessFare = enterFare("Business");
    }
    
    int totalSeats = economySeats + businessSeats;
    
    ofstream file("flights.txt", ios::app);
    file << flightNo << " " << departure << " " << destination << " " 
         << date << " " << time << " " << totalSeats << " " 
         << economySeats << " " << businessSeats << " " 
         << economyFare << " " << businessFare << " Available" << endl;
    file.close();
    
    cout << GREEN << "\n\t\t\t\t\t\tFlight added successfully!" << RESET << endl;
    Sleep(1500);
}

void viewFlights() {
    system("cls");
    cout << CYAN;
    cout << "\n\n\t\t\t\t\t\t[------- ALL FLIGHTS -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 27; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    ifstream file("flights.txt");
    if (!file) {
        cout << RED << "\t\t\t\t\t\tNo flights found!\n" << RESET;
        Sleep(2000);
        return;
    }
    
    cout << WHITE << "\t" << string(120, '-') << endl;
    cout << "\t" << left << setw(12) << "Flight" 
         << setw(15) << "Departure"
         << setw(15) << "Destination"
         << setw(12) << "Date"
         << setw(10) << "Time"
         << setw(8) << "Eco"
         << setw(8) << "Bus"
         << setw(10) << "Eco Fare"
         << setw(10) << "Bus Fare"
         << setw(12) << "Status" << endl;
    cout << "\t" << string(120, '-') << endl;
    cout << RESET;
    
    string flightNo, departure, destination, date, time, status;
    int totalSeats, economySeats, businessSeats;
    double economyFare, businessFare;
    
    while (file >> flightNo >> departure >> destination >> date >> time 
          >> totalSeats >> economySeats >> businessSeats 
          >> economyFare >> businessFare >> status) {
        cout << "\t" << left << setw(12) << flightNo
             << setw(15) << departure
             << setw(15) << destination
             << setw(12) << date
             << setw(10) << time
             << setw(8) << economySeats
             << setw(8) << businessSeats
             << "$" << setw(9) << fixed << setprecision(2) << economyFare
             << "$" << setw(9) << businessFare
             << setw(12) << status << endl;
    }
    
    file.close();
    cout << GREEN << "\n\t\t\t\t\t\tDisplaying all flights..." << RESET << endl;
    Sleep(3000);
}

void searchFlight() {
    system("cls");
    cout << CYAN;
    cout << "\n\n\t\t\t\t\t\t[------- SEARCH FLIGHT -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 29; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    cout << "\t\t\t\t\t\t" << CYAN << "1. Flight Number\n" << RESET;
    cout << "\t\t\t\t\t\t" << CYAN << "2. Destination City\n\n" << RESET;
    
    cout << "\t\t\t\t\t\t" << WHITE << "Enter choice: " << RESET;
    int choice = integerInput();
    while (choice < 1 || choice > 2) {
        cout << RED << "\t\t\t\t\t\tInvalid! Enter (1-2): " << RESET;
        choice = integerInput();
    }
    
    string searchTerm;
    if (choice == 1) {
        cout << "\t\t\t\t\t\tEnter Flight Number: ";
        searchTerm = enterFlightNumber();
    } else {
        cout << "\t\t\t\t\t\tEnter Destination City: ";
        searchTerm = enterCity();
    }
    
    ifstream file("flights.txt");
    if (!file) {
        cout << RED << "\n\t\t\t\t\t\tNo flights in database!\n" << RESET;
        Sleep(1500);
        return;
    }
    
    string flightNo, departure, destination, date, time, status;
    int totalSeats, economySeats, businessSeats;
    double economyFare, businessFare;
    bool found = false;
    
    cout << WHITE << "\n\t" << string(60, '=') << endl;
    cout << "\t\t\tSEARCH RESULTS\n";
    cout << "\t" << string(60, '=') << endl;
    cout << RESET;
    
    while (file >> flightNo >> departure >> destination >> date >> time 
          >> totalSeats >> economySeats >> businessSeats 
          >> economyFare >> businessFare >> status) {
        
        bool match = false;
        if (choice == 1 && flightNo == searchTerm) {
            match = true;
        } else if (choice == 2 && destination.find(searchTerm) != string::npos) {
            match = true;
        }
        
        if (match) {
            found = true;
            cout << CYAN << "\n\t" << string(50, '-') << endl;
            cout << "\tFlight: " << flightNo << endl;
            cout << "\tRoute: " << departure << " → " << destination << endl;
            cout << "\tDate: " << date << " | Time: " << time << endl;
            cout << "\tEconomy: " << economySeats << " seats @ $" << economyFare << endl;
            cout << "\tBusiness: " << businessSeats << " seats @ $" << businessFare << endl;
            cout << "\tStatus: " << status << endl;
            cout << RESET;
        }
    }
    
    file.close();
    
    if (!found) {
        cout << RED << "\n\t\t\tNo flights found!" << RESET << endl;
    }
    Sleep(3000);
}

// ========== POINTER EXAMPLE ==========
void updateFlight() {
    system("cls");
    cout << CYAN;
    cout << "\n\n\t\t\t\t\t\t[------- UPDATE FLIGHT -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 29; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    cout << "\t\t\t\t\t\tFlight Number: ";
    string flightNo = enterFlightNumber();
    
    ifstream inFile("flights.txt");
    if (!inFile) {
        cout << RED << "\n\t\t\t\t\t\tNo flights in database!\n" << RESET;
        Sleep(1500);
        return;
    }
    
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;
    
    while (getline(inFile, line)) {
        size_t pos1 = line.find(' ');
        string fNo = line.substr(0, pos1);
        
        if (fNo == flightNo) {
            found = true;
            
            // Using pointer for formality
            string* linePtr = &line;
            
            // Get current values
            size_t pos2 = line.find(' ', pos1 + 1);
            size_t pos3 = line.find(' ', pos2 + 1);
            size_t pos4 = line.find(' ', pos3 + 1);
            size_t pos5 = line.find(' ', pos4 + 1);
            size_t pos6 = line.find(' ', pos5 + 1);
            size_t pos7 = line.find(' ', pos6 + 1);
            size_t pos8 = line.find(' ', pos7 + 1);
            size_t pos9 = line.find(' ', pos8 + 1);
            size_t pos10 = line.find(' ', pos9 + 1);
            
            string departure = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string destination = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string date = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string time = line.substr(pos4 + 1, pos5 - pos4 - 1);
            string totalSeatsStr = line.substr(pos5 + 1, pos6 - pos5 - 1);
            string economySeatsStr = line.substr(pos6 + 1, pos7 - pos6 - 1);
            string businessSeatsStr = line.substr(pos7 + 1, pos8 - pos7 - 1);
            string economyFareStr = line.substr(pos8 + 1, pos9 - pos8 - 1);
            string businessFareStr = line.substr(pos9 + 1, pos10 - pos9 - 1);
            string status = line.substr(pos10 + 1);
            
            int ecoSeats = stoi(economySeatsStr);
            int busSeats = stoi(businessSeatsStr);
            double ecoFare = stod(economyFareStr);
            double busFare = stod(businessFareStr);
            
            cout << CYAN << "\n\t\t\t\t\t\tCurrent Details:\n" << RESET;
            cout << "\t\t\t\t\t\tDeparture: " << departure << endl;
            cout << "\t\t\t\t\t\tDestination: " << destination << endl;
            cout << "\t\t\t\t\t\tDate: " << date << endl;
            cout << "\t\t\t\t\t\tTime: " << time << endl;
            cout << "\t\t\t\t\t\tEconomy Seats: " << ecoSeats << endl;
            cout << "\t\t\t\t\t\tBusiness Seats: " << busSeats << endl;
            cout << "\t\t\t\t\t\tEconomy Fare: $" << ecoFare << endl;
            cout << "\t\t\t\t\t\tBusiness Fare: $" << busFare << endl;
            
            cout << CYAN << "\n\t\t\t\t\t\tEnter new details:\n" << RESET;
            
            cout << "\t\t\t\t\t\tNew Departure City: ";
            string newDeparture = enterCity();
            
            cout << "\t\t\t\t\t\tNew Destination City: ";
            string newDestination = enterCity();
            
            cout << "\t\t\t\t\t\tNew Date: ";
            string newDate = enterDate();
            
            cout << "\t\t\t\t\t\tNew Time: ";
            string newTime = enterTime();
            
            cout << "\t\t\t\t\t\tNew Economy Seats (1-500): ";
            int newEcoSeats = integerInput();
            while (newEcoSeats < 1 || newEcoSeats > 500) {
                cout << RED << "\t\t\t\t\t\tInvalid! Enter (1-500): " << RESET;
                newEcoSeats = integerInput();
            }
            
            // Business seats can't be more than economy seats
            cout << "\t\t\t\t\t\tNew Business Seats (1-" << newEcoSeats << "): ";
            int newBusSeats = integerInput();
            while (newBusSeats < 1 || newBusSeats > newEcoSeats) {
                cout << RED << "\t\t\t\t\t\tInvalid! Must be ≤ " << newEcoSeats << ": " << RESET;
                newBusSeats = integerInput();
            }
            
            cout << "\t\t\t\t\t\tNew Economy Fare: ";
            double newEcoFare = enterFare("Economy");
            
            // Business fare must be higher than economy fare
            cout << "\t\t\t\t\t\tNew Business fare (must be > $" << (int)newEcoFare << "): $";
            double newBusFare = enterFare("Business");
            while (newBusFare <= newEcoFare) {
                cout << RED << "\t\t\t\t\t\tBusiness fare must be higher than economy!\n" << RESET;
                cout << "\t\t\t\t\t\tEnter business fare (>$" << (int)newEcoFare << "): $";
                newBusFare = enterFare("Business");
            }
            
            int newTotal = newEcoSeats + newBusSeats;
            string newStatus = (newTotal > 0) ? "Available" : "Full";
            
            tempFile << fNo << " " << newDeparture << " " << newDestination << " " 
                     << newDate << " " << newTime << " " << newTotal << " " 
                     << newEcoSeats << " " << newBusSeats << " " 
                     << newEcoFare << " " << newBusFare << " " << newStatus << endl;
        } else {
            tempFile << line << endl;
        }
    }
    
    inFile.close();
    tempFile.close();
    
    if (found) {
        remove("flights.txt");
        rename("temp.txt", "flights.txt");
        cout << GREEN << "\n\t\t\t\t\t\tFlight updated successfully!" << RESET << endl;
    } else {
        remove("temp.txt");
        cout << RED << "\n\t\t\t\t\t\tFlight not found!" << RESET << endl;
    }
    Sleep(1500);
}

void deleteFlight() {
    system("cls");
    cout << CYAN;
    cout << "\n\n\t\t\t\t\t\t[------- DELETE FLIGHT -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i = 29; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    cout << "\t\t\t\t\t\tFlight Number: ";
    string flightNo = enterFlightNumber();
    
    ifstream inFile("flights.txt");
    if (!inFile) {
        cout << RED << "\n\t\t\t\t\t\tNo flights in database!\n" << RESET;
        Sleep(1500);
        return;
    }
    
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;
    
    while (getline(inFile, line)) {
        size_t pos = line.find(' ');
        string fNo = line.substr(0, pos);
        
        if (fNo == flightNo) {
            found = true;
            continue;
        }
        tempFile << line << endl;
    }
    
    inFile.close();
    tempFile.close();
    
    if (found) {
        remove("flights.txt");
        rename("temp.txt", "flights.txt");
        cout << GREEN << "\n\t\t\t\t\t\tFlight deleted successfully!" << RESET << endl;
    } else {
        remove("temp.txt");
        cout << RED << "\n\t\t\t\t\t\tFlight not found!" << RESET << endl;
    }
    Sleep(1500);
}

// ========== PASSENGER MANAGEMENT ==========
void managePassengers() {
    if (!adminLogin()) return;
    
    int choice;
    while (true) {
        system("cls");
        cout << BLUE;
        cout << "\n\n\t\t\t\t\t\t[------- MANAGE PASSENGERS -------]\n";
        cout << "\t\t\t\t\t\t";
        for (int i = 0; i < 33; i++) {
            cout << "*";
        }
        cout << "\n\n" << RESET;
        
        cout << "\t\t\t\t\t\t    " << BLUE << "1. Add Passenger(s)\n" << RESET;
        cout << "\t\t\t\t\t\t    " << BLUE << "2. View All Passengers\n" << RESET;
        cout << "\t\t\t\t\t\t    " << BLUE << "3. Search Passenger\n" << RESET;
        cout << "\t\t\t\t\t\t    " << BLUE << "4. Update Passenger\n" << RESET;
        cout << "\t\t\t\t\t\t    " << BLUE << "5. Delete Passenger\n" << RESET;
        cout << "\t\t\t\t\t\t    " << YELLOW << "0. Back to Main Menu\n\n" << RESET;
        
        cout << "\t\t\t\t\t\t    " << WHITE << "Enter choice: " << RESET;
        choice = integerInput();
        
        switch (choice) {
            case 1: addPassengerAdmin(); break;
            case 2: viewPassengers(); break;
            case 3: searchPassenger(); break;
            case 4: updatePassenger(); break;
            case 5: deletePassenger(); break;
            case 0: return;
            default:
                cout << RED << "\n\t\t\t\t\t\tInvalid choice!" << RESET << endl;
                Sleep(1000);
        }
    }
}

void addPassengerAdmin() {
    system("cls");
    cout << BLUE;
    cout << "\n\n\t\t\t\t\t\t[------- ADD PASSENGER(S) -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 32; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    cout << "\t\t\t\t\t\tHow many passengers? (1-10): ";
    int count = integerInput();
    while (count < 1 || count > 10) {
        cout << RED << "\t\t\t\t\t\tInvalid! Enter (1-10): " << RESET;
        count = integerInput();
    }
    
    for (int i = 0; i < count; i++) {
        cout << "\n\t\t\t\t\t\t--- Passenger " << i+1 << " of " << count << " ---\n";
        
        string userId, password, name, phone;
        
        cout << "\t\t\t\t\t\tUser ID (6-10 chars): ";
        userId = enterUserId();
        
        ifstream check("passengers.txt");
        string existingId;
        bool exists = false;
        
        if (check) {
            while (check >> existingId) {
                if (existingId == userId) {
                    exists = true;
                    break;
                }
                string dummy;
                getline(check, dummy);
            }
            check.close();
        }
        
        if (exists) {
            cout << RED << "\t\t\t\t\t\tUser ID exists! Skipping...\n" << RESET;
            continue;
        }
        
        cout << "\t\t\t\t\t\tPassword: ";
        cin >> password;
        cin.ignore();
        
        cout << "\t\t\t\t\t\tName: ";
        name = enterName();
        
        cout << "\t\t\t\t\t\tPhone (03XX-XXXXXXX format): ";
        phone = enterPhone();
        
        ofstream file("passengers.txt", ios::app);
        file << userId << " " << password << " " << name << " " 
             << phone << " 0 0.00" << endl;
        file.close();
        
        cout << GREEN << "\t\t\t\t\t\tAdded: " << userId << RESET << endl;
    }
    
    cout << GREEN << "\n\t\t\t\t\t\tAll passengers added!" << RESET << endl;
    Sleep(2000);
}

void viewPassengers() {
    system("cls");
    cout << BLUE;
    cout << "\n\n\t\t\t\t\t\t[------- ALL PASSENGERS -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 29; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    ifstream file("passengers.txt");
    if (!file) {
        cout << RED << "\t\t\t\t\t\tNo passengers found!\n" << RESET;
        Sleep(2000);
        return;
    }
    
    cout << WHITE << "\t" << string(90, '-') << endl;
    cout << "\t" << left << setw(15) << "User ID"
         << setw(25) << "Name"
         << setw(20) << "Phone"
         << setw(10) << "Bookings"
         << setw(15) << "Total Spent" << endl;
    cout << "\t" << string(90, '-') << endl;
    cout << RESET;
    
    string userId, password, name, phone;
    int bookings;
    double spent;
    
    while (file >> userId >> password >> name >> phone >> bookings >> spent) {
        cout << "\t" << left << setw(15) << userId
             << setw(25) << name
             << setw(20) << phone
             << setw(10) << bookings
             << "$" << setw(14) << fixed << setprecision(2) << spent << endl;
    }
    
    file.close();
    cout << GREEN << "\n\t\t\t\t\t\tDisplaying all passengers..." << RESET << endl;
    Sleep(3000);
}

void searchPassenger() {
    system("cls");
    cout << BLUE;
    cout << "\n\n\t\t\t\t\t\t[------- SEARCH PASSENGER -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 31; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    cout << "\t\t\t\t\t\t" << BLUE << "1. Search by User ID\n" << RESET;
    cout << "\t\t\t\t\t\t" << BLUE << "2. Search by Name\n\n" << RESET;
    
    cout << "\t\t\t\t\t\t" << WHITE << "Choice: " << RESET;
    int choice = integerInput();
    while (choice < 1 || choice > 2) {
        cout << RED << "\t\t\t\t\t\tInvalid! Enter (1-2): " << RESET;
        choice = integerInput();
    }
    
    string search;
    if (choice == 1) {
        cout << "\t\t\t\t\t\tEnter User ID: ";
        search = enterUserId();
    } else {
        cout << "\t\t\t\t\t\tEnter Name: ";
        search = enterName();
    }
    
    ifstream file("passengers.txt");
    if (!file) {
        cout << RED << "\n\t\t\t\t\t\tNo passengers in database!\n" << RESET;
        Sleep(1500);
        return;
    }
    
    string userId, password, name, phone;
    int bookings;
    double spent;
    bool found = false;
    
    cout << WHITE << "\n\t" << string(60, '=') << endl;
    cout << "\t\t\tSEARCH RESULTS\n";
    cout << "\t" << string(60, '=') << endl;
    cout << RESET;
    
    while (file >> userId >> password >> name >> phone >> bookings >> spent) {
        bool match = false;
        if (choice == 1 && userId == search) {
            match = true;
        } else if (choice == 2 && name.find(search) != string::npos) {
            match = true;
        }
        
        if (match) {
            found = true;
            cout << BLUE << "\n\t" << string(50, '-') << endl;
            cout << "\tUser ID: " << userId << endl;
            cout << "\tName: " << name << endl;
            cout << "\tPhone: " << phone << endl;
            cout << "\tTotal Bookings: " << bookings << endl;
            cout << "\tTotal Spent: $" << fixed << setprecision(2) << spent << endl;
            cout << "\t" << string(50, '-') << endl;
            cout << RESET;
        }
    }
    
    file.close();
    
    if (!found) {
        cout << RED << "\n\t\t\t\t\t\tPassenger not found!" << RESET << endl;
    }
    Sleep(3000);
}

void updatePassenger() {
    system("cls");
    cout << BLUE;
    cout << "\n\n\t\t\t\t\t\t[------- UPDATE PASSENGER -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 31; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    cout << "\t\t\t\t\t\tUser ID: ";
    string userId = enterUserId();
    
    ifstream inFile("passengers.txt");
    if (!inFile) {
        cout << RED << "\n\t\t\t\t\t\tNo passengers in database!\n" << RESET;
        Sleep(1500);
        return;
    }
    
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;
    
    while (getline(inFile, line)) {
        size_t pos1 = line.find(' ');
        string id = line.substr(0, pos1);
        
        if (id == userId) {
            found = true;
            
            size_t pos2 = line.find(' ', pos1 + 1);
            size_t pos3 = line.find(' ', pos2 + 1);
            size_t pos4 = line.find(' ', pos3 + 1);
            
            string name = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string phone = line.substr(pos3 + 1, pos4 - pos3 - 1);
            
            cout << BLUE << "\n\t\t\t\t\t\tCurrent Details:\n" << RESET;
            cout << "\t\t\t\t\t\tName: " << name << endl;
            cout << "\t\t\t\t\t\tPhone: " << phone << endl;
            
            cout << BLUE << "\n\t\t\t\t\t\tEnter new details:\n" << RESET;
            cout << "\t\t\t\t\t\tNew Name: ";
            string newName = enterName();
            
            cout << "\t\t\t\t\t\tNew Phone: ";
            string newPhone = enterPhone();
            
            cout << "\t\t\t\t\t\tNew Password: ";
            string newPass;
            cin >> newPass;
            cin.ignore();
            
            // Get remaining data
            size_t pos5 = line.find(' ', pos4 + 1);
            string bookingsStr = line.substr(pos4 + 1, pos5 - pos4 - 1);
            string spentStr = line.substr(pos5 + 1);
            
            tempFile << id << " " << newPass << " " << newName << " " 
                    << newPhone << " " << bookingsStr << " " << spentStr << endl;
        } else {
            tempFile << line << endl;
        }
    }
    
    inFile.close();
    tempFile.close();
    
    if (found) {
        remove("passengers.txt");
        rename("temp.txt", "passengers.txt");
        cout << GREEN << "\n\t\t\t\t\t\tPassenger updated successfully!" << RESET << endl;
    } else {
        remove("temp.txt");
        cout << RED << "\n\t\t\t\t\t\tPassenger not found!" << RESET << endl;
    }
    Sleep(1500);
}

void deletePassenger() {
    system("cls");
    cout << BLUE;
    cout << "\n\n\t\t\t\t\t\t[------- DELETE PASSENGER -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 31; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    cout << "\t\t\t\t\t\tUser ID: ";
    string userId = enterUserId();
    
    ifstream inFile("passengers.txt");
    if (!inFile) {
        cout << RED << "\n\t\t\t\t\t\tNo passengers in database!\n" << RESET;
        Sleep(1500);
        return;
    }
    
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;
    
    while (getline(inFile, line)) {
        size_t pos = line.find(' ');
        string id = line.substr(0, pos);
        
        if (id == userId) {
            found = true;
            continue;
        }
        tempFile << line << endl;
    }
    
    inFile.close();
    tempFile.close();
    
    if (found) {
        remove("passengers.txt");
        rename("temp.txt", "passengers.txt");
        cout << GREEN << "\n\t\t\t\t\t\tPassenger deleted successfully!" << RESET << endl;
    } else {
        remove("temp.txt");
        cout << RED << "\n\t\t\t\t\t\tPassenger not found!" << RESET << endl;
    }
    Sleep(1500);
}

// ========== BOOKING FUNCTIONS ==========
void bookFlight(string userId) {
    system("cls");
    cout << BLUE;
    cout << "\n\n\t\t\t\t\t\t[------- BOOK A FLIGHT -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 30; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    viewAvailableFlights();
    
    cout << "\n\t\t\t\t\t\tFlight Number: ";
    string flightNo = enterFlightNumber();
    
    ifstream fFile("flights.txt");
    if (!fFile) {
        cout << RED << "\n\t\t\t\t\t\tNo flights available!\n" << RESET;
        Sleep(1500);
        return;
    }
    
    string fNo, departure, destination, date, time, status;
    int totalSeats, economySeats, businessSeats;
    double economyFare, businessFare;
    bool found = false;
    
    while (fFile >> fNo >> departure >> destination >> date >> time 
          >> totalSeats >> economySeats >> businessSeats 
          >> economyFare >> businessFare >> status) {
        if (fNo == flightNo && status == "Available") {
            found = true;
            break;
        }
    }
    fFile.close();
    
    if (!found) {
        cout << RED << "\n\t\t\t\t\t\tFlight not available!\n" << RESET;
        Sleep(1500);
        return;
    }
    
    cout << "\t\t\t\t\t\t" << CYAN << "1. Economy ($" << (int)economyFare << ")\n" << RESET;
    cout << "\t\t\t\t\t\t" << CYAN << "2. Business ($" << (int)businessFare << ")\n" << RESET;
    cout << "\t\t\t\t\t\t" << WHITE << "Choice: " << RESET;
    int seatType = integerInput();
    while (seatType < 1 || seatType > 2) {
        cout << RED << "\t\t\t\t\t\tInvalid! Enter (1-2): " << RESET;
        seatType = integerInput();
    }
    
    int maxSeats = (seatType == 1) ? economySeats : businessSeats;
    double fare = (seatType == 1) ? economyFare : businessFare;
    string typeName = (seatType == 1) ? "Economy" : "Business";
    
    cout << "\t\t\t\t\t\tSeats (1-" << maxSeats << "): ";
    int seats = integerInput();
    while (seats < 1 || seats > maxSeats) {
        cout << RED << "\t\t\t\t\t\tInvalid! Enter (1-" << maxSeats << "): " << RESET;
        seats = integerInput();
    }
    
    double totalFare = fare * seats;
    
    // Update flight
    ifstream inFile("flights.txt");
    ofstream temp("temp.txt");
    
    while (inFile >> fNo >> departure >> destination >> date >> time 
          >> totalSeats >> economySeats >> businessSeats 
          >> economyFare >> businessFare >> status) {
        if (fNo == flightNo) {
            if (seatType == 1) {
                economySeats -= seats;
            } else {
                businessSeats -= seats;
            }
            totalSeats = economySeats + businessSeats;
            if (totalSeats == 0) {
                status = "Full";
            }
        }
        temp << fNo << " " << departure << " " << destination << " " 
             << date << " " << time << " " << totalSeats << " " 
             << economySeats << " " << businessSeats << " " 
             << economyFare << " " << businessFare << " " << status << endl;
    }
    inFile.close();
    temp.close();
    remove("flights.txt");
    rename("temp.txt", "flights.txt");
    
    // Add reservation
    string resId = "RES" + to_string(reservationCounter++);
    ofstream res("reservations.txt", ios::app);
    res << resId << " " << userId << " " << flightNo << " " 
        << date << " Confirmed " << seats << " " 
        << typeName << " " << totalFare << endl;
    res.close();
    
    // Update passenger
    ifstream pFile("passengers.txt");
    ofstream pTemp("ptemp.txt");
    string pId, pass, pname, phone;
    int pbookings;
    double pspent;
    
    while (pFile >> pId >> pass >> pname >> phone >> pbookings >> pspent) {
        if (pId == userId) {
            pbookings++;
            pspent += totalFare;
            pTemp << pId << " " << pass << " " << pname << " " 
                  << phone << " " << pbookings << " " << fixed << setprecision(2) << pspent << endl;
        } else {
            pTemp << pId << " " << pass << " " << pname << " " 
                  << phone << " " << pbookings << " " << fixed << setprecision(2) << pspent << endl;
        }
    }
    pFile.close();
    pTemp.close();
    remove("passengers.txt");
    rename("ptemp.txt", "passengers.txt");
    
    cout << GREEN << "\n\n\t\t\t\t\t\tBooking confirmed!" << RESET << endl;
    cout << "\t\t\t\t\t\tReservation ID: " << resId << endl;
    cout << "\t\t\t\t\t\tTotal: $" << totalFare << endl;
    Sleep(3000);
}

void viewAvailableFlights() {
    system("cls");
    cout << CYAN;
    cout << "\n\n\t\t\t\t\t\t[------- AVAILABLE FLIGHTS -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 33; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    ifstream file("flights.txt");
    if (!file) {
        cout << RED << "\t\t\t\t\t\tNo flights available!\n" << RESET;
        Sleep(2000);
        return;
    }
    
    cout << WHITE << "\t" << string(110, '-') << endl;
    cout << "\t" << left << setw(12) << "Flight" 
         << setw(15) << "Departure"
         << setw(15) << "Destination"
         << setw(12) << "Date"
         << setw(10) << "Time"
         << setw(8) << "Eco"
         << setw(8) << "Bus"
         << setw(10) << "Eco Fare"
         << setw(10) << "Bus Fare"
         << setw(12) << "Status" << endl;
    cout << "\t" << string(110, '-') << endl;
    cout << RESET;
    
    string flightNo, departure, destination, date, time, status;
    int totalSeats, economySeats, businessSeats;
    double economyFare, businessFare;
    bool found = false;
    
    while (file >> flightNo >> departure >> destination >> date >> time 
          >> totalSeats >> economySeats >> businessSeats 
          >> economyFare >> businessFare >> status) {
        if (status == "Available") {
            found = true;
            cout << "\t" << left << setw(12) << flightNo
                 << setw(15) << departure
                 << setw(15) << destination
                 << setw(12) << date
                 << setw(10) << time
                 << setw(8) << economySeats
                 << setw(8) << businessSeats
                 << "$" << setw(9) << fixed << setprecision(2) << economyFare
                 << "$" << setw(9) << businessFare
                 << setw(12) << status << endl;
        }
    }
    
    file.close();
    
    if (!found) {
        cout << RED << "\n\t\t\t\t\t\tNo flights available!" << RESET << endl;
    }
    
    Sleep(2000);
}

// ========== RESERVATION FUNCTIONS ==========
void cancelReservation(string userId) {
    system("cls");
    cout << BLUE;
    cout << "\n\n\t\t\t\t\t\t[------- CANCEL RESERVATION -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 34; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    // Show user's reservations
    ifstream resFile("reservations.txt");
    bool hasReservations = false;
    
    cout << BLUE << "\t\t\t\t\t\tYour Reservations:\n" << RESET;
    cout << WHITE << "\t" << string(80, '-') << endl;
    cout << "\t" << left << setw(12) << "Res ID"
         << setw(12) << "Flight"
         << setw(12) << "Date"
         << setw(10) << "Seats"
         << setw(12) << "Type"
         << setw(15) << "Total" << endl;
    cout << "\t" << string(80, '-') << endl;
    cout << RESET;
    
    string resId, uId, flightNo, date, status, seatType;
    int seats;
    double totalFare;
    
    while (resFile >> resId >> uId >> flightNo >> date >> status >> seats >> seatType >> totalFare) {
        if (uId == userId && status == "Confirmed") {
            hasReservations = true;
            cout << "\t" << left << setw(12) << resId
                 << setw(12) << flightNo
                 << setw(12) << date
                 << setw(10) << seats
                 << setw(12) << seatType
                 << "$" << setw(14) << fixed << setprecision(2) << totalFare << endl;
        }
    }
    resFile.close();
    
    if (!hasReservations) {
        cout << RED << "\t\t\t\t\t\tNo active reservations found!\n" << RESET;
        Sleep(2000);
        return;
    }
    
    cout << "\n\t\t\t\t\t\tEnter Reservation ID to cancel: ";
    string cancelId;
    cin >> cancelId;
    cin.ignore();
    
    // Update reservation file
    ifstream inRes("reservations.txt");
    ofstream tempRes("temp_res.txt");
    bool found = false;
    
    while (inRes >> resId >> uId >> flightNo >> date >> status >> seats >> seatType >> totalFare) {
        if (resId == cancelId && uId == userId) {
            found = true;
            tempRes << resId << " " << uId << " " << flightNo << " " 
                   << date << " Cancelled " << seats << " " << seatType << " " << totalFare << endl;
        } else {
            tempRes << resId << " " << uId << " " << flightNo << " " 
                   << date << " " << status << " " << seats << " " << seatType << " " << totalFare << endl;
        }
    }
    inRes.close();
    tempRes.close();
    
    if (found) {
        remove("reservations.txt");
        rename("temp_res.txt", "reservations.txt");
        
        // Update flight seats
        ifstream inFlight("flights.txt");
        ofstream tempFlight("temp_flight.txt");
        string fNo, departure, dest, fdate, ftime, fstatus;
        int tSeats, eSeats, bSeats;
        double eFare, bFare;
        
        while (inFlight >> fNo >> departure >> dest >> fdate >> ftime 
              >> tSeats >> eSeats >> bSeats >> eFare >> bFare >> fstatus) {
            if (fNo == flightNo) {
                if (seatType == "Economy") {
                    eSeats += seats;
                } else {
                    bSeats += seats;
                }
                tSeats = eSeats + bSeats;
                if (fstatus == "Full" && tSeats > 0) {
                    fstatus = "Available";
                }
            }
            tempFlight << fNo << " " << departure << " " << dest << " " 
                      << fdate << " " << ftime << " " << tSeats << " " 
                      << eSeats << " " << bSeats << " " 
                      << eFare << " " << bFare << " " << fstatus << endl;
        }
        inFlight.close();
        tempFlight.close();
        
        remove("flights.txt");
        rename("temp_flight.txt", "flights.txt");
        
        cout << GREEN << "\n\t\t\t\t\t\tReservation cancelled successfully!" << RESET << endl;
    } else {
        remove("temp_res.txt");
        cout << RED << "\n\t\t\t\t\t\tReservation not found!" << RESET << endl;
    }
    Sleep(2000);
}

void personalReport(string userId) {
    system("cls");
    cout << BLUE;
    cout << "\n\n\t\t\t\t\t\t[------- PERSONAL REPORT -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 31; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    // Get passenger info
    ifstream pFile("passengers.txt");
    if (!pFile) {
        cout << RED << "\t\t\t\t\t\tNo passenger data found!\n" << RESET;
        Sleep(2000);
        return;
    }
    
    string id, pass, name, phone;
    int bookings;
    double spent;
    bool found = false;
    
    while (pFile >> id >> pass >> name >> phone >> bookings >> spent) {
        if (id == userId) {
            found = true;
            cout << BLUE << "\t\t\t\t\t\tName: " << RESET << name << endl;
            cout << BLUE << "\t\t\t\t\t\tPhone: " << RESET << phone << endl;
            cout << BLUE << "\t\t\t\t\t\tTotal Bookings: " << RESET << bookings << endl;
            cout << BLUE << "\t\t\t\t\t\tTotal Spent: " << RESET << "$" << fixed << setprecision(2) << spent << endl;
            break;
        }
    }
    pFile.close();
    
    if (!found) {
        cout << RED << "\t\t\t\t\t\tPassenger not found!" << RESET << endl;
        Sleep(2000);
        return;
    }
    
    // Show reservation history
    cout << BLUE << "\n\t\t\t\t\t\tReservation History:\n" << RESET;
    cout << WHITE << "\t" << string(80, '-') << endl;
    cout << "\t" << left << setw(12) << "Res ID"
         << setw(12) << "Flight"
         << setw(12) << "Date"
         << setw(10) << "Seats"
         << setw(12) << "Type"
         << setw(12) << "Status"
         << setw(15) << "Total" << endl;
    cout << "\t" << string(80, '-') << endl;
    cout << RESET;
    
    ifstream resFile("reservations.txt");
    if (!resFile) {
        cout << RED << "\t\t\t\t\t\tNo reservation data!\n" << RESET;
        Sleep(2000);
        return;
    }
    
    string resId, uId, flightNo, date, status, seatType;
    int seats;
    double totalFare;
    int totalReservations = 0;
    
    while (resFile >> resId >> uId >> flightNo >> date >> status >> seats >> seatType >> totalFare) {
        if (uId == userId) {
            totalReservations++;
            cout << "\t" << left << setw(12) << resId
                 << setw(12) << flightNo
                 << setw(12) << date
                 << setw(10) << seats
                 << setw(12) << seatType
                 << setw(12) << status
                 << "$" << setw(14) << fixed << setprecision(2) << totalFare << endl;
        }
    }
    resFile.close();
    
    cout << GREEN << "\n\t\t\t\t\t\tTotal Reservations: " << totalReservations << RESET << endl;
    Sleep(4000);
}
void viewMyReservations(string userId) {
    system("cls");
    cout << BLUE;
    cout << "\n\n\t\t\t\t\t\t[------- MY RESERVATIONS -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 31; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    ifstream resFile("reservations.txt");
    if (!resFile) {
        cout << RED << "\t\t\t\t\t\tNo reservations found!\n" << RESET;
        Sleep(2000);
        return;
    }
    
    bool hasReservations = false;
    
    cout << WHITE << "\t" << string(80, '-') << endl;
    cout << "\t" << left << setw(12) << "Res ID"
         << setw(12) << "Flight"
         << setw(12) << "Date"
         << setw(10) << "Seats"
         << setw(12) << "Type"
         << setw(12) << "Status"
         << setw(15) << "Total" << endl;
    cout << "\t" << string(80, '-') << endl;
    cout << RESET;
    
    string resId, uId, flightNo, date, status, seatType;
    int seats;
    double totalFare;
    
    while (resFile >> resId >> uId >> flightNo >> date >> status >> seats >> seatType >> totalFare) {
        if (uId == userId) {
            hasReservations = true;
            cout << "\t" << left << setw(12) << resId
                 << setw(12) << flightNo
                 << setw(12) << date
                 << setw(10) << seats
                 << setw(12) << seatType
                 << setw(12) << status
                 << "$" << setw(14) << fixed << setprecision(2) << totalFare << endl;
        }
    }
    resFile.close();
    
    if (!hasReservations) {
        cout << RED << "\t\t\t\t\t\tNo reservations found!\n" << RESET;
    }
    Sleep(4000);
}

// ========== ADDITIONAL FUNCTIONS ==========
void systemReports() {
    system("cls");
    cout << MAGENTA;
    cout << "\n\n\t\t\t\t\t\t[------- SYSTEM REPORTS -------]\n";
    cout << "\t\t\t\t\t\t";
    for (int i = 0; i < 30; i++) {
        cout << "*";
    }
    cout << "\n\n" << RESET;
    
    // Count flights
    int flightCount = 0;
    ifstream fFile("flights.txt");
    if (fFile) {
        string line;
        while (getline(fFile, line)) {
            if (!line.empty()) {
                flightCount++;
            }
        }
        fFile.close();
    }
    
    // Count passengers
    int passengerCount = 0;
    double totalRevenue = 0;
    ifstream pFile("passengers.txt");
    if (pFile) {
        string userId, password, name, phone;
        int bookings;
        double spent;
        
        while (pFile >> userId >> password >> name >> phone >> bookings >> spent) {
            passengerCount++;
            totalRevenue += spent;
        }
        pFile.close();
    }
    
    // Count reservations
    int reservationCount = 0;
    int activeReservations = 0;
    ifstream rFile("reservations.txt");
    if (rFile) {
        string resId, uId, flightNo, date, status, seatType;
        int seats;
        double totalFare;
        
        while (rFile >> resId >> uId >> flightNo >> date >> status >> seats >> seatType >> totalFare) {
            reservationCount++;
            if (status == "Confirmed") {
                activeReservations++;
            }
        }
        rFile.close();
    }
    
    cout << MAGENTA << "\t\t\t\t\t\tTotal Flights: " << RESET << flightCount << endl;
    cout << MAGENTA << "\t\t\t\t\t\tTotal Passengers: " << RESET << passengerCount << endl;
    cout << MAGENTA << "\t\t\t\t\t\tTotal Reservations: " << RESET << reservationCount << endl;
    cout << MAGENTA << "\t\t\t\t\t\tActive Reservations: " << RESET << activeReservations << endl;
    cout << MAGENTA << "\t\t\t\t\t\tTotal Revenue: " << RESET << "$" << fixed << setprecision(2) << totalRevenue << endl;
    
    Sleep(3000);
}

// ========== VALIDATION FUNCTIONS ==========
int integerInput() {
    string input = "";
    char ch;
    
    while (true) {
        ch = _getch();
        if (ch == 13 && !input.empty()) {
            cout << endl;
            break;
        }
        if (ch == 8) {
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b";
            }
            continue;
        }
        if (ch >= '0' && ch <= '9') {
            input += ch;
            cout << ch;
        }
    }
    
    if (input.empty()) {
        return -1;
    }
    return stoi(input);
}

string enterName() {
    string name = "";
    char ch;

    while (true) {
        ch = _getch();
        if (ch == 13 && name.length() > 0) {
            cout << endl;
            break;
        }
        if (name.length() == 0 || name.back() == ' ') {
            ch = toupper(ch);
        } else {
            ch = tolower(ch);
        }
        
        bool valid = false;
        if (ch == 8) {
            if (name.length() > 0) {
                name.pop_back();
                cout << "\b \b";
            }
            continue;
        }
        
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            valid = true;
        }
        
        if (ch == ' ') {
            if (name.length() == 0 || name.back() == ' ') {
                valid = false;
            } else {
                valid = true;
            }
        }

        if (valid) {
            name += ch;
            cout << ch;
        }
    }
    
    // Format name properly
    string formatted = "";
    bool newWord = true;
    for (char c : name) {
        if (c == ' ') {
            formatted += c;
            newWord = true;
        } else if (newWord) {
            formatted += toupper(c);
            newWord = false;
        } else {
            formatted += tolower(c);
        }
    }
    
    return formatted;
}

string enterPhone() {
    string phone = "";
    char ch;
    
    while (phone.length() < 12) {
        ch = _getch();
        
        if (ch == 8) {
            if (!phone.empty()) {
                phone.pop_back();
                cout << "\b \b";
            }
            continue;
        }
        
        if (ch >= '0' && ch <= '9') {
            phone += ch;
            cout << ch;
            
            // Add hyphen automatically
            if (phone.length() == 4) {
                phone += "-";
                cout << "-";
            }
        }
    }
    cout << endl;
    
    // Validate Pakistan phone with hyphen
    if (phone.substr(0, 2) != "03" || phone[4] != '-') {
        cout << RED << "\t\t\t\t\tPhone must be in format 03XX-XXXXXXX!\n\t\t\t\t\tEnter again: " << RESET;
        return enterPhone();
    }
    
    return phone;
}

string enterDate() {
    string date = "";
    char ch;
    
    while (date.length() < 10) {
        ch = _getch();
        
        if (ch == 8) {
            if (!date.empty()) {
                date.pop_back();
                cout << "\b \b";
            }
            continue;
        }
        
        if (ch >= '0' && ch <= '9') {
            date += ch;
            cout << ch;
            
            if (date.length() == 2 || date.length() == 5) {
                date += "-";
                cout << "-";
            }
        }
    }
    cout << endl;
    
    // Validate date
    if (!validateDate(date)) {
        cout << RED << "\t\t\t\t\tInvalid date! Enter again: " << RESET;
        return enterDate();
    }
    
    return date;
}

string enterTime() {
    string time = "";
    char ch;
    
    while (time.length() < 5) {
        ch = _getch();
        
        if (ch == 8) {
            if (!time.empty()) {
                time.pop_back();
                cout << "\b \b";
            }
            continue;
        }
        
        if (ch >= '0' && ch <= '9') {
            time += ch;
            cout << ch;
            
            if (time.length() == 2) {
                time += ":";
                cout << ":";
            }
        }
    }
    cout << endl;
    
    // Validate time
    if (!validateTime(time)) {
        cout << RED << "\t\t\t\t\tInvalid time! Enter again: " << RESET;
        return enterTime();
    }
    
    return time;
}

string enterFlightNumber() {
    string flightNo = "";
    char ch;
    
    while (flightNo.length() < 5) {
        ch = _getch();
        
        if (ch == 8) {
            if (!flightNo.empty()) {
                flightNo.pop_back();
                cout << "\b \b";
            }
            continue;
        }
        
        if (flightNo.length() < 2) {
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
                flightNo += toupper(ch);
                cout << (char)toupper(ch);
            }
        } else {
            if (ch >= '0' && ch <= '9') {
                flightNo += ch;
                cout << ch;
            }
        }
    }
    cout << endl;
    return flightNo;
}

string enterCity() {
    string city = "";
    char ch;

    while (true) {
        ch = _getch();
        if (ch == 13 && city.length() > 0) {
            cout << endl;
            break;
        }
        if (city.length() == 0) {
            ch = toupper(ch);
        }
        
        bool valid = false;
        if (ch == 8) {
            if (city.length() > 0) {
                city.pop_back();
                cout << "\b \b";   
            }
            continue;
        }
        
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == ' ') {
            valid = true;
        }

        if (valid) {
            city += ch;
            cout << ch;
        }
    }
    
    // Capitalize first letter of each word
    string result = "";
    bool newWord = true;
    for (char c : city) {
        if (c == ' ') {
            result += c;
            newWord = true;
        } else if (newWord) {
            result += toupper(c);
            newWord = false;
        } else {
            result += tolower(c);
        }
    }
    
    return result;
}

string enterUserId() {
    string userId = "";
    char ch;
    
    while (true) {
        ch = _getch();
        
        // Allow Enter when user has entered at least 6 characters
        if (ch == 13 && userId.length() >= 6) {
            cout << endl;
            break;
        }
        if (ch == 8) {
            if (!userId.empty()) {
                userId.pop_back();
                cout << "\b \b";
            }
            continue;
        }
        
        // Limit to 10 characters
        if (userId.length() < 10) {
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || 
               (ch >= '0' && ch <= '9')) {
                userId += ch;
                cout << ch;
            }
        }
    }
    
    if (userId.length() < 6) {
        cout << RED << "\t\t\t\t\tMust be 6-10 chars! Enter again: " << RESET;
        return enterUserId();
    }
    
    return userId;
}

double enterFare(string seatType) {
    string fareStr = "";
    char ch;
    bool hasDecimal = false;
    
    cout << "\t\t\t\t\t\t" << seatType << " fare ($): ";
    
    while (true) {
        ch = _getch();
        
        if (ch == 13 && !fareStr.empty()) {
            cout << endl;
            break;
        }
        if (ch == 8) {
            if (!fareStr.empty()) {
                if (fareStr.back() == '.') {
                    hasDecimal = false;
                }
                fareStr.pop_back();
                cout << "\b \b";
            }
            continue;
        }
        
        if (ch >= '0' && ch <= '9') {
            fareStr += ch;
            cout << ch;
        } else if (ch == '.' && !hasDecimal && !fareStr.empty()) {
            fareStr += ch;
            hasDecimal = true;
            cout << ch;
        }
    }
    
    double fare = stod(fareStr);
    while (fare <= 0 || fare > 10000) {
        cout << RED << "\t\t\t\t\t\tInvalid! Enter ($1-$10000): " << RESET;
        fareStr = "";
        hasDecimal = false;
        
        while (true) {
            ch = _getch();
            
            if (ch == 13 && !fareStr.empty()) {
                cout << endl;
                break;
            }
            if (ch == 8) {
                if (!fareStr.empty()) {
                    if (fareStr.back() == '.') {
                        hasDecimal = false;
                    }
                    fareStr.pop_back();
                    cout << "\b \b";
                }
                continue;
            }
            
            if (ch >= '0' && ch <= '9') {
                fareStr += ch;
                cout << ch;
            } else if (ch == '.' && !hasDecimal && !fareStr.empty()) {
                fareStr += ch;
                hasDecimal = true;
                cout << ch;
            }
        }
        fare = stod(fareStr);
    }
    
    return fare;
}

// ========== VALIDATION HELPERS ==========
bool validateTime(string time) {
    if (time.length() != 5) {
        return false;
    }
    if (time[2] != ':') {
        return false;
    }
    
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));
    
    if (hour < 0 || hour > 23) {
        return false;
    }
    if (minute < 0 || minute > 59) {
        return false;
    }
    
    return true;
}

bool validateDate(string date) {
    if (date.length() != 10) {
        return false;
    }
    if (date[2] != '-' || date[5] != '-') {
        return false;
    }
    
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    
    if (year < 2024 || year > 2030) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > 31) {
        return false;
    }
    
    if (month == 2 && day > 29) {
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    
    return true;
}

bool validatePhone(string phone) {
    if (phone.length() != 12) {
        return false;
    }
    if (phone[4] != '-') {
        return false;
    }
    
    for (int i = 0; i < phone.length(); i++) {
        if (i == 4) {
            continue;
        }
        if (phone[i] < '0' || phone[i] > '9') {
            return false;
        }
    }
    
    if (phone.substr(0, 2) != "03") {
        return false;
    }
    
    return true;
}


