/*Implementation of the recommender system using the naive bayes algorithm*/

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

void read_record(string data_name) 
{ 

	// File pointer 
	fstream fin; 

	// Open an existing file 
	fin.open(data_name, ios::in); 
 

	// Read the Data from the file 
	// as String Vector 
	vector <string> row; 
	string line, word, temp; 

	while (fin >> temp) 
    { 

		row.clear(); 

		// read an entire row and 
		// store it in a string variable 'line' 
		getline(fin, line); 

		// used for breaking words 
		stringstream s(line); 

		// read every column data of a row and 
		// store it in a string variable, 'word' 
		while (getline(s, word, ',') )
        { 

			// add all the column data 
			// of a row to a vector 
			row.push_back(word); 
		} 

		cout << row[0];
    }
} 

int main()
{
    string s;// = "data.csv";
    cin>>s;
    read_record(s);

    return 0;
}