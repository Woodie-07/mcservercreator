#pragma once
#include <iostream>
#include <sstream>
#include <iostream>
#include "basic_functions.h"

// Ask what server software the user wants
int serverSoftware() {
	// Infinite loop so if the user enters an invalid number, it will loop back to the start
	while (true) {
		std::string response;
		// output all software
		std::cout << "1) Vanilla\n";
		std::cout << "2) Forge\n";
		std::cout << "3) Fabric\n";
		std::cout << "4) CraftBukkit\n";
		std::cout << "5) Spigot\n";
		std::cout << "6) Paper\n";
		std::cout << "What would you like to do? [1, 2, 3, 4, 5 or 6] ";
		std::getline(std::cin, response); // get input

		// convert to integer
		std::stringstream responseStr(response);
		int responseInt;
		responseStr >> responseInt;

		cls(); // clear screen

		// check if input was valid
		if (responseInt < 7 && responseInt > 0) {
			return responseInt;
		}
		else {
			std::cout << "Invalid option: " << response << "\n";
		}
	}
}

// Ask what version the user wants
int majorVersions(int serverSoftwareIndex) {
	// Infinite loop so if the user enters an invalid number, it will loop back to the start
	while (true) {
		std::string response;
		// set minimum and maximum versions for different software
		int min = 0, max = 0;

		if (serverSoftwareIndex == 1) min = 7, max = 17; // vanilla
		else if (serverSoftwareIndex == 2) min = 7, max = 16; // forge
		else if (serverSoftwareIndex == 3) min = 14, max = 17; // fabric
		else if (serverSoftwareIndex == 4) min = 7, max = 17; // bukkit
		else if (serverSoftwareIndex == 5) min = 7, max = 17; // spigot
		else if (serverSoftwareIndex == 6) min = 8, max = 17; // paper

		if (min == 0 && max == 0) return 0; // if they didnt get set, something went wrong so we return 0 (not a valid option)

		int count = 0; // times looped

		// display correct versions depending on min and max
		for (int i = min; i <= max; i++) {
			count++;
			std::cout << std::to_string(count) + ") 1." + std::to_string(i) + "\n";
		}
		std::cout << "What would you like to do? [1-" + std::to_string(count) + "] ";
		std::getline(std::cin, response); // get input

		// convert to integer
		std::stringstream responseStr(response);
		int responseInt;
		responseStr >> responseInt;

		cls(); // clear screen

		// check if input was valid
		if (responseInt <= count && responseInt > 0) {
			return responseInt;
		}
		else {
			std::cout << "Invalid option: " << response << "\n";
		}
	}
}

std::map<int, std::map<int, std::vector<std::string> > > versions{ // a map that contains all of the versions, more specifically a map containing an integer (the server software) and a corresponding map containing an integer (the major version) and a vector (like an array) of all the versions.
	{
		1, std::map<int, std::vector<std::string>> { // vanilla
			{1, std::vector<std::string> {"1.7.2", "1.7.5", "1.7.8", "1.7.9", "1.7.10"}}, // 1.7
			{2, std::vector<std::string> {"1.8", "1.8.3", "1.8.4", "1.8.5", "1.8.6", "1.8.7", "1.8.8"}}, // 1.8
			{3, std::vector<std::string> {"1.9", "1.9.2", "1.9.4"}}, // 1.9
			{4, std::vector<std::string> {"1.10", "1.10.1", "1.10.2"}}, // 1.10
			{5, std::vector<std::string> {"1.11", "1.11.1", "1.11.2"}}, // 1.11
			{6, std::vector<std::string> {"1.12", "1.12.1", "1.12.2"}}, // 1.12
			{7, std::vector<std::string> {"1.13", "1.13.1", "1.13.2"}}, // 1.13
			{8, std::vector<std::string> {"1.14", "1.14.1", "1.14.2", "1.14.3", "1.14.4"}}, // 1.14
			{9, std::vector<std::string> {"1.15", "1.15.1", "1.15.2"}}, // 1.15
			{10, std::vector<std::string> {"1.16", "1.16.1", "1.16.2", "1.16.3", "1.16.4", "1.16.5"}}, // 1.16
			{11, std::vector<std::string> {"1.17", "1.17.1"}}, // 1.17
		}
	},
	{
		2, std::map<int, std::vector<std::string>> { // forge
			{1, std::vector<std::string> {"1.7.10"}}, // 1.7
			{2, std::vector<std::string> {"1.8", "1.8.8", "1.8.9"}}, // 1.8
			{3, std::vector<std::string> {"1.9", "1.9.4"}}, // 1.9
			{4, std::vector<std::string> {"1.10", "1.10.2"}}, // 1.10
			{5, std::vector<std::string> {"1.11", "1.11.2"}}, // 1.11
			{6, std::vector<std::string> {"1.12", "1.12.1", "1.12.2"}}, // 1.12
			{7, std::vector<std::string> {"1.13.2"}}, // 1.13
			{8, std::vector<std::string> {"1.14.2", "1.14.3", "1.14.4"}}, // 1.14
			{9, std::vector<std::string> {"1.15", "1.15.1", "1.15.2"}}, // 1.15
			{10, std::vector<std::string> {"1.16.1", "1.16.2", "1.16.3", "1.16.4", "1.16.5"}}, // 1.16
		}
	},
	{
		3, std::map<int, std::vector<std::string>> { // fabric
			{1, std::vector<std::string> {"1.14", "1.14.1", "1.14.2", "1.14.3", "1.14.4"}}, // 1.14
			{2, std::vector<std::string> {"1.15", "1.15.1", "1.15.2"}}, // 1.15
			{3, std::vector<std::string> {"1.16", "1.16.1", "1.16.2", "1.16.3", "1.16.4", "1.16.5"}}, // 1.16
			{4, std::vector<std::string> {"1.17", "1.17.1"}}, // 1.17
		}
	},
	{
		4, std::map<int, std::vector<std::string>> { // bukkit
			{1, std::vector<std::string> {"1.7.2", "1.7.5", "1.7.8", "1.7.9", "1.7.10"}}, // 1.7
			{2, std::vector<std::string> {"1.8", "1.8.3", "1.8.4", "1.8.5", "1.8.6", "1.8.7", "1.8.8"}}, // 1.8
			{3, std::vector<std::string> {"1.9", "1.9.2", "1.9.4"}}, // 1.9
			{4, std::vector<std::string> {"1.10", "1.10.1", "1.10.2"}}, // 1.10
			{5, std::vector<std::string> {"1.11", "1.11.1", "1.11.2"}}, // 1.11
			{6, std::vector<std::string> {"1.12", "1.12.1", "1.12.2"}}, // 1.12
			{7, std::vector<std::string> {"1.13", "1.13.1", "1.13.2"}}, // 1.13
			{8, std::vector<std::string> {"1.14", "1.14.1", "1.14.2", "1.14.3", "1.14.4"}}, // 1.14
			{9, std::vector<std::string> {"1.15", "1.15.1", "1.15.2"}}, // 1.15
			{10, std::vector<std::string> {"1.16", "1.16.1", "1.16.2", "1.16.3", "1.16.4", "1.16.5"}}, // 1.16
			{11, std::vector<std::string> {"1.17", "1.17.1"}}, // 1.17
		}
	},
	{
		5, std::map<int, std::vector<std::string>> { // spigot
			{1, std::vector<std::string> {"1.7.2", "1.7.5", "1.7.8", "1.7.9", "1.7.10"}}, // 1.7
			{2, std::vector<std::string> {"1.8", "1.8.3", "1.8.4", "1.8.5", "1.8.6", "1.8.7", "1.8.8"}}, // 1.8
			{3, std::vector<std::string> {"1.9", "1.9.2", "1.9.4"}}, // 1.9
			{4, std::vector<std::string> {"1.10", "1.10.1", "1.10.2"}}, // 1.10
			{5, std::vector<std::string> {"1.11", "1.11.1", "1.11.2"}}, // 1.11
			{6, std::vector<std::string> {"1.12", "1.12.1", "1.12.2"}}, // 1.12
			{7, std::vector<std::string> {"1.13", "1.13.1", "1.13.2"}}, // 1.13
			{8, std::vector<std::string> {"1.14", "1.14.1", "1.14.2", "1.14.3", "1.14.4"}}, // 1.14
			{9, std::vector<std::string> {"1.15", "1.15.1", "1.15.2"}}, // 1.15
			{10, std::vector<std::string> {"1.16", "1.16.1", "1.16.2", "1.16.3", "1.16.4", "1.16.5"}}, // 1.16
			{11, std::vector<std::string> {"1.17", "1.17.1"}}, // 1.17
		}
	},
	{
		6, std::map<int, std::vector<std::string>> { // paper
			{1, std::vector<std::string> {"1.8.8"}}, // 1.8
			{2, std::vector<std::string> {"1.9.4"}}, // 1.9
			{3, std::vector<std::string> {"1.10.2"}}, // 1.10
			{4, std::vector<std::string> {"1.11.2"}}, // 1.11
			{5, std::vector<std::string> {"1.12", "1.12.1", "1.12.2"}}, // 1.12
			{6, std::vector<std::string> {"1.13", "1.13.1", "1.13.2"}}, // 1.13
			{7, std::vector<std::string> {"1.14", "1.14.1", "1.14.2", "1.14.3", "1.14.4"}}, // 1.14
			{8, std::vector<std::string> {"1.15", "1.15.1", "1.15.2"}}, // 1.15
			{9, std::vector<std::string> {"1.16.1", "1.16.2", "1.16.3", "1.16.4", "1.16.5"}}, // 1.16
			{10, std::vector<std::string> {"1.17", "1.17.1"}}, // 1.17
		}
	},
};

// Ask what minor version the user wants
int minorVersions(int majorVersionIndex, int serverSoftwareIndex) {
	bool validInput = false;
	while (true) { // infinite loop
		int size = versions[serverSoftwareIndex][majorVersionIndex].size();
		for (int i = 1; i <= size; i++) {
			std::cout << std::to_string(i) + ") ";
			if (versions[serverSoftwareIndex][majorVersionIndex][i - 1] == "1.8.8") std::cout << "1.8.8 (also works with 1.8.9)"; // if outputting version 1.8.8, inform user that it also works with 1.8.9
			else std::cout << versions[serverSoftwareIndex][majorVersionIndex][i - 1];
			std::cout << "\n";
		}
		std::cout << "What would you like to do? ";
		if (size == 1) std::cout << "[Only 1] "; // if only one option, say only 1
		else std::cout << "[1-" + std::to_string(size) + "] "; // if more than 1 option, say 1 to the size of the vector
		std::string response;
		std::getline(std::cin, response); // get user input

		// convert to integer
		std::stringstream responseStr(response);
		int responseInt;
		responseStr >> responseInt;

		cls(); // clear screen

		if (responseInt <= size && responseInt > 0) { // check if input was valid
			return responseInt;
		}
		else {
			std::cout << "Invalid option: " << response << "\n";
		}
	}
}

// return human readable version from the softwareindex, the versionindex and the minorindex
std::string getHRVersion(int serverSoftwareIndex, int serverVersionIndex, int serverMinorIndex) {
	return(versions[serverSoftwareIndex][serverVersionIndex][serverMinorIndex - 1]);
}