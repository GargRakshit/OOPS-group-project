#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Employee {
private:
    int id;
    string name;
    string password;
    char role;

public:
    // Default constructor
    Employee() : id(0), name(""), password(""), role('\0') {}

    // Parameterized constructor
    Employee(int id, string name, string password, char role) : id(id), name(name), password(password), role(role) {}

    // Input
    int getId() { return id; }
    string getName() { return name; }
    string getPassword() { return password; }
    char getRole() { return role; }
};

const int MAX_EMPLOYEES = 100; // Maximum employees
Employee employees[MAX_EMPLOYEES] = {}; // Array to store employees
int numEmployees = 0; // Number of employees

void readEmployeesFromFile(string filename) {
    ifstream file(filename); // ifstream FOR READING "input" FILES, 'file' is the object for this input stream
    int id;
    string name, password;
    char role;
    while (file >> id >> name >> password >> role) {
        /*sabse pehle file likha, woh current stream mein jaayega, phir in order '>>' karke 
        it reads it in sequential form and stores it into variables id>>name>>password and so on*/
        employees[numEmployees++] = Employee(id, name, password, role);
    }
    file.close();
}

Employee* login() { // '*' because this FUNCTION is returning a pointer of type EMPLOYEE
    int username;
    string password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < numEmployees; i++) { // VERIFICATION
        if (employees[i].getId() == username && employees[i].getPassword() == password) {
            return &employees[i];
        }
    }
    return nullptr; // agar kucch dikkat aaye aur fail ho jaaye
}

void managerMenu() {
    cout << "\n";
    cout << "Manager Menu:" << endl;
    cout << "1. Update employee information" << endl;
    cout << "2. Manage stock" << endl;
    cout << "3. View transaction history" << endl;
    cout << "Press Esc to go back." << endl;
    cout << "\n";
}

void cashierMenu() {
    cout << "\n";
    cout << "Cashier Menu:" << endl;
    cout << "1. Billing" << endl;
    cout << "Press Esc to go back." << endl;
    cout << "\n";
}


