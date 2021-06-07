#pragma once
#include <windows.h> // Windows API stuff
#include <iostream> 
#include <sstream>

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

// check if java is installed and working
int javaCheck(bool forge) {
	std::string response;
	if (system("java -version >nul 2>&1") == 1) {
		if (forge) {
			std::cout << "You do not have Java installed. You cannot make a Forge server without Java. Would you like to install it? [Y/n] ";
		}
		else {
			std::cout << "You do not have Java installed. The server will not run without Java. Would you like to install it? [Y/n] ";
		}
		std::getline(std::cin, response);
		if (response != "n" && response != "N") {
			system("start \"\" https://www.java.com/en/download/manual.jsp");
			std::cout << "Taking you to the Java website. Make sure to download the 'Windows Offline 64-bit' version. \n";
			system("pause");
		}
		else if (forge) {
			return(1);
		}
	}
	else {
		std::cout << "Java already installed.\n";
	}
}