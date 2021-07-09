// Project: CSV Practice
// File: csv_practice.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>


void create_csv(const char * file)
{
	std::fstream fout;

	fout.open(file, std::ios::out | std::ios::app);
	
	fout.close();
}

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
	
	while (fin.good()) {

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

void update_record()
{
	// File pointer
	std::fstream fin, fout;

	// Open an existing record 
	fin.open("reportcard.csv", std::ios::in);

	// Create a new file to store updated data 
	fout.open("reportcardnew.csv", std::ios::out);

	int rollnum, roll, marks, count = 0, i;
	char sub;
	int index, new_marks;
	std::string line, word;
	std::vector<std::string> row;

	// Get the roll number from the user 
	std::cout << "Enter the roll number "
		  << "of the record to be updated: ";
	std::cin >> rollnum;

	// Get the data to be updated 
	std::cout << "Enter the subject "
		  << "to be updated(M/P/C/B): ";
	std::cin >> sub;

	// Determine the index of the subject where Maths has index 2,
	// Physics has index 3, and so on 
	if (sub == 'm' || sub == 'M')
		index = 2;
	else if (sub == 'p' || sub == 'P')
		index = 3;
	else if (sub == 'c' || sub == 'C')
		index = 4;
	else if (sub == 'b' || sub == 'B')
		index = 5;
	else {
		std::cout << "Wrong choice. Enter again\n";
		update_record();
	}

	// Get the new marks
	std::cout << "Enter new marks: ";
	std::cin >> new_marks;

	// Traverse the file 
	while (!fin.eof()) {
		
		row.clear();
		
		getline(fin, line);
		std::stringstream s(line);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		roll = std::stoi(row[0]);
		int row_size = row.size();

		if (roll == rollnum) {
			count = 1;
			std::stringstream convert;

			// sending a new number as a stream into output string 
			convert << new_marks;

			// the str() converts number into string 
			row[index] = convert.str();
			
			if (!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {

					// write the updated data 
					// into a new file 'reportcardnew.csv'
					// using fout 
					fout << row[i] << ",";
				}

				fout << row[row_size - 1] << "\n";
			}
		} else {
			if(!fin.eof()) {
				for (i = 0; i < row_size - 1; i++) {

					// writing other existing records 
					// into the new file using fout 
					fout << row[i] << ",";
				}

				// the last column data ends with a '\n'
				fout << row[row_size - 1] << "\n";
			}
		}
		if (fin.eof())
			break;
	}
	if (count == 0)
		std::cout << "Record not found\n";

	fin.close();
	fout.close();

	// remove the existing file 
	remove("reportcard.csv");
	
	// renaming the updated file with the existing file name 
	rename("reportcardnew.csv", "reportcard.csv");
}

void delete_record()
{
	// Open the file pointers
	std::fstream fin, fout;

	// Open the existing file 
	fin.open("reportcard.csv", std::ios::in);

	// Create a new file to store the non-deleted data 
	fout.open("reportcardnew.csv", std::ios::out);

	int rollnum, roll, marks, count = 0, i;
	char sub;
	int index, new_marks;
	std::string line, word;
	std::vector<std::string> row;

	// get the roll number to decide the data to be deleted 
	std::cout << "Enter the roll number "
		  << "of the record to be deleted: ";
	std::cin >> rollnum;

	// Check if this record exists 
	// If exists, leave it and 
	// add all other data to the new file 
	while (!fin.eof()) {

		row.clear();
		getline(fin, line);
		std::stringstream s(line);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		int row_size = row.size();
		roll = std::stoi(row[0]);

		// writing all records 
		// except the record to be deleted 
		// into the new file 'reportcardnew.csv'
		// using fout pointer 
		if (roll != rollnum) {
			if (!fin.eof()) {
				for (i=0; i<row_size-1; i++) {
					fout << row[i] << ",";
				}
				fout << row[row_size - 1] << "\n";
			}
		} else {
			count = 1;
		}
		if (fin.eof())
			break;
	}
	if (count == 1)
		std::cout << "Record deleted\n";
	else 
		std::cout << "Record not found\n";

	// Close the pointers 
	fin.close();
	fout.close();

	// removing the existing file
	remove("reportcard.csv");

	// renaming the new file with the existing file name 
	rename("reportcardnew.csv", "reportcard.csv");
}

int main(int argc, char * argv[])
{
	create_csv(argv[1]);
	// create();
	// read_record();
	// update_record();
	// delete_record();


	return 0;

}


