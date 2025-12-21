#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

// Structure for booking details
struct Booking {
    int bookingID;
    string customerName;
    int roomID;
    string date;
    string paymentStatus;
    Booking* next;

    Booking(int id, string name, int room, string d, string pay) {
        bookingID = id;
        customerName = name;
        roomID = room;
        date = d;
        paymentStatus = pay;
        next = NULL;
    }
};

class HashTable {
private:
    Booking* table[TABLE_SIZE];

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = NULL;
    }

    // Insert booking
    void insert(int id, string name, int room, string date, string status) {
        int hashKey = hashFunction(id);
        Booking* newBooking = new Booking(id, name, room, date, status);

        if (table[hashKey] == NULL) {
            table[hashKey] = newBooking;
        } else {
            Booking* temp = table[hashKey];
            while (temp->next != NULL) {
                if (temp->bookingID == id) {
                    temp->customerName = name;
                    temp->roomID = room;
                    temp->date = date;
                    temp->paymentStatus = status;
                    delete newBooking;
                    return;
                }
                temp = temp->next;
            }
            temp->next = newBooking;
        }
        cout << "Booking added successfully.\n";
    }

    // Search booking
    void search(int id) {
        int hashKey = hashFunction(id);
        Booking* temp = table[hashKey];

        while (temp != NULL) {
            if (temp->bookingID == id) {
                cout << "\nBooking Found:\n";
                cout << "Customer: " << temp->customerName << endl;
                cout << "Room ID: " << temp->roomID << endl;
                cout << "Date: " << temp->date << endl;
                cout << "Payment: " << temp->paymentStatus << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Booking ID not found.\n";
    }

    // Remove booking
    void remove(int id) {
        int hashKey = hashFunction(id);
        Booking* temp = table[hashKey];
        Booking* prev = NULL;

        while (temp != NULL && temp->bookingID != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Booking ID not found.\n";
            return;
        }

        if (prev == NULL)
            table[hashKey] = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout << "Booking cancelled successfully.\n";
    }
};

int main() {
    HashTable bookings;
    int choice, bookingID, roomID;
    string name, date, status;

    do {
        cout << "\nTourism Management System\n";
        cout << "1. Add Booking\n";
        cout << "2. Search Booking\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Booking ID: ";
                cin >> bookingID;
                cout << "Customer Name: ";
                cin >> name;
                cout << "Room ID: ";
                cin >> roomID;
                cout << "Date: ";
                cin >> date;
                cout << "Payment Status (Paid/Unpaid): ";
                cin >> status;
                bookings.insert(bookingID, name, roomID, date, status);
                break;

            case 2:
                cout << "Enter Booking ID: ";
                cin >> bookingID;
                bookings.search(bookingID);
                break;

            case 3:
                cout << "Enter Booking ID to cancel: ";
                cin >> bookingID;
                bookings.remove(bookingID);
                break;

            case 4:
                cout << "Exiting system...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
