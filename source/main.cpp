#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <iomanip>
#include <openssl/sha.h> // vcpkg install openssl,, vcpkg integrate install // libssl.lib libcrypto.lib
#include <openssl/evp.h>
#include <thread>

std::string sha256(const std::string& str);
void crackPassword(std::vector<std::string> list, std::string_view hash);
bool running{ false };

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Usage: hashcracker.exe <HASH> <LIST>");
		return 1;
	}

	std::string hash{ argv[1]}; // hash to crack
	const char* list{ argv[2]}; // list location C:\\Users\\schwarztoter\\source\\repos\\hashcracker\\build\\passwords.txt

	std::ifstream inputFile(list); // location of password list.

	std::vector<std::string> passwords; // vector of strings to store password list in.
	std::vector<std::string> passwords1;
	std::vector<std::string> passwords2;
	std::string buffer;

	if (!inputFile)
	{
		printf("Failed to open the input file\n");
		return 1;
	}

	int black{ 0 };

	while (std::getline(inputFile, buffer)) // gets each line within password list and stores them into the passwords.
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

	//size_t middle = passwords.size() / 2;

	/*std::vector<std::string> passwords1(passwords.begin(), passwords.begin() + middle);
	std::vector<std::string> passwords2(passwords.begin() + middle, passwords.end());
	memset(&passwords, 0, sizeof(passwords));*/

	inputFile.close(); // closes input file, becasue we dont need it anymore.

	printf("Cracking password...\n");

	std::thread crack1(crackPassword, passwords , hash);
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

	return 0;
}

void crackPassword(std::vector<std::string> list, std::string_view hash)
{
	for (const auto& password : list) // loops through vector printing out all passwords allocated to it.
	{
		if (hash.compare(sha256(password)) == 0)
		{
			printf("Password cracked: %s\n", password.c_str());
			running = false;
			break;
		}
	}
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

// This is a depracted version of sha256 hasing in c++
/*std::string sha256(const std::string& str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH]; // uses standard sha256 hash length.

	SHA256_CTX sha256; // defining sha256 structure.
	SHA256_Init(&sha256); // initializes sha256 context for hashing.
	SHA256_Update(&sha256, str.c_str(), str.length()); // processes the string to be hashed, must convert to char array.
	SHA256_Final(hash, &sha256); // outputs final hash

	std::stringstream ss; // store the hexadecimal version of our hash.

	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)(hash[i]); // converts hash to hexadecimal.
	}

	return ss.str(); // converts ss back to a string.
}*/ 