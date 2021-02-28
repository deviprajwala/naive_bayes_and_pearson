#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

 vector < float > mean;
 vector < float > simili;
 float new_user_mean;
 vector < float > new_user;

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
    int n = matrix[0].size(), i, j;
    float val=0;
    for (i=0;i<matrix.size();i++)
    {
        for(j=0; j<matrix[i].size();j++)
        {
           val+= matrix[i][j];
        }
            val/=n;
            mean.push_back(val);
            val=0;
    }
}
void similarity_measure(vector< vector< float> > matrix)
{
    int i, j;
    float val=0, nomi=0, denomi_1=0, denomi_2 =0, denomi;
    for( i = 0; i < matrix.size(); i++)
    {
        for( j = 0; j < matrix[i].size() -1 ; j++)
        {
           nomi += ( matrix[i][j] - mean[i] ) * (new_user[j] - new_user_mean );
          // cout<<matrix[i][j]<<"-"<<mean[i]<<"*"<<new_user[j]<<"-"<<new_user_mean<<"=";
          // cout<<nomi<<"\n ";
           denomi_1 +=( matrix[i][j] - mean[i] ) * (matrix[i][j] - mean[i]) ;
          // cout<<matrix[i][j]<<"-"<<mean[i]<<"*"<<matrix[i][j]<<"-"<<mean[i]<<"="<<denomi_1<<"\n";
           denomi_2 +=(new_user[j] - new_user_mean ) * (new_user[j] - new_user_mean );
          // cout<<new_user[j] <<"-"<< new_user_mean<< "*"<< new_user[j] <<"-"<< new_user_mean<<"="<<denomi_2<<"\n";
        //   cout<<denomi_1<<" "<<denomi_2<<"\n";

        }
        denomi = sqrt(denomi_1) * sqrt(denomi_2);
        if( denomi > 0 )
        {
        // cout<<denomi<<" "<<denomi_1<<" "<<denomi_2;
          val = nomi / denomi;
        }
        simili.push_back(val);
        val=0;
        nomi=0;
        denomi_1=0;
        denomi_2 =0;
    }
   /* for(int i=0;i<simili.size();i++)
    {
        cout<<simili[i]<<" ";
    }*/
}
void get_ratings_for_new_user()
{
    int sum=0;
    float r;
    cout<<"enter the ratings for churches,resorts,beaches,parks, theatres, museums, malls,zoo,restaurants";
    for(int i=0;i<9;i++)
    {
        cin>>r;
        new_user.push_back(r);
        sum+= r;
    }
    new_user_mean = sum/9.0;
}
void make_prediction( vector < vector <float> > matrix)
{
    int max=0, index=0;
    cout<<"hi";

    for(int i=0;i<simili.size();i++)
    {
      if(max <= simili[i])
      {
          max= simili[i];
          index= i;
      }
    }
    if( matrix[index][9] >= 2.5 )
    {
        cout<<" Place 10 can be recommended to the user\n";
    }
    else
    {
        cout<<"User may not like the 10th place\n";
    }
}
int main()
{
    string s = "ratings.csv";
    //cin>>s;
    int rows = 4, cols = 10;
    vector <vector <float> > matrix (rows, vector<float>(cols));
   
    //cin>>rows>>cols;
    read_record(s,matrix);
    view_matrix(matrix);
    calculation_of_mean(matrix);
   /* for(int i=0;i<mean.size();i++)
    {
        cout<<mean.at(i)<<" ";
    }*/
    get_ratings_for_new_user();
    similarity_measure(matrix);
    make_prediction( matrix) ;
    return 0;
}