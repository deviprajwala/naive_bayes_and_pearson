/*Implementation of the recommender system using the naive bayes algorithm*/
/*The below program helps us to predict whether the user clicks on the ad or not given the time spent in the web page, his age, his income and his internet usage*/

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

void read_record( string data_name );
//function to read the comma seperated values from a csv file;

void calculation( vector <float> rows, float &time_spent_mean, float &age_mean, float &income_mean, float &internet_usage_mean, float &time_spent_sd, float &age_sd, float &income_sd, float &internet_usage_sd );
//function to calculate the mean and standard deviation for the available set of inputs

float make_prediction(float time, float age, float income, float internet_usage, float time_spent_mean, float age_mean, float income_mean, float internet_usage_mean, float time_spent_sd, float age_sd, float income_sd, float internet_usage_sd);
//function to calculate the probability for each class using the gaussian probability density function 

void splitting_classes();
//function to split the data in accordance with thier classes


float time_spent_mean_yes = 0, age_mean_yes = 0, income_mean_yes = 0, internet_usage_mean_yes = 0;
//to store the mean value of each attribute belonging to class yes

float time_spent_sd_yes = 0, age_sd_yes = 0, income_sd_yes = 0, internet_usage_sd_yes = 0;
//to store the standard deviation value of each attribute belonging to class yes

float time_spent_pdf = 0, age_pdf = 0, income_pdf = 0, internet_usage_pdf = 0;
//to store the probaility density function value of each attribute belonging to class yes

float time_spent_mean_no = 0, age_mean_no = 0, income_mean_no = 0, internet_usage_mean_no = 0;
//to store the mean value of each attribute belonging to class no

float time_spent_sd_no = 0, age_sd_no = 0, income_sd_no = 0, internet_usage_sd_no = 0;
//to store the standard deviation value of each attribute belonging to class yes

 
vector <string> row;
//to read the input from a file as string

vector <float> row_yes;
//to store the values of the attribute belonging to class yes

vector <float> row_no; 
//to strore the values of the attribute belonging to class no

void read_record( string data_name ) 
//read the Data from the file as String Vector
{ 

	// File pointer 
	fstream fin; 

	// Open an existing file 
	fin.open (data_name, ios::in); 
 
	string line, word, temp; 

	while (fin >> temp) 
    {
		// read an entire row and store it in a string variable 'line' 
		getline(fin, line); 

		// used for breaking words 
		stringstream s(line); 

		// read every column data of a row and store it in a string variable, 'word' 
		while (getline(s, word, ',') )
        { 
			// add all the column data of a row to a vector 
			row.push_back(word); 
		} 
    }
} 

void calculation(vector <float> rows, float &time_spent_mean, float &age_mean, float &income_mean, float &internet_usage_mean, float &time_spent_sd, float &age_sd, float &income_sd, float &internet_usage_sd )
{
    for(int i=0;i<rows.size();i++)
	//calculate the sum of each of the attributes
    {
        time_spent_mean += rows[i];
        age_mean += rows[i+1];
        income_mean += rows[i+2];
        internet_usage_mean += rows[i+3];
        i+=3;
    }
   
    //clculate the mean for each of the attributes
	//mean = sum of the attribute values divided by the total number of attributes
	int n = rows.size ()/4;
    time_spent_mean /= n;
    age_mean /= n;
    income_mean /= n;
    internet_usage_mean /= n;

    
	for(int i = 0; i < rows.size(); i++)
	//calculate the variance for each of the attribute
	{
      time_spent_sd += ( rows[i] - time_spent_mean)*( rows[i] - time_spent_mean);
	  age_sd += ( rows[i+1] - age_mean)*( rows[i+1] - age_mean);
	  income_sd += ( rows[i+2] - income_mean)*( rows[i+2] - income_mean);
	  internet_usage_sd += ( rows[i+3] - internet_usage_mean)*( rows[i+3] - internet_usage_mean);
	  i+=3;
	}

    //calculate the standard deviation for each of the attribute
	//the stadard deviation is the square root of the variance
	time_spent_sd = sqrt (time_spent_sd / n );
	age_sd = sqrt (age_sd / n );
	income_sd = sqrt (income_sd / n );
	internet_usage_sd = sqrt (internet_usage_sd / n );

}

float make_prediction(float time, float age, float income, float internet_usage, float time_spent_mean,float age_mean, float income_mean, float internet_usage_mean, float time_spent_sd, float age_sd,  float income_sd, float internet_usage_sd)
{
	//the pdf(probability density function ) is calculated using the gaussian probability for the continous variables which helps in making the pediction whether the user would click o the add or not
	
	float val, res;
	val = ( ( time - time_spent_mean ) * ( time - time_spent_mean ) ) / (2 * (time_spent_sd * time_spent_sd) );
	time_spent_pdf = (1 / (sqrt (2 * 3.1428) * time_spent_sd) ) * exp( -1*val);
    
	
	val = ( ( age - age_mean ) * ( age - age_mean ) ) / (2 * (age_sd * age_sd) );
	age_pdf = (1 / (sqrt (2 * 3.1428) * age_sd )) * exp( -1*val);
    
	
	val = ( ( income - income_mean ) * ( income - income_mean ) ) / (2 * (income_sd * income_sd) );
	income_pdf = (1 / (sqrt (2 * 3.1428) * income_sd)) * exp( -1*val);
  
    
	val = ( ( internet_usage - internet_usage_mean ) * ( internet_usage - internet_usage_mean ) ) / (2 * (internet_usage_sd * internet_usage_sd) );
	internet_usage_pdf = (1 / (sqrt (2 * 3.1428)) * internet_usage_sd ) * exp( -1*val);

    res = time_spent_pdf * age_pdf * income_pdf * internet_usage_pdf;

	return res;

}

void splitting_classes()
//function to split the data in accordance with thier classes
{
    for(int i = 4 ;i < row.size() ;i += 5)
	//4 since the number of attributes is 4
   {
	   int j, ind = i;
	   if( stoi (row[i]) == 1 )
	   //if the class is yes push the values into the vector row_yes 
	   {
		   for(j = 4; j >= 1; j--)
		   {
             row_yes.push_back( stof (row[ind-j]) );
			 //push all the four values of attribute by converting them into float
		   }
	   }
	   else if( stoi (row[i]) == 0 )
	   //if the class is no push the values into the vector row_no
	   {
		   for(j = 4; j >= 1; j--)
		   {
             row_no.push_back( stof (row[ind-j]) );
			 //push all the four values of attribute by converting them into float
		   }
	   }   
   }
}

int main()
{
    string s;// = "data.csv";
	cin>>s;
	//to get the name of the input file
    float yes, no;
    float user_time, user_age, user_income, user_internet_usage;
	cin>>user_time>>user_age>>user_income>>user_internet_usage;
	//to get the values of the attributes for which the perdiction has to be made

    read_record(s);
	//function to read the comma seperated values from a csv file;

	splitting_classes();
	//function to split the data in accordance with thier classes

    calculation(row_yes, time_spent_mean_yes, age_mean_yes, income_mean_yes, internet_usage_mean_yes, time_spent_sd_yes, age_sd_yes,income_sd_yes, internet_usage_sd_yes);
	calculation(row_no, time_spent_mean_no, age_mean_no, income_mean_no, internet_usage_mean_no, time_spent_sd_no, age_sd_no,income_sd_no, internet_usage_sd_no);
	//function to calculate the mean and standard deviation for the available set of inputs

	yes = make_prediction(user_time, user_age, user_income, user_internet_usage, time_spent_mean_yes, age_mean_yes, income_mean_yes, internet_usage_mean_yes, time_spent_sd_yes, age_sd_yes,income_sd_yes, internet_usage_sd_yes);
	no = make_prediction(user_time, user_age, user_income, user_internet_usage, time_spent_mean_no,age_mean_no,income_mean_no,internet_usage_mean_no,time_spent_sd_no,age_sd_no,income_sd_no,internet_usage_sd_no);
	//function to calculate the probability for each class using the gaussian probability density function 

  //cout<< time_spent_mean_yes<<" "<< age_mean_yes<<" "<< income_mean_yes<<" "<< internet_usage_mean_yes<<" "<< time_spent_sd_yes<<" "<< age_sd_yes<<" "<<income_sd_yes<<" "<< internet_usage_sd_yes<<"\n";
  //cout<<time_spent_mean_no<<" "<< age_mean_no<<" "<< income_mean_no<<" "<< internet_usage_mean_no<<" "<< time_spent_sd_no<<" "<< age_sd_no<<" "<<income_sd_no<<" "<< internet_usage_sd_no;

   if( yes > no )
   //if the probability of class yes is greater than the class no print yes or else print no
   {
	   cout<<"dialog --msgbox \"YES there is high chance of user clicking on th advertise\" 10 30";
   }
   else
   {
	   cout<<"dialog --msgbox \"NO there is low chance of user clicking on th advertise\" 10 30";
   }

   return 0;
}