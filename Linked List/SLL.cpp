#include <iostream>
#include <string>
using namespace std;

// Node represents one visit
struct Visit {
    string place;
    string date;
    int hoursSpent;
    Visit* next;

    Visit(string p, string d, int h) {
        place = p;
        date = d;
        hoursSpent = h;
        next = NULL;
    }
};

class TouristHistory {
private:
    Visit* head;

public:
    TouristHistory() {
        head = NULL;
    }

    // Add a new visit
    void addVisit(string place, string date, int hours) {
        Visit* newVisit = new Visit(place, date, hours);

        if (head == NULL) {
            head = newVisit;
        } else {
            Visit* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newVisit;
        }

        cout << "Visit recorded: " << place << " on " << date << endl;
    }

    // Display full visit history
    void showHistory() {
        if (head == NULL) {
            cout << "No visits recorded yet.\n";
            return;
        }

        cout << "\nTourist Visit History\n";
        Visit* temp = head;
        while (temp != NULL) {
            cout << "Place: " << temp->place
                 << " | Date: " << temp->date
                 << " | Time Spent: " << temp->hoursSpent << " hrs\n";
            temp = temp->next;
        }
    }

    // Recommend places based on time spent
    void recommendPlaces() {
        if (head == NULL) {
            cout << "No data available for recommendations.\n";
            return;
        }

        cout << "\nRecommended Places (Loved by Tourist)\n";
        Visit* temp = head;
        while (temp != NULL) {
            if (temp->hoursSpent >= 5) {
                cout << " " << temp->place << endl;
            }
            temp = temp->next;
        }
    }
};

int main() {
    TouristHistory history;
    int choice, hours;
    string place, date;

    do {
        cout << "\nTourism Management System\n";
        cout << "1. Add Visit\n";
        cout << "2. View Visit History\n";
        cout << "3. Get Recommendations\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter place name: ";
                cin >> place;
                cout << "Enter visit date (DD-MM-YYYY): ";
                cin >> date;
                cout << "Enter hours spent: ";
                cin >> hours;
                history.addVisit(place, date, hours);
                break;

            case 2:
                history.showHistory();
                break;

            case 3:
                history.recommendPlaces();
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
