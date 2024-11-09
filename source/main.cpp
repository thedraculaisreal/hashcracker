#include <fstream>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <vector>

int main()
{
	std::ifstream inputFile("C:\\Users\\schwarztoter\\source\\repos\\hashcracker\\build\\passwords.txt"); // location of password list.

	std::vector<std::string> passwords; // vector of strings to store password list in.
	std::string buffer;

	if (!inputFile)
	{
		printf("Failed to open the input file\n");
		return 1;
	}

	while (std::getline(inputFile, buffer)) // gets each line within password list and stores them into the passwords.
	{
		passwords.push_back(buffer);
	}

	inputFile.close(); // closes input file, becasue we dont need it anymore.

	for (const auto& password : passwords) // loops through vector printing out all passwords allocated to it.
	{
		std::cout << password << '\n';
	}

	return 0;
}