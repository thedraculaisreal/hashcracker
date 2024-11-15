#include "cracker/cracker.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Usage: hashcracker.exe <HASH> <LIST>");
		return 1;
	}

	cracker.hash = argv[1]; // hash to crack
	cracker.list = argv[2]; // list location C:\\Users\\schwarztoter\\source\\repos\\hashcracker\\build\\passwords.txt
	cracker.reader();

	return 0;
}
