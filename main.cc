
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tclap/CmdLine.h>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace TCLAP;

int main(int argc, char* argv[])
{
	try
	{
		enum myFiles {INFILE, OUTFILE, TOUPPER, TOLOWER};
		//The CmdLine class manages the parsing
		CmdLine cmd("CS3376.502 Program 2",' ',"1.0"); 	   
		
		//ValueArg for the output file argument
		ValueArg<string> outfileArg("o","outfile","The output file name.",false,"output.txt","output filename"); 
		cmd.add(outfileArg);

		//Required UnlabeledValueArg for the input file argument
		UnlabeledValueArg<string> infileArg("input","The input file name.",true,"input.txt","input file name",false);
		cmd.add(infileArg);
		
		//SwitchArgs that parses arguments responsible for changing the letter case in textfiles
		SwitchArg lowerSwitch("l","lower","Convert all text to lowercase.",cmd,false);
		SwitchArg upperSwitch("u","upper","Convert all text to uppercase.",cmd,false);

		//Parse the argv array
		cmd.parse(argc, argv);

		//Assign the value of all Args to basic variables
		bool up = upperSwitch.getValue();
		bool low = lowerSwitch.getValue();
		string in = infileArg.getValue();
		string out = outfileArg.getValue();
		
		//Assign the variables to an option map
		map<int, string> optionMap;
		optionMap[INFILE] = in;
		optionMap[OUTFILE] = out;
		map<int, bool> optionMap2;
     		optionMap2[TOUPPER] = up;
		optionMap2[TOLOWER] = low;

		//Perform operations on reading input files and writing to output files based on the conditions of the upper/lower case commands
		if(optionMap2[TOLOWER] && optionMap2[TOUPPER])
		{
			cout << "-u and -l are mutually exclusive." << endl;
			return 1;
		}
		else if(optionMap2[TOUPPER])
		{
			string line;
			ifstream inFile;
			inFile.open(optionMap[INFILE].c_str());
			if(inFile.is_open())
			{
		 		ofstream outFile;
				outFile.open(optionMap[OUTFILE].c_str());
				while(!inFile.eof())
				{
					getline(inFile, line);
					for(int i = 0; i < line.size(); i++)
					{
						line[i] = toupper(line[i]);
					}
					outFile << line << endl;
				}
				inFile.close();
				outFile.close();
			}
			else cout << "Unable to open file" << endl;
		}
		else if(optionMap2[TOLOWER])
		{
			string line;
			ifstream inFile;
			inFile.open(optionMap[INFILE].c_str());
			if(inFile.is_open())
			{
				ofstream outFile;
				outFile.open(optionMap[OUTFILE].c_str());
				while(!inFile.eof())
				{
					getline(inFile, line);
					for(int i = 0; i < line.size(); i++)
					{
						line[i] = tolower(line[i]);
					}
					outFile << line << endl;
				}
				inFile.close();
				outFile.close();
			}
			else cout << "Unable to open file" << endl;
		}

		//outputs the values of the parsed command  line arguments
		cout << "The value of the parsed command line argument for the input file is: " << optionMap[INFILE] << endl;
		cout << "The value of the parsed command line argument for the output file is: " << optionMap[OUTFILE] << endl;
	}
	catch (ArgException &e)
	{
		cerr << "Error: " << e.error() << " for arg " << e.argId() << endl;
	}
		
	return 0;
}
