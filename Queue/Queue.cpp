#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<string> counterQueue;
    int choice;
    string visitor;

    do {
        cout << "\n--- Ticket Counter ---\n";
        cout << "1. Join Queue\n";
        cout << "2. Serve Visitor\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter visitor name: ";
                cin >> visitor;
                counterQueue.push(visitor);
                cout << visitor << " joined the queue.\n";
                break;

            case 2:
                if (!counterQueue.empty()) {
                    cout << "Serving: " << counterQueue.front() << endl;
                    counterQueue.pop();
                } else {
                    cout << "No visitors waiting.\n";
                }
                break;
        }
    } while (choice != 3);

    return 0;
}
