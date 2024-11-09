#include <fstream>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <vector>

int main()
{
	std::ifstream inputFile("C:\\Users\\schwarztoter\\source\\repos\\hashcracker\\build\\passwords.txt");

	std::vector<std::string> passwords;
	std::string buffer;

	if (!inputFile)
	{
		printf("Failed to open the input file");
		return 1;
	}

	while (std::getline(inputFile, buffer))
	{
		passwords.push_back(buffer);
	}

	inputFile.close();

	for (const auto& password : passwords)
	{
		std::cout << password << '\n';
	}

	return 1;
}