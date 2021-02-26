/*Implementation of the recommender system using the naive bayes algorithm*/

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
void read_record(string data_name);
void calculation(vector<float>rows, float &time_spent_mean,float &age_mean, float &income_mean, float &internet_usage_mean,float &time_spent_sd, float &age_sd, float &income_sd, float &internet_usage_sd );
float make_prediction(float time, float age, float income, float internet_usage, float time_spent_mean,float age_mean, float income_mean, float internet_usage_mean,float time_spent_sd,float age_sd,float income_sd, float internet_usage_sd);
void splitting_classes();


float time_spent_mean_yes = 0, age_mean_yes = 0, income_mean_yes = 0, internet_usage_mean_yes = 0;
float time_spent_sd_yes = 0, age_sd_yes = 0, income_sd_yes = 0, internet_usage_sd_yes = 0;
float time_spent_pdf = 0, age_pdf = 0, income_pdf = 0, internet_usage_pdf = 0;
float time_spent_mean_no = 0, age_mean_no = 0, income_mean_no = 0, internet_usage_mean_no = 0;
float time_spent_sd_no = 0, age_sd_no = 0, income_sd_no = 0, internet_usage_sd_no = 0;


 
vector <string> row;
vector <float> row_yes;
vector <float> row_no; 

void read_record(string data_name) 
   // Read the Data from the file 
	// as String Vector
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

void calculation(vector<float>rows, float &time_spent_mean,float &age_mean, float &income_mean, float &internet_usage_mean,float &time_spent_sd, float &age_sd, float &income_sd, float &internet_usage_sd )
{
    for(int i=0;i<rows.size();i++)
    {
        time_spent_mean += rows[i];
	//	cout<<rows[i]<<" ";
        age_mean += rows[i+1];
        income_mean += rows[i+2];
        internet_usage_mean += rows[i+3];
        i+=3;
    }
   
	int n = rows.size ()/4;
    time_spent_mean /= n;
    age_mean /= n;
    income_mean /= n;
    internet_usage_mean /= n;

    
	for(int i = 0; i < rows.size(); i++)
	{
      time_spent_sd += ( rows[i] - time_spent_mean)*( rows[i] - time_spent_mean);
	  age_sd += ( rows[i+1] - age_mean)*( rows[i+1] - age_mean);
	  income_sd += ( rows[i+2] - income_mean)*( rows[i+2] - income_mean);
	  internet_usage_sd += ( rows[i+3] - internet_usage_mean)*( rows[i+3] - internet_usage_mean);
	  i+=3;
	}

	time_spent_sd = sqrt (time_spent_sd / n );
	age_sd = sqrt (age_sd / n );
	income_sd = sqrt (income_sd / n );
	internet_usage_sd = sqrt (internet_usage_sd / n );

}
float make_prediction(float time, float age, float income, float internet_usage, float time_spent_mean,float age_mean, float income_mean, float internet_usage_mean,float time_spent_sd,float age_sd,float income_sd, float internet_usage_sd)
{
	float val, res;
	val = ( ( time - time_spent_mean ) * ( time - time_spent_mean ) ) / (2 * (time_spent_sd * time_spent_sd) );
	time_spent_pdf = (1 / (sqrt (2 * 3.1428) * time_spent_sd) ) * exp( -1*val);
    //cout<<val<<" "<<exp(-1* val)<<" "<<(1 /( sqrt (2 * 3.1428)  * time_spent_sd ));
	
	val = ( ( age - age_mean ) * ( age - age_mean ) ) / (2 * (age_sd * age_sd) );
	age_pdf = (1 / (sqrt (2 * 3.1428) * age_sd )) * exp( -1*val);
    
	
	val = ( ( income - income_mean ) * ( income - income_mean ) ) / (2 * (income_sd * income_sd) );
	income_pdf = (1 / (sqrt (2 * 3.1428) * income_sd)) * exp( -1*val);
  
    
	val = ( ( internet_usage - internet_usage_mean ) * ( internet_usage - internet_usage_mean ) ) / (2 * (internet_usage_sd * internet_usage_sd) );
	internet_usage_pdf = (1 / (sqrt (2 * 3.1428)) * internet_usage_sd ) * exp( -1*val);

    res = time_spent_pdf * age_pdf * income_pdf * internet_usage_pdf;
//	cout<<res;
	return res;

}

void splitting_classes()
{
    for(int i=4 ;i<row.size();i+=5)
   {
	   int j,ind=i;
	   if(stoi(row[i]) == 1)
	   {
		   for(j=4;j>=1;j--)
		   {
             row_yes.push_back( stof (row[ind-j]) );
			 //cout<<ind-j<< " ";
			 //cout<<row_yes[ind-j]<<" ";
		   }
		   //cout<<"\n";
		  // cout<<row_yes[i-j]<<" ";
	   }
	   else if(stoi(row[i]) == 0)
	   {
		     for(j=4;j>=1;j--)
		   {
             row_no.push_back( stof (row[ind-j]) );
			 //cout<<ind-j<< " ";
			 //cout<<row_yes[ind-j]<<" ";
		   }
	   }
	   
   }
   for(int i=0;i<row_yes.size();i++)
  {
	 // cout<<row_yes[i]<<"  ";
  }
}
int main()
{
    string s = "data.csv";
    float yes, no;
    read_record(s);
	splitting_classes();
    calculation(row_yes, time_spent_mean_yes, age_mean_yes, income_mean_yes, internet_usage_mean_yes, time_spent_sd_yes, age_sd_yes,income_sd_yes, internet_usage_sd_yes);
    calculation(row_no, time_spent_mean_no, age_mean_no, income_mean_no, internet_usage_mean_no, time_spent_sd_no, age_sd_no,income_sd_no, internet_usage_sd_no);
	yes = make_prediction(2,23,10000,30, time_spent_mean_yes, age_mean_yes, income_mean_yes, internet_usage_mean_yes, time_spent_sd_yes, age_sd_yes,income_sd_yes, internet_usage_sd_yes);
	no = make_prediction(2,23,10000,30,time_spent_mean_no,age_mean_no,income_mean_no,internet_usage_mean_no,time_spent_sd_no,age_sd_no,income_sd_no,internet_usage_sd_no);
	//cout<< time_spent_mean<<" "<<time_spent_sd<<" "<<time_spent_pdf;
   /// cout<< exp(-0.5);
 // cout<< time_spent_mean_yes<<" "<< age_mean_yes<<" "<< income_mean_yes<<" "<< internet_usage_mean_yes<<" "<< time_spent_sd_yes<<" "<< age_sd_yes<<" "<<income_sd_yes<<" "<< internet_usage_sd_yes<<"\n";
  //cout<<time_spent_mean_no<<" "<< age_mean_no<<" "<< income_mean_no<<" "<< internet_usage_mean_no<<" "<< time_spent_sd_no<<" "<< age_sd_no<<" "<<income_sd_no<<" "<< internet_usage_sd_no;
 // cout<<"\n";

   if(yes>no)
   {
	   cout<<"yes";
   }
   else
   {
	   cout<<"no";
   }

   return 0;
}