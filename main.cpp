#include <curl.h> // curl downloads files
#include <iostream> 
#include <sstream>
#include <strsafe.h>
#include <windows.h> // Windows API stuff
#include <boost/filesystem.hpp> // is an external library, can check if files exist and stuff
#include <fstream>
#include <conio.h>
#include "server_functions.h"
#include "download_functions.h"

// main function that is run when server starts
int main() {
	float currentVersion = 2.5;
	std::string response;

	// check if version is old
	std::cout << "Checking for updates...\n";

	if (getLatestVersion() > currentVersion) { // get the latest version and check if it is larger than the current version
		std::cout << "A new version is available, would you like to download it? [Y/n] "; // ask user if they want to update
		std::getline(std::cin, response);
		if (response != "N" || response != "n") { // if the user didnt respond with 'n' or 'N', it will download the file in their browser
			std::string cmd = "start \"\" \"";
			cmd = cmd.append(getLatestURL());
			cmd = cmd.append("\"");
			system(cmd.c_str());
		}
	}

	// set window title
	TCHAR szNewTitle[MAX_PATH];
	StringCchPrintf(szNewTitle, MAX_PATH, TEXT("MCServerCreator by Woodie"));
	SetConsoleTitle(szNewTitle);

	cls(); // clear screen
	start: // create point that can be jumped to
	std::cout << "Welcome to MCServerCreator made by Woodie.\n";
	std::cout << "THIS IS A WORK IN PROGRESS, please notify me on Discord (Woodie#1096) if you find any bugs or have some feedback.\n";
	std::cout << "1) Create or update a server\n";
	std::cout << "2) Edit a server\n";
	std::cout << "3) Join the MCServerCreator Discord\n";
	std::cout << "What would you like to do? [1, 2 or 3] ";
	std::getline(std::cin, response); // get input

	// convert to int
	std::stringstream responseStr(response);
	int responseInt;
	responseStr >> responseInt;

	cls(); // clear screen
	switch (responseInt)
	{
	case 1: // if they selected option 1 (create a server)
	{
		return(createServer()); // call the createServer function and exit when it returns something
	}
	case 2: // if the user chose to edit a server (option 2)
	{
		return(editServer()); // call the editServer function and exit when it returns something
	}
	case 3: // if user chose to join the discord
		system("start \"\" https://discord.gg/ngRxbrh"); // open the discord link in their default web browser
		goto start;
	default:
		std::cout << "Invalid option: " << response << "\n";
		goto start;
	}
	return 0;
}

