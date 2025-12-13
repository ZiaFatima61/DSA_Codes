#include <iostream>
#include <string>
using namespace std;

// Product structure
struct Product {
    string name;
    int productID;
    int price;
};

// Lookup Table class
class LookupTable {
public:
    Product phone;
    Product shoes;
    Product laptop;
    Product watch;

    LookupTable();                 // Constructor
    Product search(string input);  // Lookup
    void display(Product p);       // Display details
    void updateProduct();          // Update product details
};

// Initialize products
LookupTable::LookupTable() {
    phone  = {"Smartphone", 101, 25000};
    shoes  = {"Shoes", 102, 3000};
    laptop = {"Laptop", 103, 60000};
    watch  = {"Watch", 104, 5000};
}

// Lookup function
Product LookupTable::search(string input) {
    if (input == phone.name)  return phone;
    if (input == shoes.name)  return shoes;
    if (input == laptop.name) return laptop;
    if (input == watch.name)  return watch;

    return {"", 0, 0}; // Not found
}

// Display product details
void LookupTable::display(Product p) {
    if (p.name != "") {
        cout << "\nProduct Name: " << p.name << endl;
        cout << "Product ID: " << p.productID << endl;
        cout << "Price: Rs. " << p.price << endl;
    } else {
        cout << "\nProduct not found." << endl;
    }
}

// Update product details
void LookupTable::updateProduct() {
    string name;
    int id, price;

    cin.ignore();
    cout << "Enter Product Name to Update: ";
    getline(cin, name);

    cout << "Enter New Product ID: ";
    cin >> id;
    cout << "Enter New Price: ";
    cin >> price;

    if (name == phone.name)       phone  = {name, id, price};
    else if (name == shoes.name)  shoes  = {name, id, price};
    else if (name == laptop.name) laptop = {name, id, price};
    else if (name == watch.name)  watch  = {name, id, price};
    else
        cout << "Product not recognized. Update failed." << endl;
}

// Main function
int main() {
    LookupTable mall;
    int choice;
    string input;

    while (true) {
        cout << "\n--- Mall Product Lookup System ---\n";
        cout << "1. Update Product Details\n";
        cout << "2. Search Product\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            mall.updateProduct();
            break;
        case 2:
            cin.ignore();
            cout << "Enter Product Name to Search: ";
            getline(cin, input);
            mall.display(mall.search(input));
            break;
        case 3:
            cout << "Exiting system..." << endl;
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}

