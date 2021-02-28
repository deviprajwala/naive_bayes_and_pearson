#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

float church_mean = 0, resort_mean = 0, beach_mean = 0, park_mean = 0, theatre_mean = 0, museum_mean = 0, mall_mean = 0, zoo_mean = 0, restaurant_mean = 0, pub_bar_mean = 0;

void read_record( string data_name, vector < vector<float> > &matrix ) 
//read the Data from the file as String Vector
{ 

    int idx = 0;
	// File pointer 
	fstream fin; 
 
	// Open an existing file 
	fin.open (data_name, ios::in); 
 
	string value, word, temp; 

	while (fin >> temp) 
    {
		// read an entire row and store it in a string variable 'line' 
		getline(fin, value); 
        const auto pos = value.find(',');
        if(pos != string::npos)
        value.erase(0, pos + 1);

		// used for breaking words 
		stringstream s(value); 
		// read every column data of a row and store it in a string variable, 'word' 
		
			// add all the column data of a row to a vector 
         // while (getline(s, word, ',') )
         //  {
          //  for(int i = 0; i < 4; i++)
          //  {
                for(int j = 0; j < 10; j++)
                {

                    if(getline(s, word, ','))
                    {
                        matrix[idx][j] = stof(word);
                    }
                }
                idx++;
          //  }
         //  }    
		} 
} 
void view_matrix(vector< vector <float> > matrix)
{
    for(int i=0; i<4;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<"\n";
    }

}
void calculation_of_mean(vector < vector <float> > matrix)
{
    for(int i = 0; i < matrix.size(); i++)
    {
        church_mean += matrix[i][0];
        resort_mean += matrix[i][1];
        beach_mean += matrix[i][2];
        park_mean += matrix[i][3];
        theatre_mean += matrix[i][4];
        museum_mean += matrix[i][5];
        mall_mean += matrix[i][6];
        zoo_mean += matrix[i][7];
        restaurant_mean += matrix[i][8];
        pub_bar_mean += matrix[i][9];
    }
    int n = matrix.size();
    church_mean /= n;
    resort_mean /= n;
    beach_mean /= n;
    park_mean /= n;
    theatre_mean /= n;
    museum_mean /= n;
    mall_mean /= n;
    zoo_mean /= n;
    restaurant_mean /= n;
    pub_bar_mean /= n;
}
int main()
{
    string s = "ratings.csv";
    //cin>>s;
    cout<<"hi";
    int rows = 4, cols = 10;
    vector <vector <float> > matrix (rows, vector<float>(cols));
    //cin>>rows>>cols;
    read_record(s,matrix);
    //view_matrix(matrix);
    calculation_of_mean(matrix);
    cout<< church_mean<<" "<<resort_mean<<" "<<beach_mean<<" "<<park_mean<<" "<<theatre_mean<<" "<<museum_mean<<" "<<mall_mean<<" "<<zoo_mean<<" "<<restaurant_mean<<" "<<pub_bar_mean;

    return 0;
}