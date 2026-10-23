#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
using namespace std;

const int TOTAL_SEATS = 30;

// Structure for passenger details
struct Passenger {
    int seatNo;
    string name;
    int age;
    char gender;
    Passenger* next;
};

// Dynamically allocated seat array
int* seats = nullptr;

// Head pointer of linked list
Passenger* head = nullptr;

// Function to initialize seats
void initializeSeats() {
    seats = (int*)malloc(TOTAL_SEATS * sizeof(int));

    if (seats == nullptr) {
        cout << "Memory allocation failed!\n";
        exit(1);
    }

    for (int i = 0; i < TOTAL_SEATS; i++) {
        seats[i] = 0;
    }
}

// Function to book a ticket
void bookTicket() {
    int seat = -1;

    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[i] == 0) {
            seat = i;
            break;
        }
    }

    if (seat == -1) {
        cout << "\nSorry! No seats are available.\n";
        return;
    }

    Passenger* newPassenger =
        (Passenger*)malloc(sizeof(Passenger));

    if (newPassenger == nullptr) {
        cout << "Memory allocation failed!\n";
        return;
    }

    cout << "\nEnter passenger name: ";
    getline(cin, newPassenger->name);

    cout << "Enter age: ";
    while (!(cin >> newPassenger->age) ||
           newPassenger->age <= 0) {
        cout << "Enter a valid age: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter gender (M/F/O): ";
    cin >> newPassenger->gender;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    newPassenger->seatNo = seat + 1;
    newPassenger->next = nullptr;

    // Insert passenger into linked list
    if (head == nullptr) {
        head = newPassenger;
    } else {
        Passenger* temp = head;

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newPassenger;
    }

    // Mark seat as booked
    seats[seat] = 1;

    cout << "\nTicket booked successfully!\n";
    cout << "Seat Number: " << seat + 1 << "\n";
}

// Function to cancel a ticket
void cancelTicket() {
    int seatNo;

    cout << "\nEnter seat number to cancel: ";

    if (!(cin >> seatNo)) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (seatNo < 1 || seatNo > TOTAL_SEATS) {
        cout << "Invalid seat number!\n";
        return;
    }

    if (seats[seatNo - 1] == 0) {
        cout << "This seat is already available.\n";
        return;
    }

    Passenger* temp = head;
    Passenger* previous = nullptr;

    while (temp != nullptr && temp->seatNo != seatNo) {
        previous = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Passenger record not found!\n";
        return;
    }

    // Remove passenger node from linked list
    if (previous == nullptr) {
        head = temp->next;
    } else {
        previous->next = temp->next;
    }

    // Release dynamically allocated memory
    free(temp);

    // Mark seat as available
    seats[seatNo - 1] = 0;

    cout << "Ticket cancelled successfully!\n";
}

// Function to display train status
void viewTrainStatus() {
    cout << "\n===== TRAIN STATUS =====\n";

    for (int i = 0; i < TOTAL_SEATS; i++) {
        cout << "Seat " << i + 1 << ": ";

        if (seats[i] == 1) {
            cout << "Booked\n";
        } else {
            cout << "Available\n";
        }
    }
}

// Function to display passenger list
void viewPassengerList() {
    Passenger* temp = head;

    if (temp == nullptr) {
        cout << "\nNo passengers have booked tickets.\n";
        return;
    }

    cout << "\n===== PASSENGER LIST =====\n";

    while (temp != nullptr) {
        cout << "\nSeat Number: " << temp->seatNo
             << "\nName: " << temp->name
             << "\nAge: " << temp->age
             << "\nGender: " << temp->gender
             << "\n-------------------------\n";

        temp = temp->next;
    }
}

// Function to free all allocated memory
void cleanup() {
    Passenger* temp = head;

    while (temp != nullptr) {
        Passenger* nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    head = nullptr;

    free(seats);
    seats = nullptr;

    cout << "Memory released successfully.\n";
}

// Main function
int main() {
    initializeSeats();

    int choice;

    do {
        cout << "\n===== RAILWAY RESERVATION SYSTEM =====\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. View Train Status\n";
        cout << "4. View Passenger List\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                bookTicket();
                break;

            case 2:
                cancelTicket();
                break;

            case 3:
                viewTrainStatus();
                break;

            case 4:
                viewPassengerList();
                break;

            case 5:
                cleanup();
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
