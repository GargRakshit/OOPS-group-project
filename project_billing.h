#pragma once
// for visual c++ compilers
// #pragma warning(disable : 4996)

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "vector_storage.h"

using namespace std;


// This class stores the bill number and customer details
class Bill_Info {
private:
    string customer_name;
    string customer_number;

public:
    string bill_number;
    // This function accepts cutomer details from the cashier
    void get_customer_details();
    // This function displays the customer details
    void display_customer_details();
    // Function to generate bill number
    void generate_Bill_Number();

    friend void write_billing_entry(Bill_Info& bill_info, Product product, int units);
};

void Bill_Info::get_customer_details() {
    cout << "Enter the customer's name: ";
    cin.ignore();
    getline(cin, customer_name);
    cout << "Enter the customer's phone number: ";
    cin >> customer_number;
}

void Bill_Info::generate_Bill_Number() {
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    int day = timeinfo->tm_mday;
    int month = timeinfo->tm_mon + 1;
    int year = timeinfo->tm_year + 1900;

    // Read last bill number from file or initialize to 0 if file doesn't exist
    int lastBillNumber = 0;
    ifstream inFile("last_bill_number.txt");
    if (inFile) {
        inFile >> lastBillNumber;
        inFile.close();
    }
    else {
        lastBillNumber = 0;
    }

    lastBillNumber++;

    // Write incremented bill number back to file
    ofstream outFile("last_bill_number.txt");
    if (outFile) {
        outFile << lastBillNumber;
        outFile.close();
    }
    else {
        cout << "Error: Unable to write to file.";
    }

    // Format bill number as DDMMYYYYNN
    string billNumber = to_string(day) + to_string(month) + to_string(year) +
        to_string(lastBillNumber);

    bill_number = billNumber;
}

void Bill_Info::display_customer_details() {
    cout << "Customer name:" << customer_name << endl;
    cout << "Customer phone number:" << customer_number << endl;
    cout << "Bill number:" << bill_number << endl;
}

void write_billing_entry(Bill_Info& bill_info, Product product, int units) {
    ofstream outFile("billing.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "6578"
            << '\t' << bill_info.bill_number << '\t' << bill_info.customer_name
            << '\t' << bill_info.customer_number << '\t' << product.get_id()
            << '\t' << product.get_name() << '\t' << units << '\t'
            << product.get_price() << '\t' << product.get_price() * units << "\n";
    }
    outFile.close();
}

void display_billing_data(string current_billnum) {
    ifstream inFile("billing.txt");
    string line;
    int sl_no = 1;

    cout << "----------------------------------------------------------------"
        << endl;
    cout << "| Sl.no. |"
        << " Product Name  |"
        << " Qty   |"
        << " Unit Price    |"
        << " Total Price |" << endl;
    cout << "----------------------------------------------------------------"
        << endl;
    // Read and display each line
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        int counter = 0;
        string bill_num;

        // Variables to store the values we want
        string productName;
        int qty;
        double unitPrice;
        double totalPrice;

        // Display values separated by commas
        while (getline(ss, token, '\t')) {
            if (counter == 1) // Bill number (index 1)
            {
                bill_num = token;
            }
            else if (counter == 5) // Product Name (index 5)
            {
                productName = token;
            }
            else if (counter == 6) // Qty (index 6)
            {
                qty = stoi(token);
            }
            else if (counter == 7) // Product Price (index 7)
            {
                unitPrice = stod(token);
            }
            else if (counter == 8) // Total Price (index 8)
            {
                totalPrice = stod(token);
            }
            counter++;
        }

        // Display the values
        if (current_billnum == bill_num) {
            cout << "| " << sl_no << "\t | " << productName << "\t | " << qty
                << "\t | " << unitPrice << "\t | " << totalPrice << "\t|"
                << endl;
            sl_no++;
        }
    }
    cout << "----------------------------------------------------------------\n"
        << endl;
    inFile.close();
}

void bill_interface(vector<Tech>& tech_container, vector<Food>& food_container, vector<Clothing>& clothing_container) {
    char choice;
    double total_bill_price = 0; // the final bill amount

    Product product;
    int current_product_id;      // the product id entered by the cashier
    int units;                   // the quantity of the product

    // Input
    Bill_Info bill_info;

    bill_info.get_customer_details();
    cout << "Initiating Billing Process..." << endl;
    bill_info.generate_Bill_Number();
    do {
        cout << "Enter the product ID: ";
        cin >> current_product_id;
        cout << "Enter the quantity: ";
        cin >> units;
        ifstream inputFile("product.txt"); // Open the file inventory
        // Read the file line by line
        int flag = 0;
        int temp_id; string name; string category; string company; float price; int stock;
        while (inputFile >> temp_id >> name >> category >> company >> price >> stock) {
            if (temp_id == current_product_id) {
                flag = 1;
                if (stock < units) {
                    flag = 2;
                    break;
                }
                Product temp_product(temp_id, name, category, company, price, stock);
                product = temp_product;
                total_bill_price += price * units;

                if (category == "tech") {
                    inputFile.close();
                    update_product(tech_container, current_product_id, (stock - units), "stock");
                }
                else if (category == "food") {
                    inputFile.close();
                    update_product(food_container, current_product_id, (stock - units), "stock");
                }
                else if (category == "clothing") {
                    inputFile.close();
                    update_product(clothing_container, current_product_id, (stock - units), "stock");
                }
                break;
            }
        }

        if (flag == 0) {
            cout << "ID not found\nDo you want to enter again?(Y/N): " << endl;
            cin >> choice;
            continue;
        }
        else if (flag == 2) {
            cout << "Insufficient stock\nDo you want to enter again?(Y/N): " << endl;
            cin >> choice;
            continue;
        }
        write_billing_entry(bill_info, product, units);

        cout << "Would you like to process more products? (Y/N): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    // DISPLAYING OF THE FINAL BILL
    cout << "Cashier ID: " << endl;
    cout << "================================================================"
        << endl;
    cout << "                            BILL" << endl;
    cout << "================================================================\n"
        << endl;
    bill_info.display_customer_details();
    display_billing_data(bill_info.bill_number);
    cout << "Total price : Rs." << total_bill_price << endl;
    cout << "----------------------------------------------------------------\n"
        << endl;

}
