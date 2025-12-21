#include <iostream>
#include <string>
using namespace std;

// BST Node for water consumption logs
struct ConsumptionNode {
    string areaName;  // Name of area or household
    int consumption;  // Water consumed in liters
    string timestamp; // Timestamp of log (YYYY-MM-DD)
    ConsumptionNode* left;
    ConsumptionNode* right;

    ConsumptionNode(string area, int cons, string time) {
        areaName = area;
        consumption = cons;
        timestamp = time;
        left = right = nullptr;
    }
};

// Insert a new log into BST
ConsumptionNode* insertLog(ConsumptionNode* root, string area, int cons, string time) {
    if (!root) return new ConsumptionNode(area, cons, time);
    if (cons < root->consumption)
        root->left = insertLog(root->left, area, cons, time);
    else
        root->right = insertLog(root->right, area, cons, time);
    return root;
}

// In-order traversal (sorted by consumption)
void displayLogs(ConsumptionNode* root) {
    if (!root) return;
    displayLogs(root->left);
    cout << root->timestamp << " | " << root->areaName << " | " << root->consumption << " liters\n";
    displayLogs(root->right);
}

// Range query: find logs in [low, high]
void rangeQuery(ConsumptionNode* root, int low, int high) {
    if (!root) return;
    if (root->consumption > low) rangeQuery(root->left, low, high);
    if (root->consumption >= low && root->consumption <= high)
        cout << root->timestamp << " | " << root->areaName << " | " << root->consumption << " liters\n";
    if (root->consumption < high) rangeQuery(root->right, low, high);
}

// Update log for a given area and timestamp
bool updateLog(ConsumptionNode* root, string area, string timestamp, int newConsumption) {
    if (!root) return false;
    if (root->areaName == area && root->timestamp == timestamp) {
        root->consumption = newConsumption;
        return true;
    }
    // Search both sides (BST is sorted by consumption, but updates can be anywhere)
    if (updateLog(root->left, area, timestamp, newConsumption)) return true;
    if (updateLog(root->right, area, timestamp, newConsumption)) return true;
    return false;
}

int main() {
    ConsumptionNode* root = nullptr;
    int choice;

    do {
        cout << "\n--- Smart Water System Menu ---\n";
        cout << "1. Add new water consumption log\n";
        cout << "2. Update existing log\n";
        cout << "3. Display all logs\n";
        cout << "4. Range query\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        if (choice == 1) {
            string area, timestamp;
            int consumption;
            cout << "Enter area name: ";
            getline(cin, area);
            cout << "Enter timestamp (YYYY-MM-DD): ";
            getline(cin, timestamp);
            cout << "Enter water consumption (liters): ";
            cin >> consumption;
            cin.ignore();
            root = insertLog(root, area, consumption, timestamp);
            cout << "Log added successfully.\n";
        }
        else if (choice == 2) {
            string area, timestamp;
            int newConsumption;
            cout << "Enter area name to update: ";
            getline(cin, area);
            cout << "Enter timestamp (YYYY-MM-DD): ";
            getline(cin, timestamp);
            cout << "Enter new water consumption: ";
            cin >> newConsumption;
            cin.ignore();
            if (updateLog(root, area, timestamp, newConsumption))
                cout << "Log updated successfully.\n";
            else
                cout << "Log not found!\n";
        }
        else if (choice == 3) {
            cout << "\nAll water consumption logs (sorted by consumption):\n";
            displayLogs(root);
        }
        else if (choice == 4) {
            int low, high;
            cout << "Enter water consumption range (low high): ";
            cin >> low >> high;
            cin.ignore();
            cout << "\nLogs in the range " << low << " - " << high << " liters:\n";
            rangeQuery(root, low, high);
        }
    } while (choice != 5);

    cout << "Exiting Smart Water System.\n";
    return 0;
}
