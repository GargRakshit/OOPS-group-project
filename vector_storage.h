#pragma once

#include <vector>
#include "inventory_class.h"

/*

  This file is to temporarily store the data that we read from a file
  into RAM using vectors, so that we can use Objects (otherwise the project
  will only be limited to file handling).

*/

using std::vector;

// storing objects inside a vector using the data from the file
void store_tech(vector<Tech>&);
void store_food(vector<Food>&);
void store_clothing(vector<Clothing>&);

// getting the index position of a perticular object inside the vector using product id
template<typename T>
int get_index(vector<T>&, int);

// removing a perticular object from both the vector and the file using product id
void erase_tech(vector<Tech>&, int);
void erase_food(vector<Food>&, int);
void erase_clothing(vector<Clothing>&, int);

// adding new object into the file and the vector
void add_tech(vector<Tech>&, Tech&);
void add_food(vector<Food>&, Food&);
void add_clothing(vector<Clothing>&, Clothing&);

// updating the price or the stock of an object
template<typename T>
void update_product(vector<T>&, int, float, std::string);

// accessing an object inside of the vector using the product id
template<typename T>
T& return_obj(vector<T>&, int);



//=======================================================================================================

// storing data from tech file into a vector
void store_tech(vector<Tech>& temp) {

  std::ifstream read_file_t(tech_file); // reading the tech file
  std::ifstream read_file_p(product_file); // reading the product file

  // defined in inventory_class.h
  PRODUCT_ATTRIBUTES; // defining temperory variables to get the data
  TECH_ATTRIBUTES;
  int id_p; // temporary varibale to check id in the product file

  // looping through the tech file(line by line) storing the data inside the temporary variables
  while (read_file_t >> id >> dimensions >> color >> weight >> warranty) {
    // looping thorugh the product file
    while (read_file_p >> id_p >> name >> category >> company >> price >> stock) {
      // check if the current id in the current file matches the id of the tech file
      // i.e. we are filtering out the tech products from the product file
      // so the data like company, price, etc(which are not in the tech file) are also stored in the vector object
      if (id_p == id) {
        // create a tech object
        Tech ob(id, name, category, company, price, stock, dimensions, color, weight, warranty);
        // add it to the vector
        temp.push_back(ob);
        break; // break the product loop and thus go to the next tech item and search product file again
      }
    }
  }
  read_file_t.close(); read_file_p.close(); // close the files
}

// storing data from food file into a vector (similar to tech)
void store_food(vector<Food>& temp) {

  std::ifstream read_file_f(food_file);
  std::ifstream read_file_p(product_file);

  PRODUCT_ATTRIBUTES;
  FOOD_ATTRIBUTES;
  int id_p;

  while (read_file_f >> id >> calories >> shelf_life) {
    while (read_file_p >> id_p >> name >> category >> company >> price >> stock) {
      if (id_p == id) {
        Food ob(id, name, category, company, price, stock, calories ,shelf_life);
        temp.push_back(ob);
        break;
      }
    }
  }
  read_file_f.close(); read_file_p.close();
}

// storing data from clothing file into a vector (similar to tech)
// just the attributes for reading the file are different
void store_clothing(vector<Clothing>& temp) {

  std::ifstream read_file_c(clothing_file);
  std::ifstream read_file_p(product_file);

  PRODUCT_ATTRIBUTES;
  CLOTHING_ATTRIBUTES;
  int id_p;

  while (read_file_c >> id >> cloth_type >> size) {
    while (read_file_p >> id_p >> name >> category >> company >> price >> stock) {
      if (id_p == id) {
        Clothing ob(id, name, category, company, price, stock, cloth_type, size);
        temp.push_back(ob);
        break;
      }
    }
  }
  read_file_c.close(); read_file_p.close();
}

//=======================================================================================================

// getting the index of an object inside the vector using its product id
template<typename T>
int get_index(vector<T>& search_vec, int id) {
  int t = 0; // declare temp variable and set it to 0
  // loop through the vector
  for (t=0; t < search_vec.size(); t++) {
    // search each object if its id is the same as the id we need
    if (search_vec.at(t).get_id() == id) {
      // if it is same then return that index position
      return t;
    }
  }
  std::cerr << "Invalid ID";
  return -1;
}

//=======================================================================================================

// to delete an object from the vector and the file
void erase_tech(vector<Tech>& search_vec, int id) {
  int index = get_index(search_vec, id); // get the index of the required object
  auto it = search_vec.begin() + index; // make an iterator for that index position(for .erase())
  search_vec.at(index).remove_tech(); // remove the data of the object from the files
  search_vec.erase(it); // remove the object from the vector
}

// similar to tech(the functions that remove from file are different)
void erase_food(vector<Food>& search_vec, int id) {
  int index = get_index(search_vec, id);
  auto it = search_vec.begin() + index;
  search_vec.at(index).remove_food();
  search_vec.erase(it);
}
// similar to tech
void erase_clothing(vector<Clothing>& search_vec, int id) {
  int index = get_index(search_vec, id);
  auto it = search_vec.begin() + index;
  search_vec.at(index).remove_clothing();
  search_vec.erase(it);
}

//=======================================================================================================

// to return an object from the vector using its product id
template<typename T>
T& return_obj(vector<T>& search_vec, int id) {
  return search_vec.at(get_index(search_vec, id)); // returning the object
}

//=======================================================================================================

// adding new objects/items to the vector and the file
void add_tech(vector<Tech>& store_vec, Tech& new_tech) {
  new_tech.add_tech_to_file(); // add to the file
  store_vec.push_back(new_tech); // add to the vector
}

void add_food(vector<Food>& store_vec, Food& new_food) {
  new_food.add_food_to_file(); //  add to the file
  store_vec.push_back(new_food); //  add to the vector
}

void add_clothing(vector<Clothing>& store_vec, Clothing& new_clothing) {
  new_clothing.add_clothing_to_file(); // add to the file
  store_vec.push_back(new_clothing); // add to the vector
}

//=======================================================================================================

// to update the price and the stock of a product
template<typename T>
void update_product(vector<T>& store_vec, int id, float update_value, std::string option) {
  // get the product using its id and update it
  store_vec.at(get_index(store_vec, id)).update_product(update_value, option);
}