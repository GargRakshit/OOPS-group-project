#pragma once

#include "inventory_func.h"

/*

  This file contains the classes and methods for the inventory.

*/

// defining some macros to avoid long code repetition
#define PRODUCT_ATTRIBUTES int id; std::string name; std::string category; std::string company; float price; int stock;
#define TECH_ATTRIBUTES std::string dimensions; std::string color; float weight; int warranty;
#define FOOD_ATTRIBUTES float calories; std::string shelf_life;
#define CLOTHING_ATTRIBUTES std::string cloth_type; std::string size;

#define PRODUCT_CONSTRUCT int id, std::string name, std::string category, std::string company, float price, int stock
#define TECH_CONSTRUCT std::string dimensions, std::string color, float weight, int warranty
#define FOOD_CONSTRUCT float calories, std::string shelf_life
#define CLOTHING_CONSTRUCT std::string cloth_type, std::string size


// declaring the base class Product
class Product {
protected:
  PRODUCT_ATTRIBUTES; // declaring the protected variables

public:
  // Constructors
  Product(); // default constructor
  Product(PRODUCT_CONSTRUCT);

  void update_product(float, std::string); // member function to update price or stock

  // member functions to access private/protected member variables
  int get_id() const { return id; }
  std::string get_name() const { return name; }
  std::string get_company() const { return company; }
  float get_price() const { return price; }
  int get_stock() const { return stock; }
};

//=======================================================================================================

// inheriting derived class Tech from Product
class Tech : public Product {
  TECH_ATTRIBUTES; // declaring the private variables

public:
  // Constructor
  Tech(PRODUCT_CONSTRUCT, TECH_CONSTRUCT);

  void remove_tech(); // to remove a Tech object/product
  void add_tech_to_file(); // to add a Tech product in the file
};

//=======================================================================================================

// inheriting derived class Food from Product
class Food : public Product {
  FOOD_ATTRIBUTES; // declaring the private variables

public:
  // Constructor
  Food(PRODUCT_CONSTRUCT, FOOD_CONSTRUCT);

  void remove_food(); // to remove a Food object/product
  void add_food_to_file(); // to add a Food product in the file

  std::string get_shelf() { return shelf_life; }
};

//=======================================================================================================

// inheriting derived class Clothing from Product
class Clothing : public Product {
  CLOTHING_ATTRIBUTES; // declaring the private variables

public:
  // Constructor
  Clothing(PRODUCT_CONSTRUCT, CLOTHING_CONSTRUCT);

  void remove_clothing(); // to remove a Clothing object/product
  void add_clothing_to_file(); // to add a Clothing product in the file
};

//=======================================================================================================

// constructors
Product::Product() {
  // give some default values
  this->id = 0;
  this->name = "DEFAULT_NAME";
  this->category = "DEFAULT_CAT";
  this->company = "DEFAULT_COMP";
  this->price = 0;
  this->stock = 0;
}

Product::Product(PRODUCT_CONSTRUCT) {
  this->id = id;
  this->name = name;
  this->category = category;
  this->company = company;
  this->price = price;
  this->stock = stock;
}

Tech::Tech(PRODUCT_CONSTRUCT, TECH_CONSTRUCT) : Product::Product(id, name, category, company, price, stock) {
  this->dimensions = dimensions;
  this->color = color;
  this->weight = weight;
  this->warranty = warranty;
}

Food::Food(PRODUCT_CONSTRUCT, FOOD_CONSTRUCT) : Product::Product(id, name, category, company, price, stock) {
  this->calories = calories;
  this->shelf_life = shelf_life;
}

Clothing::Clothing(PRODUCT_CONSTRUCT, CLOTHING_CONSTRUCT) : Product::Product(id, name, category, company, price, stock) {
  this->cloth_type = cloth_type;
  this->size = size;
}

//=======================================================================================================

// methods
void Product::update_product(float update_value, std::string option) {
  update_item(id, update_value, option); // update the item in the file according to the option

  // check if the option is set to price or stock (else the update_item function will itself return error)
  if (option == "price") {
    price = update_value;
  }
  else if (option == "stock") {
    // using static cast to avoid warnings or further complications
    stock = static_cast<int>(update_value); // convert float to int, as stock is an int
  }
}


void Tech::remove_tech() {
  delete_tech(id); // delete from the txt file
}
void Food::remove_food() {
  delete_food(id); // delete from the txt file
}
void Clothing::remove_clothing() {
  delete_clothing(id); // delete from the txt file
}



void Tech::add_tech_to_file() {
  add_tech(id, name, company, price, stock, dimensions, color, weight, warranty); // add to the file
}

void Food::add_food_to_file() {
  add_food(id, name, company, price, stock, calories, shelf_life); // add to the file
}

void Clothing::add_clothing_to_file() {
  add_clothing(id, name, company, price, stock, cloth_type, size); // add to the file
}