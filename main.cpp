#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;


class Product {
private:
    int id;
    string name;
    float price;
    int quantity;

public:
    Product(int id = 0, string name = "", float price = 0.0, int quantity = 0) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }

   
    int getId() const { return id; }
    string getName() const { return name; }
    float getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    
    void setQuantity(int q) { quantity = q; }

    
    void display() const {
        cout << setw(5) << id << setw(15) << name << setw(10)
             << price << setw(10) << quantity << endl;
    }

    
    string toFileString() const {
        return to_string(id) + "," + name + "," + to_string(price) + "," + to_string(quantity);
    }
};


map<int, Product> inventory;


void loadFromFile() {
    ifstream file("inventory.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, priceStr, qtyStr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, qtyStr, ',');

        int id = stoi(idStr);
        float price = stof(priceStr);
        int qty = stoi(qtyStr);

        Product p(id, name, price, qty);
        inventory[id] = p;
    }
    file.close();
}


void saveToFile() {
    ofstream file("inventory.txt");
    for (auto &pair : inventory) {
        file << pair.second.toFileString() << endl;
    }
    file.close();
}


void addProduct() {
    int id;
    string name;
    float price;
    int quantity;

    cout << "Enter Product ID: ";
    cin >> id;
    if (inventory.find(id) != inventory.end()) {
        cout << "Product with this ID already exists!" << endl;
        return;
    }
    cin.ignore(); 
    cout << "Enter Product Name: ";
    getline(cin, name);
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Quantity: ";
    cin >> quantity;

    Product p(id, name, price, quantity);
    inventory[id] = p;
    saveToFile();
    cout << "✅ Product added successfully.\n";
}


void viewProducts() {
    cout << setw(5) << "ID" << setw(15) << "Name" << setw(10)
         << "Price" << setw(10) << "Qty" << endl;
    cout << "-----------------------------------------" << endl;
    for (auto &pair : inventory) {
        pair.second.display();
    }
}


void updateStock() {
    int id, qty;
    cout << "Enter Product ID to update: ";
    cin >> id;
    if (inventory.find(id) == inventory.end()) {
        cout << "Product not found.\n";
        return;
    }
    cout << "Enter new quantity: ";
    cin >> qty;
    inventory[id].setQuantity(qty);
    saveToFile();
    cout << "✅ Stock updated.\n";
}


void searchProduct() {
    int id;
    cout << "Enter Product ID to search: ";
    cin >> id;
    if (inventory.find(id) != inventory.end()) {
        cout << "\nProduct found:\n";
        cout << setw(5) << "ID" << setw(15) << "Name" << setw(10)
             << "Price" << setw(10) << "Qty" << endl;
        inventory[id].display();
    } else {
        cout << "Product not found.\n";
    }
}


void lowStockAlert(int threshold = 5) {
    cout << "\n⚠️  Low Stock Products (Qty < " << threshold << "):\n";
    cout << setw(5) << "ID" << setw(15) << "Name" << setw(10)
         << "Price" << setw(10) << "Qty" << endl;
    cout << "-----------------------------------------" << endl;
    for (auto &pair : inventory) {
        if (pair.second.getQuantity() < threshold) {
            pair.second.display();
        }
    }
}


void menu() {
    int choice;
    do {
        cout << "\n📦 === Inventory Management Menu === 📦\n";
        cout << "1. Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Update Stock\n";
        cout << "4. Search Product\n";
        cout << "5. Low Stock Alert\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: updateStock(); break;
            case 4: searchProduct(); break;
            case 5: lowStockAlert(); break;
            case 6: cout << "Exiting... Thank you!\n"; break;
            default: cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 6);
}


int main() {
    loadFromFile(); 
    menu();
    return 0;
}
