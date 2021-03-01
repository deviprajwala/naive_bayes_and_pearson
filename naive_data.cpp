#include<iostream>
#include<fstream>
using namespace std;

void create() 
{ 
	// file pointer 
	std::fstream fout; 

	// opens an existing csv file or creates a new file. 
	fout.open("data.csv", ios::out | ios::app); 

	cout << "Enter the data"
		<< " sl no time spent age income internet usage clicked on add" << endl; 

	int i, time_spent, age, income, internet_usage, clicked_on_add;  

	// Read the input 
	int n;
	cout<<"Enter the number of users :";
	cin>>n;
	for (i = 0; i < n; i++) { 

		cin >> time_spent
			>> age
			>> income
			>> internet_usage
			>> clicked_on_add; 

		// Insert the data to file 
		fout << time_spent << ", "
			<< age << ", "
			<< income << ", "
			<< internet_usage << ", "
			<< clicked_on_add
			<< "\n"; 
	} 
} 

int main()
{
    create();
    return 0;
}