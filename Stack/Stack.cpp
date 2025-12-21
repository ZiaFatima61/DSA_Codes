#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> undoStack;
    int choice;
    string action;

    do {
        cout << "\n--- Booking Undo System ---\n";
        cout << "1. Perform Action\n";
        cout << "2. Undo Last Action\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter action (BookTicket/CancelTicket): ";
                cin >> action;
                undoStack.push(action);
                cout << "Action saved.\n";
                break;

            case 2:
                if (!undoStack.empty()) {
                    cout << "Undoing action: " << undoStack.top() << endl;
                    undoStack.pop();
                } else {
                    cout << "No actions to undo.\n";
                }
                break;
        }
    } while (choice != 3);

    return 0;
}
