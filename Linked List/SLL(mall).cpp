#include <iostream>
#include <string>
using namespace std;

// Shop node
struct Shop {
    int shopID;
    string tenant;
    string category;
    string status;   // Occupied / Vacant
    Shop* next;
};

class ShopList {
private:
    Shop* head;

public:
    ShopList() {
        head = nullptr;
    }

    // Add new shop (O(1))
    void addShop(int id, string tenant, string category, string status) {
        Shop* newShop = new Shop();
        newShop->shopID = id;
        newShop->tenant = tenant;
        newShop->category = category;
        newShop->status = status;
        newShop->next = head;
        head = newShop;
    }

    // Remove tenant (mark vacant)
    void markVacant(int id) {
        Shop* temp = head;
        while (temp != nullptr) {
            if (temp->shopID == id) {
                temp->tenant = "None";
                temp->status = "Vacant";
                cout << "Shop " << id << " marked as Vacant.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Shop not found.\n";
    }

    // Display shops
    void displayShops() {
        Shop* temp = head;
        cout << "\nShop List:\n";
        while (temp != nullptr) {
            cout << "Shop ID: " << temp->shopID
                 << ", Tenant: " << temp->tenant
                 << ", Category: " << temp->category
                 << ", Status: " << temp->status << endl;
            temp = temp->next;
        }
    }
};

int main() {

    // Linked List for Floor 1
    ShopList floor1;

    // Add shops
    floor1.addShop(101, "ZARA", "Clothing", "Occupied");
    floor1.addShop(102, "NIKE", "Sportswear", "Occupied");
    floor1.addShop(103, "H&M", "Clothing", "Occupied");

    floor1.displayShops();

    // Tenant leaves shop 102
    floor1.markVacant(102);

    floor1.displayShops();

    return 0;
}
