#include<conio.h>
#include "employee2.h"
#include "manager_class.h"
#include "project_billing.h"


using namespace std;


vector<Tech> tech_container;
vector<Clothing> clothing_container;
vector<Food> food_container;

void menuProd(){//Manager menu for managing stock
  cout << "\n";
  cout << "1. Add new product" << endl;
  cout << "2. Delete product" << endl;
  cout << "3. Update product" << endl;
  cout << "4. Show all products" << endl;
  cout << "Press ESC to go back" << endl;
  cout << "\n";
}


void menuAddProd(){//Manager menu for adding an item
  cout << "\n";
  cout << "1. Add new Tech product" << endl;
  cout << "2. Add new Food product" << endl;
  cout << "3. Add new Clothing product" << endl;
  cout << "\n";
}


void menuDeleteProd(){//Manager menu for deleting an item
  cout << "\n";
  cout << "1. Delete Tech product" << endl;
  cout << "2. Delete Food product" << endl;
  cout << "3. Delete Clothing product" << endl;
  cout << "\n";
}

void menuUpdateProd(){//Manager menu for updating an item
  cout << "\n";
  cout << "1. Update Tech product" << endl;
  cout << "2. Update Food product" << endl;
  cout << "3. Update Clothing product" << endl;
  cout << "\n";
}

void opAddTech(Manager& m){
  int id;
  string name, category, company, dimensions, color;
  float price, weight;
  int stock, warranty;

  cout << "Enter product id: ";
  cin >> id;
  cout << "Enter product name: ";
  cin >> name;
  cout << "Enter product category: ";
  cin >> category;
  cout << "Enter product company: ";
  cin >> company;
  cout << "Enter product price: ";
  cin >> price;
  cout << "Enter product stock: ";
  cin >> stock;
  cout << "Enter product dimensions: ";
  cin >> dimensions;
  cout << "Enter product color: ";
  cin >> color;
  cout << "Enter product weight: ";
  cin >> weight;
  cout << "Enter product warranty: ";
  cin >> warranty;

  // Create a Tech object
  Tech temp_tech(id, name, category, company, price, stock, dimensions, color, weight, warranty);

  // Pass the object to productAdd by reference
  m.productAdd(tech_container, temp_tech);
}

void opAddFood(Manager& m){
  int id;
  string name, category, company, shelf_life;
  float price, calories;
  int stock;

  cout << "Enter product id: ";
  cin >> id;
  cout << "Enter product name: ";
  cin >> name;
  cout << "Enter product category: ";
  cin >> category;
  cout << "Enter product company: ";
  cin >> company;
  cout << "Enter product price: ";
  cin >> price;
  cout << "Enter product stock: ";
  cin >> stock;
  cout << "Enter product calories: ";
  cin >> calories;
  cout << "Enter product shelf life: ";
  cin >> shelf_life;

  // Create a Food object
  Food temp_food(id, name, category, company, price, stock, calories, shelf_life);
  // Pass the object to productAdd by reference
  m.productAdd(food_container, temp_food);
}

void opAddClothing(Manager& m){
  int id;
  string name, category, company, cloth_type, size;
  float price;
  int stock;

  cout << "Enter product id: ";
  cin >> id;
  cout << "Enter product name: ";
  cin >> name;
  cout << "Enter product category: ";
  cin >> category;
  cout << "Enter product company: ";
  cin >> company;
  cout << "Enter product price: ";
  cin >> price;
  cout << "Enter product stock: ";
  cin >> stock;
  cout << "Enter product cloth type: ";
  cin >> cloth_type;
  cout << "Enter product size: ";
  cin >> size;

  // Create a Food object
  Clothing temp_clothing(id, name, category, company, price, stock, cloth_type, size);
  // Pass the object to productAdd by reference
  m.productAdd(clothing_container, temp_clothing);
}

//Add Functions completed here for the manager in the inventory

//Now starting with Delete functions

void opDelTech(Manager &m){
  int id;
  cout << "Enter the ID you want to delete: ";
  cin >> id;

  m.invDelete(tech_container, id);
}

void opDelFood(Manager &m){
  int id;
  cout << "Enter the ID you want to delete: ";
  cin >> id;

  m.invDelete(food_container, id);
}

void opDelClothing(Manager &m){
  int id;
  cout << "Enter the ID you want to delete: ";
  cin >> id;

  m.invDelete(clothing_container, id);
}

//Delete Functions completed here for the manager in the inventory

//Now starting with Update functions

void opUpdateTechProd(Manager &m){
  int id;
  float value;
  string option;
  cout << "Enter the ID of the product you want to update: ";
  cin >> id;
  cout << "Enter the updated value you want to update: ";
  cin >> value;
  cout << "Enter the option(stock or price) you want to update: ";
  cin >> option;
  m.invUpdate(tech_container, id, value, option);
}

void opUpdateFoodProd(Manager &m){
  int id;
  float value;
  string option;
  cout << "Enter the ID of the product you want to update: ";
  cin >> id;
  cout << "Enter the updated value you want to update: ";
  cin >> value;
  cout << "Enter the option(stock or price) you want to update: ";
  cin >> option;
  m.invUpdate(food_container, id, value, option);
}

void opUpdateClothingProd(Manager &m){
  int id;
  float value;
  string option;
  cout << "Enter the ID of the product you want to update: ";
  cin >> id;
  cout << "Enter the updated value you want to update: ";
  cin >> value;
  cout << "Enter the option(stock or price) you want to update: ";
  cin >> option;
  m.invUpdate(clothing_container, id, value, option);
}

//Update Functions completed here for the manager in the inventory

//Now starting with Display function

void opDisplayProd(Manager &m){
  m.invDisplay();
}

//Display Function completed here for the manager in the inventory

//STARTING WITH EMPLOYEE FUNCTIONS FOR MANAGER


void menuEmp(){
  cout << "\n";
  cout << "1. Add new employee" << endl;
  cout << "2. Delete employee" << endl;
  cout << "3. Update employee" << endl;
  cout << "4. Show all employees" << endl;
  cout << "\n";
}

//Now starting with the add function 
void opAddEmp(Manager &m){
  int id;
  string name, password, role;
  cout << "Enter employee id: ";
  cin >> id;
  cout << "Enter employee name: ";
  cin >> name;
  cout << "Enter employee password: ";
  cin >> password;
  cout << "Enter employee role: ";
  cin >> role;
  m.empAdd(id, name, password, role);
}

//Now starting with the delete function 
void opDelEmp(Manager &m){
  int id;
  cout << "Enter employee id you want to delete: ";
  cin >> id;
  m.empDelete(id); 
}

//Now starting with the update function 
void opUpdateEmp(Manager &m){
  int id;
  string option,value;
  cout << "Enter employee id you want to update: ";
  cin >> id;
  cout << "Enter the option(password or role): ";
  cin >> option;
  cout << "Enter the updated value: ";
  m.empUpdate(id, option, value); 
}

//Now starting with the display function
void opDisplayEmp(Manager &m){
  cout << "\n";
  m.empDisplay();
  cout << "\n";
}

//DISPLAYING THE TRANSACTION HISTORY

void opDisplayTransac(Manager &m){
  cout << "\n";
  m.dispTransaction();
  cout << "\n";
}
// DONE WITH MANAGER OPTIONS

int main() {
  store_tech(tech_container);
  store_clothing(clothing_container);
  store_food(food_container);
  //Employee 
  readEmployeesFromFile("empinfo.txt");
  int flag=1;
  char op;
  Employee* loggedInUser = nullptr;
  do {
    loggedInUser = login();
    if (!loggedInUser) {
        cout << "Invalid username or password. Please try again." << endl;
    }
  } while (!loggedInUser);
  do{
    // Display menu based on role
    if (loggedInUser->getRole() == 'm') {
      Manager m;
      ctrl1manager:
      cout << "Welcome, " << loggedInUser->getName() << "!" << endl;
      managerMenu();
      op = _getch();
      
      //Manager menu entry for managing stock
      if (op=='2'){//Manager menu entry for managing stock
        ctrl2prod:
        menuProd();
        op = _getch();
        if (op=='1'){// manager menu entry for adding a product
          menuAddProd();
          op = _getch();
          if(op=='1'){//manager menu entry for adding tech product
            opAddTech(m);
            goto ctrl2prod;
          }
          else if(op=='2'){//manager menu entry for adding food product
            opAddFood(m);
            goto ctrl2prod;
          }
          else if(op=='3'){//manager menu entry for adding clothing product
            opAddClothing(m);
            goto ctrl2prod;
          }
        }
        else if(op=='2'){// manager menu entry for deleting a product
          menuDeleteProd();
          op = _getch();
          if(op==1){//manager menu entry for deleting tech product
            opDelTech(m);
            goto ctrl2prod;
          }
          else if(op=='2'){//manager menu entry for deleting food product
            opDelFood(m);
            goto ctrl2prod;
          }
          else if(op=='3'){//manager menu entry for deleting clothing 
            opDelClothing(m);
            goto ctrl2prod;
          }
        }
        else if(op=='3'){//manager menu entry for updating product info
          menuUpdateProd();
          op = _getch();
          if(op=='1'){//manager menu entry for updating tech product
            opUpdateTechProd(m);
            goto ctrl2prod;
          }
          else if(op=='2'){//manager menu entry for updating food product
            opUpdateFoodProd(m);
            goto ctrl2prod;
        }
          else if(op=='3'){//manager menu entry for updating clothing product
            opUpdateClothingProd(m);
            goto ctrl2prod;
          }
        }
        else if(op=='4'){//manager menu entry for displaying the product list
          cout << "\n";
          opDisplayProd(m);
          goto ctrl2prod;
        }
        else if(op==27){
          goto ctrl1manager;
        }
      }

      //Starting with editing employee file options
      else if(op=='1'){//manager menu entry for managing the emp file
        ctrl2emp:
        menuEmp();
        op = _getch();
        if(op=='1'){//manager menu entry for adding an employee
          opAddEmp(m);
          goto ctrl2emp;
        }
        else if(op=='2'){//manager menu entry for deleting an emoloyee
          opDelEmp(m);
          goto ctrl2emp;
        }
        else if(op=='3'){//manager menu entry for updating emp details
          opUpdateEmp(m);
          goto ctrl2emp;
        }
        else if(op=='4'){//manager menu entry for dispalying all emp
          opDisplayEmp(m);
          goto ctrl2emp;
        }
        else if(op==27){
          goto ctrl1manager;
        }
      }
      
      
      //Manager menu entry for viewing transaction
      else if(op=='3'){
        opDisplayTransac(m);
        goto ctrl1manager;
      }
      else if (op==27){
        flag=0;
      }
    }
    else if (loggedInUser->getRole() == 'c') {
      ctrl1cashier:
      cout << "Welcome, " << loggedInUser->getName() << "!" << endl;
      cashierMenu();
      op = _getch();
      if(op=='1'){
        bill_interface(tech_container ,food_container , clothing_container);
        goto ctrl1cashier;
      }
      else if (op==27){
        flag=0;
      }
    }
  } while(flag!=0);
  cout << "Thank you for using the program!" << endl;
  return 0;
}
