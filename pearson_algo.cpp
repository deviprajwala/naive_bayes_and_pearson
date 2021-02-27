#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

//vector <string> row;

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
                        cout<<idx<<" "<<j<<"    ";
                    }
                }
                cout<<"\n";
                idx++;
          //  }
         //  }    
		} 
    
    
   /* int ind = 1;
    for(int i=0;i<row.size();i++)
    {
        
        if(stoi(row[i]) == ind)
        {
            for( int j = 1; j <= 10; j++)
            {
                cout<<"hi";
                matrix[i].push_back( stof(row[j]) );
                cout<<i;
            }
        }
    }*/

    //cout<<row.size();*/
} 

int main()
{
    string s = "ratings.csv";
    //cin>>s;
    int rows = 4, cols = 10;
    vector <vector <float> > matrix (rows, vector<float>(cols));
    //cin>>rows>>cols;
    read_record(s,matrix);

    for(int i=0; i<4;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}