#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

/*

	This file has the functions to perform actions related
	to file handling.

	NOTE - always keep a newline at the end of the txt files

*/

#define TAB '\t'

// declaring variables from the file names
// the product file has common attributes that all categories have
const char* product_file = "product.txt";
const char* tech_file = "product_tech.txt";
const char* food_file = "product_food.txt";
const char* clothing_file = "product_clothing.txt";

// showing the entire inventory
void show_inventory();

// deleting products according to id
void delete_product(int);
void delete_tech(int);
void delete_food(int);
void delete_clothing(int);

// updating the price or stock of a product
void update_item(int, float, std::string);

// adding new products to the file
void add_product(int, std::string, std::string, std::string, float, int);
void add_tech(int, std::string, std::string, float, int, std::string, std::string,float, int);
void add_food(int, std::string, std::string, float, int, float, std::string);
void add_clothing(int, std::string, std::string, float, int, std::string, std::string);


//=======================================================================================================


// showing inventory
void show_inventory() {
	// read the product file
	std::ifstream read_file(product_file);
	// declare temporary variables 
	int temp_id; std::string name; std::string category; std::string company; float price; int stock;
	// loop through teh file reading each line and storing the whitespace/tab seperated data inside the variables
	while (read_file >> temp_id >> name >> category >> company >> price >> stock) {
		// printing out the variables
    std::cout << temp_id << std::setw(20) << name << std::setw(20) << category << std::setw(20) << company << std::setw(20)
      << price << std::setw(20) << stock <<  std::endl;
	}
	read_file.close(); // closing the file
}

//=======================================================================================================

// to delete a product(line) from the product file using the id
void delete_product(int id) {
	// read the file
	std::ifstream read_file(product_file);

	// make a temporary file to write in
	std::ofstream write_file;
	write_file.open("temp_p.txt", std::ofstream::out);

	// decalre temporary variables
	int temp_id;
	std::string name;
	std::string category;
	std::string company;
	float price;
	int stock;

	int flag = 0;
	// loop through the file(through each line) storing the data in variables
	while (read_file >> temp_id >> name >> category >> company >> price >> stock) {
		// check if the given id matched the id at the current line
		if (temp_id != id) {
			// if not then write that line in the temporary file
			write_file << temp_id << TAB << name << TAB << category<< TAB << company << TAB << price << TAB << stock << "\n";
		}
		else {
			flag = 1;
		}
	}
	// that is we are skipping/ not writing the line of the product to be deleted in the temp file
	if (!flag) {
		std::cerr << "ID not found: " << id << std::endl;
	}
	read_file.close(); write_file.close(); // close both files
	remove(product_file); // remove the product file
	int re;
	re = rename("temp_p.txt", product_file); // rename the temp file as our product file, that is replacing it
											 // without the product we need to delete(i.e. removing the product)
	if (re) {
		std::cerr << "Deleting product failed";
	}
}

// deleting from the tech file
// similar to delete_product only with different attributes/variables
void delete_tech(int id) {
	std::ifstream read_file(tech_file);

	std::ofstream write_file;
	write_file.open("temp_t.txt", std::ofstream::out);

	int temp_id;
	std::string dimensions;
	std::string color;
	float weight;
	int warranty;

	int flag = 0;
	while (read_file >> temp_id >> dimensions >> color >> weight >> warranty) {
		if (temp_id != id) {
			write_file << temp_id << TAB << dimensions << TAB << color << TAB << weight << TAB << warranty << "\n";
		}
		else {
			flag = 1;
		}
	}
	if (!flag) {
		std::cerr << "ID not found: " << id << std::endl;
	}
	read_file.close(); write_file.close();
	remove(tech_file);
	int re;
	re = rename("temp_t.txt", tech_file);
	if (re) {
		std::cerr << "Deleting product failed";
	}

	// call the delete_product to also remove the tech product from the product file
	delete_product(id);
}

// deleting from the food file
// similar to delete_product only with different attributes/variables
void delete_food(int id) {
	std::ifstream read_file(food_file);

	std::ofstream write_file;
	write_file.open("temp_f.txt", std::ofstream::out);

	int temp_id;
	float calories;
	std::string shelf_life;

	int flag = 0;
	while (read_file >> temp_id >> calories >> shelf_life) {
		if (temp_id != id) {
			write_file << temp_id << TAB << calories << TAB << shelf_life << "\n";
		}
		else {
			flag = 1;
		}
	}
	if (!flag) {
		std::cerr << "ID not found: " << id << std::endl;
	}
	read_file.close(); write_file.close();
	remove(food_file);
	int re;
	re  = rename("temp_f.txt", food_file);
	if (re) {
		std::cerr << "Deleting product failed";
	}

	// call the delete_product to also remove the food product from the product file
	delete_product(id);
}

// deleting from the clothing file
// similar to delete_product only with different attributes/variables
void delete_clothing(int id) {
	std::ifstream read_file(clothing_file);

	std::ofstream write_file;
	write_file.open("temp_c.txt", std::ofstream::out);

	int temp_id;
	std::string cloth_type;
	std::string size;

	int flag = 0;
	while (read_file >> temp_id >> cloth_type >> size) {
		if (temp_id != id) {
			write_file << temp_id << TAB << cloth_type << TAB << size << "\n";
		}
		else {
			flag = 1;
		}
	}
	if (!flag) {
		std::cerr << "ID not found: " << id << std::endl;
	}
	read_file.close(); write_file.close();
	remove(clothing_file);
	int re;
	re = rename("temp_c.txt", clothing_file);
	if (re) {
		std::cerr << "Deleting product failed";
	}

	// call the delete_product to also remove the clothing product from the product file
	delete_product(id);
}

//=======================================================================================================

// to update the price and stock of an item(which is stored only in product file)
void update_item(int id, float item_update, std::string option) {
	std::ifstream read_file(product_file); // read the product file

	std::ofstream write_file; // open a temp file to write data in
	write_file.open("temp_update.txt", std::ofstream::out);

	//  declare temp variables
	int temp_id; std::string name; std::string category; std::string company; float price; int stock;

	int flag = 0; // flag to check if id exists
	// loop through the file
	while (read_file >> temp_id >> name >> category >> company >> price >> stock) {

		// check if the id given matches the id from the line
		if (temp_id == id) {
			flag = 1; // if yes then set flag to 1
			// check which thing to update- price/stock
			if (option == "price") {
				price = item_update; // set the price to the given price
			}
			else if (option == "stock") {
				stock = static_cast<int>(item_update); // set stock to the given stock
			}
			else {
				// if anything other than stock or price is given show error
				std::cerr << "Invalid option chosen: " << option << std::endl;
			}
		}
		// write these new values into the temp file
		write_file << temp_id << TAB << name << TAB << category << TAB << company << TAB << price << TAB << stock << "\n";
	}
	// if the flag is still 0, id was not found
	if (!flag) {
		std::cerr << "ID not found: " << id << std::endl;
	}

	read_file.close(); write_file.close(); // close the files
	remove(product_file); // remove the product file
	int re;
	re = rename("temp_update.txt", product_file); // replace the temp file with the new values
	if (re) {
		std::cerr << "Updating product failed";
	}
}

//=======================================================================================================

// adding new products in the product file
void add_product(int id, std::string name, std::string category, std::string company, float price, int stock) {

	// open file in append mode
	std::ofstream append_file;
	append_file.open(product_file, std::ofstream::app);

	// append/write the attributes into the file
	append_file << id << TAB << name << TAB << category << TAB << company << TAB << price << TAB << stock << "\n";
	append_file.close(); // close the file
}

// adding new products in the tech file
void add_tech(int id, std::string name, std::string company, float price, int stock,
				std::string dimensions, std::string color, float weight, int warranty) {

	// add the products in the product file also, so call add_product
	add_product(id, name, "tech", company, price, stock);

	// open file in append mode
	std::ofstream append_file;
	append_file.open(tech_file, std::ofstream::app);

	// append/write the attributes into the file
	append_file << id << TAB << dimensions << TAB << color << TAB << weight << TAB << warranty << "\n";
	append_file.close(); // close the file
}

// adding new products in the food file
void add_food(int id, std::string name, std::string company, float price, int stock, float calories, std::string shelf_life) {
	// add the products in the product file also, so call add_product
	add_product(id, name, "food", company, price, stock);

	// open file in append mode
	std::ofstream append_file;
	append_file.open(food_file, std::ofstream::app);

	// append/write the attributes into the file
	append_file << id << TAB << calories << TAB << shelf_life << "\n";
	append_file.close(); // close the file
}

// adding new products in the clothing file
void add_clothing(int id, std::string name, std::string company, float price, int stock, std::string cloth_type, std::string size) {
	// add the products in the product file also, so call add_product
	add_product(id, name, "clothing", company, price, stock);

	// open file in append mode
	std::ofstream append_file;
	append_file.open(clothing_file, std::ofstream::app);

	// append/write the attributes into the file
	append_file << id << TAB << cloth_type << TAB << size << "\n";
	append_file.close(); // close the file
}