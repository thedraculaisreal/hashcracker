#include "cracker.h"

std::string sha256(const std::string& str);

void crackPassword(std::vector<std::string> list, std::string_view hash)
{
	for (const auto& password : list) // loops through vector printing out all passwords allocated to it.
	{
		if (hash.compare(sha256(password)) == 0)
		{
			printf("Password cracked: %s\n", password.c_str());
			cracker.running = false;
			break;
		}
	}
}

void Cracker::reader()
{
	// location of password list.
	std::ifstream inputFile(cracker.list);

	std::string buffer;

	if (!inputFile)
	{
		printf("Failed to open the input file\n");
		return;
	}

	int black{ 0 };

	// gets each line within password list and stores them into the passwords.
	while (std::getline(inputFile, buffer)) 
	{
		if (black == 0)
		{
			passwords.push_back(buffer);
			black++;
		}
		else if (black == 1)
		{
			passwords1.push_back(buffer);
			black++;
		}
		else if (black == 2)
		{
			passwords2.push_back(buffer);
			black++;
		}
		else
		{
			black = 0;
		}
	}

	// closes input file, becasue we dont need it anymore.
	inputFile.close(); 
	
	start_threads();
}

void Cracker::start_threads()
{
	printf("Cracking password...\n");

	std::thread crack1(crackPassword, passwords, hash);
	std::thread crack2(crackPassword, passwords1, hash);
	std::thread crack3(crackPassword, passwords2, hash);

	crack1.detach();
	crack2.detach();
	crack3.detach();

	int time = 0;
	running = true;

	while (running)
	{
		if ((time % 5) == 0)
		{
			std::cout << "Time elapsed: " << time << "seconds" << '\n';
		}
		Sleep(1000);
		time++;
	}

	printf("Time to crack: %dseconds", time);
}

std::string sha256(const std::string& str)
{
	unsigned char hash[EVP_MAX_MD_SIZE]; // buffer to hold hash.
	unsigned int hashLength{ 0 };

	std::stringstream ss;

	EVP_MD_CTX* context{ EVP_MD_CTX_new() }; // create context.
	if (!context)
	{
		return ""; // empty stirng.	
	}

	EVP_DigestInit_ex(context, EVP_sha256(), nullptr); // intializes hashing, using SHA256.
	EVP_DigestUpdate(context, str.c_str(), str.size()); // processes string.
	EVP_DigestFinal_ex(context, hash, &hashLength); // hashes str and stores it into hash buffer.

	for (unsigned int i = 0; i < hashLength; i++)
	{
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)(hash[i]); // converts hash to hexadecimal.
	}

	EVP_MD_CTX_free(context); // free context / cleanup.

	return ss.str();
}