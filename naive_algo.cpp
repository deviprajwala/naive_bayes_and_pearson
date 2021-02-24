/*Implementation of the recommender system using the naive bayes algorithm*/

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
float time_spent_mean_yes = 0, age_mean_yes = 0, income_mean_yes = 0, internet_usage_mean_yes = 0;
float time_spent_sd_yes = 0, age_sd_yes = 0, income_sd_yes = 0, internet_usage_sd_yes = 0;
float time_spent_pdf_yes = 0, age_pdf_yes = 0, income_pdf_yes = 0, internet_usage_pdf_yes = 0;

float time_spent_mean_no = 0, age_mean_no = 0, income_mean_no = 0, internet_usage_mean_no = 0;
float time_spent_sd_no = 0, age_sd_no = 0, income_sd_no = 0, internet_usage_sd_no = 0;
float time_spent_pdf_no = 0, age_pdf_no = 0, income_pdf_no = 0, internet_usage_pdf_no = 0;

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
    
	int n = sqrt(row.size () );
    time_spent_mean /= n;
    age_mean /= n;
    income_mean /= n;
    internet_usage_mean /= n;

	for(int i = 0; i < row.size(); i++)
	{
      time_spent_sd += ( stof (row[i]) - time_spent_mean)*( stof (row[i]) - time_spent_mean);
	  age_sd += ( stof (row[i+1]) - age_mean)*( stof (row[i+1]) - age_mean);
	  income_sd += ( stof (row[i+2]) - income_mean)*( stof (row[i+2]) - income_mean);
	  internet_usage_sd += ( stof (row[i+3]) - internet_usage_mean)*( stof (row[i+3]) - internet_usage_mean);
	  i+=4;
	}

	time_spent_sd = sqrt (time_spent_sd / n );
	age_sd = sqrt (age_sd / n );
	income_sd = sqrt (income_sd / n );
	internet_usage_sd = sqrt (internet_usage_sd / n );

}
void make_prediction(float time, float age, float income, float internet_usage)
{
	float val ;
	val = ( ( time - time_spent_mean ) * ( time - time_spent_mean ) ) / (2 * (time_spent_sd * time_spent_sd) );
	time_spent_pdf = (1 / (sqrt (2 * 3.1428) * time_spent_sd) ) * exp( -1*val);
    //cout<<val<<" "<<exp(-1* val)<<" "<<(1 /( sqrt (2 * 3.1428)  * time_spent_sd ));
	
	val = ( ( age - age_mean ) * ( age - age_mean ) ) / (2 * (age_sd * age_sd) );
	age_pdf = (1 / (sqrt (2 * 3.1428) * age_sd )) * exp( -1*val);
    
	
	val = ( ( income - income_mean ) * ( income - income_mean ) ) / (2 * (income_sd * income_sd) );
	income_pdf = (1 / (sqrt (2 * 3.1428) * income_sd)) * exp( -1*val);
  
    
	val = ( ( internet_usage - internet_usage_mean ) * ( internet_usage - internet_usage_mean ) ) / (2 * (internet_usage_sd * internet_usage_sd) );
	internet_usage_pdf = (1 / (sqrt (2 * 3.1428)) * internet_usage_sd ) * exp( -1*val);

}
int main()
{
    string s = "data.csv";
    //cin>>s;
    read_record(s);
   // calculation();
//	make_prediction(1,1,1,1);
	//cout<< time_spent_mean<<" "<<time_spent_sd<<" "<<time_spent_pdf;
   /// cout<< exp(-0.5);
    return 0;
}