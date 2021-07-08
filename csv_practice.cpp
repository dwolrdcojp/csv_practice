// Project: CSV Practice
// File: csv_practice.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

void create()
{
	// file pointer
	std::fstream fout;

	// opens an existing csv file or creates a new file
	fout.open("reportcard.csv", std::ios::out | std::ios::app);

	std::cout << "Enter the details of 5 students:"
		  << " roll name math phy chem bio"
	          << std:: endl;

	int i, roll, phy, chem, math, bio;
	std::string name;

	// Read the input
	for (i = 0; i < 5; i++) {

		std::cin >> roll
			 >> name
			 >> math
			 >> phy
			 >> chem
			 >> bio;

		// Insert the data to file
		fout << roll << ", "
			  << name << ", "
			  << math << ", "
			  << phy  << ", "
			  << chem << ", "
			  << bio
			  << "\n";
	}
}


void read_record()
{

	// File pointer
	std::fstream fin;

	// Open an existing file
	fin.open("reportcard.csv", std::ios::in);

	// Get the roll number
	// of which the data is required
	int rollnum, roll2, count = 0;
	std::cout << "Enter the roll number "
		<< "of the student to display details: ";
	std::cin >> rollnum;

	// Read the Data from the file
	// as String Vector
	std::vector<std::string> row;
	std::string line, word, temp;
	
	while (1) {

		row.clear();

		// read an entire row and
		// store it in a string variable 'line'
		getline(fin, line);

		// used for breaking words
		std::stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (std::getline(s, word, ',')) {

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}
		
		// convert string to integer for comparision
		roll2 = stoi(row[0]);

		// Compare the roll number
		if (roll2 == rollnum) {

			// Print the found data
			count = 1;
			std::cout << "Details of Roll " << row[0] << " : \n";
			std::cout << "Name: " << row[1] << "\n";
			std::cout << "Maths: " << row[2] << "\n";
			std::cout << "Physics: " << row[3] << "\n";
			std::cout << "Chemistry: " << row[4] << "\n";
			std::cout << "Biology: " << row[5] << "\n";
			break;
		}
	}
	if (count == 0)
		std::cout << "Record not found\n";
}

int main()
{
	// create();
	read_record();

	return 0;
}


