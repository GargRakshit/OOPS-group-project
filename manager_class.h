#pragma once
#include<string>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "vector_storage.h"

using namespace std;

#define TAB '\t'


//#define ESC 27
class Manager
{
// protected:
//     //MANAGER INFO
//     int id;
//     string ename;
//     string phoneNo;

// public:
//     //MANAGER INFO
//     void managerDisp(){
//         cout<<id<<endl<<ename<<endl<<phoneNo<<endl;
//     }
    public:
    //EMPLOYEE
    //to add employees
    void empAdd(int id,string name,string password,string role);
    //to update details of employee
    void empUpdate(int id,string option,string value);
    //to delete details of employee
    void empDelete(int id);
    //to display details of employee
    void empDisplay();

    //INVENTORY
    //to add products to inventory
    void productAdd(vector<Tech>& container, Tech& t);
    void productAdd(vector<Food>& container, Food& t);
    void productAdd(vector<Clothing>& container, Clothing& t);
    //to update details of inventory
    template<typename T>
    void invUpdate(vector<T>& container, int id, float value, string option);
    //to delete details of inventory
    void invDelete(vector<Tech>& container, int id);
    void invDelete(vector<Food>& container, int id);
    void invDelete(vector<Clothing>& container, int id);
    //to display details of inventory
    void invDisplay();

    //CASHIER
    //to display transaction
    void dispTransaction();
    //to display customer info
    void dispCustomerinfo();

};

void Manager::empDisplay(){
    ifstream read_file("empinfo.txt");
  int temp_id; string name; string password; string role;
  while (read_file >> temp_id >> name >> password >> role ) {
    cout << temp_id << TAB << name << TAB << password << TAB << role<< endl;
    }
  read_file.close();

}

void Manager::empDelete(int id){
    ifstream read_file("empinfo.txt");

  ofstream write_file;
  write_file.open("temp_e.txt",ofstream::out);

  int temp_id;
  string name;
    string password;
    string role;

  while (read_file >> temp_id >> name >> password>> role) {
    if (temp_id != id) {
      write_file << temp_id << TAB << name << TAB << password<< TAB << role << "\n";
    }
  }
  read_file.close(); write_file.close();
  remove("empinfo.txt");
  int re;
  re = rename("temp_e.txt","empinfo.txt");
  if (re) {
    cerr << "Deleting empdata failed";
  }
}

void Manager::empAdd(int id,string name,string password,string role){
    ofstream append_file;
  append_file.open("empinfo.txt", ofstream::app);
    append_file << id << TAB << name << TAB << password << TAB << role << "\n";
  append_file.close();
}

void Manager::empUpdate(int id,string option,string value){
    ifstream read_file("empinfo.txt");

  ofstream write_file;
  write_file.open("temp_update.txt", ofstream::out);

  int temp_id; string name; string password;string role;

  int flag = 0;
  while (read_file >> temp_id >> name >> password >> role) {

    if (temp_id == id) {
      flag = 1;
      if (option == "password") {
        password = value;
      }
      else if (option == "role") {
        role = value; 
      }
      else {
        cerr << "Invalid option chosen: " << option << endl;
      }
    }
    write_file << temp_id << TAB << name << TAB << password << TAB << role<<"\n";
  }
  if (!flag) {
    cerr << "ID not found: " << id << endl;
  }

  read_file.close(); write_file.close();
  remove(product_file);
  int re;
  re = rename("temp_update.txt", "empinfo.txt");
  if (re) {
    std::cerr << "Deleting empdata failed";
  }
}

/*void Manager::dispCustomerinfo(){
    ifstream read_file("customer_info.txt");
  string name,customer_number;
    int points;
  while (read_file >> name >> customer_number>>points ) {
    cout <<name<< TAB << customer_number<< TAB << points <<endl;
    }
  read_file.close();
}*/

void Manager::dispTransaction(){
    ifstream read_file("billing.txt");
    int productId ,qty, price, totalPrice;
    string billNo,customerName,customer_number,cashierId, productName;
  while (read_file >>cashierId >>billNo >>customerName >>customer_number >>productId >> productName >>qty>>price >>totalPrice ) {
    cout <<cashierId<<TAB<<billNo<<TAB<<customerName<<TAB<<customer_number<<TAB<<productId<<TAB<<productName<<TAB<<qty<<TAB<<price<<TAB<<totalPrice<<endl;
    }
  read_file.close();
}

void Manager::productAdd(vector<Tech>& container, Tech& t) {
  add_tech(container, t);
}

void Manager::productAdd(vector<Food>& container, Food& f) {
  add_food(container, f);
}
void Manager::productAdd(vector<Clothing>& container, Clothing& c) {
  add_clothing(container, c);
}

template<typename T>
void Manager::invUpdate(vector<T>& container, int id, float value, string option) {
  update_product(container, id, value, option);
}

void Manager::invDelete(vector<Tech>& container, int id) {
  erase_tech(container, id);
}
void Manager::invDelete(vector<Food>& container, int id) {
  erase_food(container, id);
}
void Manager::invDelete(vector<Clothing>& container, int id) {
  erase_clothing(container, id);
}

void Manager::invDisplay() {
  show_inventory();
}