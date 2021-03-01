#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

void read_record( string data_name, vector < vector < float > > &matrix );
//read the Data from the file which is in csv format

void view_matrix( vector < vector < float > > matrix );
//function to view the matrix elements

void calculation_of_mean( vector < vector < float > > matrix );
//function to calculate the mean of each user

void similarity_measure( vector < vector < float > > matrix );
//function to calculate the pearson's similarity measure by making use of the mean values and the ratings of the user

void get_ratings_for_new_user();
//function to get the ratings of the user for whom the recommendation has to be made based on his previous ratings by comparing with the other users

void make_prediction( vector < vector < float > > matrix );
//function to make the prediction whether the user would like or dislike the 10th place based on the similarity measure

vector < float > mean;
//vector to store mean value of the users

vector < float > simili;
//vector to store the similarity measure between the users in the record and the new user

float new_user_mean;
//mean value of the new user

vector < float > new_user;
//vector to store the ratings given by the new user to the nine places

void read_record( string data_name, vector < vector < float > > &matrix ) 
//read the Data from the file as String Vector
{ 

    int idx = 0;
	// File pointer 
	fstream fin; 
 
	// Open an existing file 
	fin.open ( data_name, ios::in );
 
	string value, word, temp; 

	while ( fin >> temp ) 
    {
		// read an entire row and store it in a string variable 'line' and ignore the first entry 
		getline( fin, value ); 
        const auto pos = value.find(',');
        if( pos != string::npos )
        value.erase( 0, pos + 1 );

		// used for breaking words 
		stringstream s( value ); 
		// read every column data of a row and store it in a string variable, 'word' 
		
        for( int j = 0; j < 10; j++ )
        {
            if( getline( s, word, ',' ) )
            {
                matrix[idx][j] = stof(word);
                //to store the data in the matrix format
            }
        }
        idx++;    
	} 
} 
void view_matrix( vector< vector < float > > matrix )
//function to view the matrix elements
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<"\n";
    }

}
void calculation_of_mean( vector < vector < float > > matrix )
//function to calculate the mean of each user
{
    int n = matrix[0].size(), i, j;
    float val=0;
    for (i = 0; i < matrix.size(); i++)
    {
        for(j = 0; j < matrix[i].size(); j++)
        {
           val += matrix[i][j];
           //sum is calculated by adding all the ratings of the user
        }
            val /= n;
            //sum is divided by the number of ratings to obtain the mean
            mean.push_back(val);
            //the calculated value is pushed to the mean vector
            val = 0;
    }
}
void similarity_measure( vector < vector < float> > matrix )
//function to calculate the pearson's similarity measure by making use of the mean values and the ratings of the user
{
    int i, j;
    float val = 0, nomi = 0, denomi_1 = 0, denomi_2 = 0, denomi;
    for( i = 0; i < matrix.size(); i++)
    {
        for( j = 0; j < matrix[i].size() -1 ; j++)
        {
           nomi += ( matrix[i][j] - mean[i] ) * (new_user[j] - new_user_mean );
          // cout<<matrix[i][j]<<"-"<<mean[i]<<"*"<<new_user[j]<<"-"<<new_user_mean<<"=";
          // cout<<nomi<<"\n ";
           denomi_1 += ( matrix[i][j] - mean[i] ) * (matrix[i][j] - mean[i]) ;
          // cout<<matrix[i][j]<<"-"<<mean[i]<<"*"<<matrix[i][j]<<"-"<<mean[i]<<"="<<denomi_1<<"\n";
           denomi_2 += (new_user[j] - new_user_mean ) * (new_user[j] - new_user_mean );
          // cout<<new_user[j] <<"-"<< new_user_mean<< "*"<< new_user[j] <<"-"<< new_user_mean<<"="<<denomi_2<<"\n";
        //   cout<<denomi_1<<" "<<denomi_2<<"\n";

        }
        denomi = sqrt(denomi_1) * sqrt(denomi_2);
        if( denomi > 0 )
        //to avoid the arithmatic error
        {
        // cout<<denomi<<" "<<denomi_1<<" "<<denomi_2;
          val = nomi / denomi;
        }
        simili.push_back(val);
        //the calculated similarity measure is pushed into the vector simili
        val = 0;
        nomi = 0;
        denomi_1 = 0;
        denomi_2 = 0;
    }
}
void get_ratings_for_new_user()
//function to get the ratings of the user for whom the recommendation has to be made based on his previous ratings by comparing with the other users
{
    int sum = 0;
    float r;
   // cout<<"Enter the ratings for churches, resorts, beaches, parks, theatres, museums, malls, zoo, restaurants";
    for(int i = 0; i < 9; i++)
    {
        cin>>r;
        new_user.push_back(r);
        //the ratings of the new user is pushed into the vector new_user
        sum += r;
    }
    new_user_mean = sum/9.0;
    //mean value of the ratings is calculated for the user
}
void make_prediction( vector < vector <float> > matrix )
//function to make the prediction whether the user would like or dislike the 10th place based on the similarity measure
{
    int max = 0, index = 0;
    for(int i = 0; i < simili.size(); i++)
    {
      if(max <= simili[i])
      //searching for the user who most similar to the new user i.e maximum pearsons co effecient
      {
          max = simili[i];
          index = i;
      }
    }
    if( matrix[index][9] >= 2.5 )
    //if the rating of the 10th place is greater than or equal to 2.5 then the 10th place is recommended else it is not recommended
    {
        cout<<"dialog --msgbox \" Place 10 can be recommended to the user\" 10 30\n";
    }
    else
    {
        cout<<"dialog --msgbox \"User may not like the 10th place\" 10 30\n";
    }
}
int main()
{
    string s ;//= "ratings.csv";
    //cin>>s;
    int rows = 4, cols = 10;
   // cout<<"Enter the number of users and the number of places\n";
    //cin>>rows>>cols;
    vector <vector <float> > matrix ( rows, vector < float > ( cols ) );   

    read_record( s, matrix );
    //read the Data from the file which is in csv format

    //view_matrix( matrix );
    //function call to view the matrix elements

    calculation_of_mean( matrix );
    //function call to calculate the mean of each user

    get_ratings_for_new_user();
    //function call to get the ratings of the user for whom the recommendation has to be made based on his previous ratings by comparing with the other users

    similarity_measure( matrix );
    //function call to calculate the pearson's similarity measure by making use of the mean values and the ratings of the user

    make_prediction( matrix );
    //function call to make the prediction whether the user would like or dislike the 10th place based on the similarity measure

    return 0;
}
