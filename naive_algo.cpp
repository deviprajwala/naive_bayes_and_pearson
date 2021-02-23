/*Implementation of the recommender system using the naive bayes algorithm*/

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
float time_spent_mean=0, age_mean = 0, income_mean = 0, internet_usage_mean = 0;
// Read the Data from the file 
	// as String Vector 
	vector <string> row; 
void read_record(string data_name) 
{ 

	// File pointer 
	fstream fin; 

	// Open an existing file 
	fin.open(data_name, ios::in); 
 

	
	string line, word, temp; 

	while (fin >> temp) 
    { 

		//row.clear(); 

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
    }
} 

void calculation()
{
    for(int i=0;i<row.size();i++)
    {
        time_spent_mean += stof(row[i]);
        age_mean += stof(row[i+1]);
        income_mean += stof(row[i+2]);
        internet_usage_mean += stof(row[i+3]);
        i+=4;
    }
    
    time_spent_mean /= sqrt(row.size());
    age_mean /= sqrt(row.size());
    income_mean /= sqrt(row.size());
    internet_usage_mean /= sqrt(row.size());

}
int main()
{
    string s = "data.csv";
    //cin>>s;
    read_record(s);
    calculation();
    return 0;
}