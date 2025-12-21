#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<int, string> passMap;
    int choice, passID;
    string visitorName;

    do {
        cout << "\n--- Pass Verification System ---\n";
        cout << "1. Issue Pass\n";
        cout << "2. Verify Pass\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Pass ID: ";
                cin >> passID;
                cout << "Enter Visitor Name: ";
                cin >> visitorName;
                passMap[passID] = visitorName;
                cout << "Pass issued successfully.\n";
                break;

            case 2:
                cout << "Enter Pass ID to verify: ";
                cin >> passID;
                if (passMap.find(passID) != passMap.end())
                    cout << "Access Granted to " << passMap[passID] << endl;
                else
                    cout << "Invalid Pass! Access Denied.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
