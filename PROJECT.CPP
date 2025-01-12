#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;

struct Train {
    int trainNumber;
    string trainName;
    string source;
    string destination;
    int availableSeats;
};

struct Passenger {
    string name;
    int age;
    int trainNumber;
    int ticketID;
};

vector<Train> trains;
vector<Passenger> passengers;
int ticketIDCounter = 1;

// Function to add a train
void addTrain() {
    Train t;
    cout << "Enter Train Number: ";
    cin >> t.trainNumber;
    cin.ignore(); // Clear input buffer
    cout << "Enter Train Name: ";
    getline(cin, t.trainName);
    cout << "Enter Source: ";
    getline(cin, t.source);
    cout << "Enter Destination: ";
    getline(cin, t.destination);
    cout << "Enter Available Seats: ";
    cin >> t.availableSeats;

    trains.push_back(t);
    cout << "Train added successfully!\n";
}

// Function to view all trains
void viewTrains() {
    if (trains.empty()) {
        cout << "No trains available.\n";
        return;
    }

    cout << "\nTrain Details:\n";
    for (const auto &t : trains) {
        cout << "Train Number: " << t.trainNumber << ", Train Name: " << t.trainName
             << ", Source: " << t.source << ", Destination: " << t.destination
             << ", Available Seats: " << t.availableSeats << endl;
    }
}

// Function to book a ticket
void bookTicket() {
    if (trains.empty()) {
        cout << "No trains available for booking.\n";
        return;
    }

    int trainNumber;
    cout << "Enter Train Number to Book: ";
    cin >> trainNumber;

    // Find train 
    auto it = find_if(trains.begin(), trains.end(), [&trainNumber](const Train &t) {
        return t.trainNumber == trainNumber;
    });

    if (it == trains.end()) {
        cout << "Train not found.\n";
        return;
    }

    if (it->availableSeats <= 0) {
        cout << "No seats available on this train.\n";
        return;
    }

    Passenger p;
    cin.ignore(); // Clear input buffer
    cout << "Enter Passenger Name: ";
    getline(cin, p.name);
    cout << "Enter Age: ";
    cin >> p.age;

    p.trainNumber = trainNumber;
    p.ticketID = ticketIDCounter++;

    passengers.push_back(p);
    it->availableSeats--; // Decrease available seats
    cout << "Ticket booked successfully! Ticket ID: " << p.ticketID << endl;
}

// Function to cancel a ticket
void cancelTicket() {
    if (passengers.empty()) {
        cout << "No bookings available to cancel.\n";
        return;
    }

    int ticketID;
    cout << "Enter Ticket ID to Cancel: ";
    cin >> ticketID;

    auto it = find_if(passengers.begin(), passengers.end(), [&ticketID](const Passenger &p) {
        return p.ticketID == ticketID;
    });

    if (it == passengers.end()) {
        cout << "Ticket not found.\n";
        return;
    }

    // Increase available seats in the train
    auto trainIt = find_if(trains.begin(), trains.end(), [&it](const Train &t) {
        return t.trainNumber == it->trainNumber;
    });

    if (trainIt != trains.end()) {
        trainIt->availableSeats++;
    }

    passengers.erase(it);
    cout << "Ticket cancelled successfully.\n";
}

// Function to view all bookings
void viewBookings() {
    if (passengers.empty()) {
        cout << "No bookings found.\n";
        return;
    }

    cout << "\nPassenger Details:\n";
    for (const auto &p : passengers) {
        cout << "Name: " << p.name << ", Age: " << p.age
             << ", Train Number: " << p.trainNumber
             << ", Ticket ID: " << p.ticketID << endl;
    }
}

// Main menu
int main() {
    int choice;
    do {
        cout << "\nIndian Railway Management System created by Kaushal\n";
        cout << "1. Add Train\n";
        cout << "2. View Trains\n";
        cout << "3. Book Ticket\n";
        cout << "4. Cancel Ticket\n";
        cout << "5. View Bookings\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTrain();
                break;
            case 2:
                viewTrains();
                break;
            case 3:
                bookTicket();
                break;
            case 4:
                cancelTicket();
                break;
            case 5:
                viewBookings();
                break;
            case 6:
                cout << "Exiting... Thank you Please Visit Again \n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}