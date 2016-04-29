#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

double youGet, outOf, weight;
double currentYourWeight;
double currentTotalWeight;

void printGrade(string filename)
{
	string line;
	filename = filename + ".txt";
	ifstream myfile (filename);
	if (myfile.is_open())
	{
		getline (myfile,line);
		cout << line << endl;
		string which;
		
		while(myfile >> which >> youGet >> outOf >> weight)
		{
			cout << setw(7);
			cout << which << ":" << setw(5) << youGet << "/" << outOf << "=" << youGet/outOf*100 << "%" << endl;
			currentYourWeight += youGet / outOf * weight;
			currentTotalWeight += weight;
		}
		cout << "Your Mark for" << filename << "is: " << currentYourWeight << "/" << currentTotalWeight << "=" << currentYourWeight/currentTotalWeight*100 << "%" << endl;
		myfile.close();
		cout << endl;

		currentYourWeight = 0;
		currentTotalWeight = 0;
	}
}

int main()
{
	string line;
	printGrade("math239");
	printGrade("cs240");
	printGrade("cs241");
	printGrade("econ102");
	printGrade("mcsi211");
	
	return 0;
}