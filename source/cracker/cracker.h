#pragma once
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


class Cracker
{
private:

	// vector of strings to store password list in.
	std::vector<std::string> passwords; 
	std::vector<std::string> passwords1;
	std::vector<std::string> passwords2;

	void start_threads();

public:

	bool running{ false };
	std::string hash{ 0 };
	const char* list{ 0 };
	void reader();

};

inline Cracker cracker;