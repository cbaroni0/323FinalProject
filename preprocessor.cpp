//
//  main.cpp
//  FinalProject
//
//  Created by Long Nguyen on 5/3/19.
//  Copyright © 2019 Long Nguyen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{

	ifstream inFile("final.txt");
	ofstream outFile("finalOut.txt");
	string line;

	if (inFile.is_open() && outFile.is_open())
	{
		//read file into stringstream
		stringstream ss;
		ss << inFile.rdbuf();
		inFile.close();
		string temp = ss.str();
		//delete all comment sections
		int start;
		bool comment = false;
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] == '(' && temp[i + 1] == '*')
			{
				start = i;
				comment = true;
			}
			if (comment && temp[i] == ')' && temp[i - 1] == '*')
			{
				temp.erase(temp.begin() + start, temp.begin() + i + 1);
				comment = false;
				i = start;
			}
		}
		
		ss.str(temp);
		//WHILE - delete spacings
		while (getline(ss, line))
		{
			//WHILE - turns multiple spaces into a single space
			int i = 0, j = 0, count;
			while (i < line.length())
			{
				if (line[i] == ' ' && line[i+1] == ' ')
				{
					j = i+1;
					count = 0;
					while (line[j] == ' ')
					{
						j++;
						count++;
					}
					line.erase(i+1, count);

				}
				i++;
			}//end WHILE - multiple spaces into one
			//WHILE - remove all first tab space or regular space
			while (line[0] == '\t' || line[0] == ' ')	
				line.erase(line.begin());

			//FOR - fix spacing for , = + * - : ;
			bool insideQuote = false;
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == '\'' || line[i] == '\"')
					insideQuote = !insideQuote;
				//space after not before ,
				if (line[i] == ',' && !insideQuote)
				{
					if (line[i + 1] != ' ')
						line.insert(i + 1, " ");
					if (line[i - 1] == ' ')
					{
						line.erase(line.begin() + i - 1);
						i--;
					}
				}
				//space both before and after * = : 
				else if ((line[i] == '*' || line[i] == '=' || line[i] == ':') && !insideQuote)
				{
					if (line[i + 1] != ' ')
						line.insert(i + 1, " ");
					if (line[i - 1] != ' ')
					{
						line.insert(i, " ");
						i++;
					}
				}
				//no spaces before or after ;
				else if (line[i] == ';' && !insideQuote)
				{
					if (line[i + 1] == ' ')
						line.erase(line.begin() + i + 1);
					if (line[i - 1] == ' ')
					{
						line.erase(line.begin() + i - 1);
						i--;
					}
				}
			}//end FOR - fix spacing for, = +*-:;
			//OUT - outputs line and writes line to file
			if (line != "" && line != "\n")			//does not output for blank lines
			{
				cout << line << endl;
				outFile << line;
				if (line != "END.")
					outFile << endl;
			}

		}
	}
	else cout << "Unable to open file";

	outFile.close();

	return 0;
}
