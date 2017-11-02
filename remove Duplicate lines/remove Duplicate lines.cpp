// remove Duplicate lines.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>

std::string fixFileName(std::string &fileName) {
	
	std::string newFile;
	int len = fileName.length();
	std::string fileType = fileName.substr(len - 4);
	fileName.erase(len - 4);
	newFile = fileName + "_edited" + fileType;
	return newFile;

}

void removeSubstrs(std::string& s, std::string& p) {
	std::string::size_type n = p.length();
	for (std::string::size_type i = s.find(p);
		i != std::string::npos;
		i = s.find(p))
		s.erase(i, n+1);
}

int writeToFile(const std::string &writeLine) {

	std::ofstream file;

	file.open("c:\\Testing\\test_3.csv", std::ios::app);
	if (file.is_open()) {
		
		//std::cout << "Writeing File" << std::endl;
		file << writeLine << std::endl;
	}
	file.close();

	return 0;
}


int compareLines(const std::string &newLine) {
	
	//std::cout << "comapring lines" << std::endl;
	std::string oldLine;
	size_t pos = newLine.find('\t');
	//std::cout << pos << std::endl;
	//std::cout << newLine << std::endl;
	std::string compString = newLine.substr(pos);
	//std::cout << oldLine << std::endl;
	//std::cout << compString << std::endl;
	if (!oldLine.compare(compString))
	{
		//std::cout << "Lines Match, Skipping Line" << std::endl;
		
		return 1;
	}
	else {
		//std::cout << "Lines dos not match" << std::endl;
		oldLine = compString;
		writeToFile(newLine);
	}
	

	return 0;
}



int main(int argc, char* argv[])
{
	
    clock_t t;
	t = clock();
	std::ifstream fIn;
	std::ofstream file;
	std::string fileName, saveFileName;

	// Check the number of parameters
	if (argc < 2) {
		// Tell the user how to run the program
		std::cerr << "Usage: " << argv[0] << " File path and name" << std::endl;
		/* "Usage messages" are a conventional way of telling the user
		* how to run a program if they enter the command incorrectly.
		*/
		return 1;

	}

	//std::cout << "Please enter the input file name and path > " << std::flush;
	//getline(std::cin,fileName);
	// Check the number of parameters
	std::string current_exec_name = argv[0]; // Name of the current exec program
	std::vector<std::string> all_args;

	if (argc > 1) {

		fileName = argv[1];

		all_args.assign(argv + 1, argv + argc);
	}
	std::cout << argv[0];
	std::cout << " is trying to open: " << fileName << std::endl;
	fIn.open(fileName, std::ios::in);
	saveFileName = fixFileName(fileName);

	if (fIn.is_open())
	{
		std::string s;
		std::string oldLine;
		std::string pattern = "NaN";
		while (getline(fIn, s))
		{

			std::ofstream file;
			file.open(saveFileName, std::ios::app);
		    //	compareLines(s);
			size_t pos = s.find('\t');
			//std::cout << pos << std::endl;
			//std::cout << newLine << std::endl;
			std::string compString = s.substr(pos);
			if (oldLine.compare(compString))
			{
				oldLine = compString;
				removeSubstrs( s, pattern);
	
				if (file.is_open()) {
					file << s << std::endl;
				}
		   }
		}
		fIn.close();
		file.close();
	}
	else {
		std::cout << "Error opening file " << errno << " " << std::endl;
	}
	t = clock() - t;
	std::cout << "Minutes: " << (t*1.0 / CLOCKS_PER_SEC) / 60 << std::endl;
}
