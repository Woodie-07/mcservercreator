#pragma once
#include <windows.h> // Windows API stuff
#include <iostream> 
#include <sstream>
#include <stdlib.h>

void error(std::string errorCode = "Unknown Error") { // function called when there has been an error
	std::cout << "MCServerCreator has encountered an error and cannot continue. Please try again and if you still get this error, let me know on Discord.\n";
	std::cout << "Error: " + errorCode;
	std::cout << "Press any key to exit.\n";
	_getch(); // wait for a key press
	exit(1); // exit with return code 1
}

// Clear screen function, does stuff with the Windows API I don't really know, just got it from stackoverflow and it works
void cls(char fill = ' ') {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

// Checks if a number is a string
bool isNumber(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

// returns an env as an std::string (not null if the env var doesn't exist)
std::string env(const char* name)
{
	const char* ret = getenv(name);
	if (!ret) return "";
	return std::string(ret);
}

// check if java is installed and working
int javaCheck(bool forge, bool fabric, int requiredJavaMajorVersion) {

	std::string javaHome = env("JAVA_HOME"); // get value of JAVA_HOME environment variable

	int javaMajorVersion = 0; // variable that will eventually contain the major version of java

	std::fstream releaseFile; // creates a variable that can be used to read a file
	std::string releaseFilePath = javaHome + "\\release";
	releaseFile.open(releaseFilePath, std::ios::in); // open a file to perform read operation using file object
	if (releaseFile.is_open()) { // checking whether the file is open (exists and can be accessed)

		std::string line; // a variable that will be used for each line of the file

		while (std::getline(releaseFile, line)) {  // read data from file object and put it into string.
			int findResult = line.find("JAVA_VERSION="); // find JAVA_VERSION= in the line

			if (findResult != std::string::npos) { // if it was there
				std::string javaVersion = "";
				javaVersion = line.substr(findResult + 13); // get the text 13 characters after the start of JAVA_VERSION= which will be something like "11.0.11" for java 11
				javaVersion.erase(std::remove(javaVersion.begin(), javaVersion.end(), '\"'), javaVersion.end()); // remove the double quotes
				findResult = javaVersion.find("."); // find a dot in the line
				if (findResult != std::string::npos) { // if it was there
					std::string javaMajorVersionStr = javaVersion.substr(0, findResult); // get the text between the dot and the start of the string
					if (javaMajorVersionStr == "1") { // if the first number is 1 (such as with java 8 where the version is 1.8.0)
						findResult = javaVersion.find("1."); // find 1. in the line
						javaMajorVersionStr = javaVersion.substr(2, findResult + 2); // get the number 2 characters after the start of 1.
					}

					std::istringstream(javaMajorVersionStr) >> javaMajorVersion; // convert it to an int, finally giving us the java major version.
				}
			}
		}
		releaseFile.close();   //close the file object.
	}


	std::string response;
	if (javaMajorVersion == 0) {
		if (forge) {
			std::cout << "Your JAVA_HOME variable doesn't exist so MCServerCreator cannot verify if Java is installed. You cannot make a Forge server without Java. Would you like to install it? [Y/n] ";
		}
		else if (fabric) {
			std::cout << "Your JAVA_HOME variable doesn't exist so MCServerCreator cannot verify if Java is installed. You cannot make a Fabric server without Java. Would you like to install it? [Y/n] ";
		}
		else {
			std::cout << "Your JAVA_HOME variable doesn't exist so MCServerCreator cannot verify if Java is installed. The server will not run without Java. Would you like to install it? [Y/n] ";
		}
		std::getline(std::cin, response);
		if (response != "n" && response != "N") {
			system("start \"\" https://www.java.com/en/download/manual.jsp");
			std::cout << "Taking you to the Java website. Make sure to download the 'Windows Offline 64-bit' version. \n";
			system("pause");
		}
		else if (forge || fabric) {
			return(1);
		}
	}
	else if (javaMajorVersion < requiredJavaMajorVersion) { // if the current java macjor version is lower than the required one for the version
		std::cout << "Your currently installed Java version is too old for the version of Minecraft you are trying to create a server for. Please update to at least Java " << requiredJavaMajorVersion << " or your server won't launch. When installing, make sure you tick the box (if any) to set the 'JAVA_HOME' variable. \n"; // warn the user about the old java version
		std::cout << "Press any key to continue...\n";
		_getch(); // wait until a key is pressed (give user time to read it)
	}
	else {
		std::cout << "Java already installed.\n";
		return 0;
	}
}