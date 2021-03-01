#include<iostream>
#include<fstream>
using namespace std;

int n;

void create() 
{ 
	// file pointer 
	std::fstream fout; 

	// opens an existing csv file or creates a new file. 
	fout.open( "ratings.csv", ios::out | ios::app ); 

	cout << "Enter the ratings"
		<< " user_id, churches, resorts, beaches, parks, theatres, museums, malls, zoo, restaurants" << endl; 

	int i, user_id, churches, resorts, beaches, parks, theatres, museums, malls, zoo, restaurants; 
 
    cout << "Enter the number of users" ;
    cin >> n;

	// Read the input 
	for (i = 0; i < n; i++) 
    { 
		cin >> user_id
            >> churches
            >> resorts
            >> beaches
            >> parks
            >> theatres
            >> museums
            >> malls
            >> zoo
            >> restaurants;


		// Insert the data to file 
		fout <<user_id  << ", "
			<< churches << ", "
			<< resorts << ", "
			<< beaches << ", "
			<< parks << ", "
            << theatres << ", "
        	<< museums << ", "
    		<< malls << ", "
   			<< zoo << ", "
    		<< restaurants           
			<< "\n"; 
	} 
} 

int main()
{
    create();
    return 0;
}