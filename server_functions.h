#pragma once
#include "basic_functions.h"
#include "userinput.h"
#include "download_functions.h"

std::string getServerLoc(bool shouldContainServer) {
enterpath: // another point that can be jumped to
	std::cout << "Enter path to server folder (without a slash at the end): "; // ask user for folder to put the server
	std::string serverLoc;
	std::getline(std::cin, serverLoc); // get input

	// check if server folder is valid
	if (!boost::filesystem::is_directory(serverLoc)) {
		std::cout << "That folder doesn't exist. Make sure the path is correct.\n";
		goto enterpath; // jump back to previous point
	}
	if (shouldContainServer) {
		if (!boost::filesystem::exists(serverLoc + "\\server.properties")) {
			std::cout << "That folder doesn't contain a server.\n";
			goto enterpath;
		}
	}
	else {
		if (!boost::filesystem::is_empty(serverLoc) && !boost::filesystem::exists(serverLoc + "\\server.properties")) {
			std::cout << "That folder isn't empty, please choose a folder that is empty.\n";
			goto enterpath;
		}
	}

	return serverLoc;
}

void removeOldJar(std::string serverLoc) {
errorremoving: // add a point to jump to if removing the old server.jar fails
	// if there is already a server.jar, we will remove it so we can upgrade the server to the version selected.
	if (boost::filesystem::exists(serverLoc + "\\server.jar")) {
		try {
			boost::filesystem::remove(serverLoc + "\\server.jar");
		}
		catch (...) { // catch any exception
			std::cout << "\nThere was an error removing the old server.jar from the server directory. Make sure the server is not currently running and if it isn't, try running this program as admin.\n";
			system("pause");
			cls();
			goto errorremoving;
		}
	}
}

std::string getHRSoftware(int serverSoftwareIndex) {
	switch (serverSoftwareIndex) {
	case 1:
		return "Vanilla";
	case 2:
		return "Forge";
	case 3:
		return "Fabric";
	case 4:
		return "Bukkit";
	case 5:
		return "Spigot";
	case 6: 
		return "Paper";
	}
}

void writeStartBat(std::string serverLoc, bool aikarsFlags, bool gui, std::string RAM) {
	std::ofstream startBat;
	startBat.open(serverLoc + "\\start.bat"); // create start.bat
	// depending on what the user chose, create the batch file they need
	if (aikarsFlags) {
		if (!boost::filesystem::exists(serverLoc + "\\fabric-server-launch.jar")) {
			if (gui == false) {
				startBat << "java -Xms" + RAM + " -Xmx" + RAM + " -XX:+UseG1GC -XX:+ParallelRefProcEnabled -XX:MaxGCPauseMillis=200 -XX:+UnlockExperimentalVMOptions -XX:+DisableExplicitGC -XX:+AlwaysPreTouch -XX:G1NewSizePercent=30 -XX:G1MaxNewSizePercent=40 -XX:G1HeapRegionSize=8M -XX:G1ReservePercent=20 -XX:G1HeapWastePercent=5 -XX:G1MixedGCCountTarget=4 -XX:InitiatingHeapOccupancyPercent=15 -XX:G1MixedGCLiveThresholdPercent=90 -XX:G1RSetUpdatingPauseTimePercent=5 -XX:SurvivorRatio=32 -XX:+PerfDisableSharedMem -XX:MaxTenuringThreshold=1 -Dusing.aikars.flags=https://mcflags.emc.gs -Daikars.new.flags=true -jar server.jar nogui";
			}
			else {
				startBat << "java -Xms" + RAM + " -Xmx" + RAM + " -XX:+UseG1GC -XX:+ParallelRefProcEnabled -XX:MaxGCPauseMillis=200 -XX:+UnlockExperimentalVMOptions -XX:+DisableExplicitGC -XX:+AlwaysPreTouch -XX:G1NewSizePercent=30 -XX:G1MaxNewSizePercent=40 -XX:G1HeapRegionSize=8M -XX:G1ReservePercent=20 -XX:G1HeapWastePercent=5 -XX:G1MixedGCCountTarget=4 -XX:InitiatingHeapOccupancyPercent=15 -XX:G1MixedGCLiveThresholdPercent=90 -XX:G1RSetUpdatingPauseTimePercent=5 -XX:SurvivorRatio=32 -XX:+PerfDisableSharedMem -XX:MaxTenuringThreshold=1 -Dusing.aikars.flags=https://mcflags.emc.gs -Daikars.new.flags=true -jar server.jar";
			}
		}
		else {
			if (gui == false) {
				startBat << "java -Xms" + RAM + " -Xmx" + RAM + " -XX:+UseG1GC -XX:+ParallelRefProcEnabled -XX:MaxGCPauseMillis=200 -XX:+UnlockExperimentalVMOptions -XX:+DisableExplicitGC -XX:+AlwaysPreTouch -XX:G1NewSizePercent=30 -XX:G1MaxNewSizePercent=40 -XX:G1HeapRegionSize=8M -XX:G1ReservePercent=20 -XX:G1HeapWastePercent=5 -XX:G1MixedGCCountTarget=4 -XX:InitiatingHeapOccupancyPercent=15 -XX:G1MixedGCLiveThresholdPercent=90 -XX:G1RSetUpdatingPauseTimePercent=5 -XX:SurvivorRatio=32 -XX:+PerfDisableSharedMem -XX:MaxTenuringThreshold=1 -Dusing.aikars.flags=https://mcflags.emc.gs -Daikars.new.flags=true -jar fabric-server-launch.jar nogui";
			}
			else {
				startBat << "java -Xms" + RAM + " -Xmx" + RAM + " -XX:+UseG1GC -XX:+ParallelRefProcEnabled -XX:MaxGCPauseMillis=200 -XX:+UnlockExperimentalVMOptions -XX:+DisableExplicitGC -XX:+AlwaysPreTouch -XX:G1NewSizePercent=30 -XX:G1MaxNewSizePercent=40 -XX:G1HeapRegionSize=8M -XX:G1ReservePercent=20 -XX:G1HeapWastePercent=5 -XX:G1MixedGCCountTarget=4 -XX:InitiatingHeapOccupancyPercent=15 -XX:G1MixedGCLiveThresholdPercent=90 -XX:G1RSetUpdatingPauseTimePercent=5 -XX:SurvivorRatio=32 -XX:+PerfDisableSharedMem -XX:MaxTenuringThreshold=1 -Dusing.aikars.flags=https://mcflags.emc.gs -Daikars.new.flags=true -jar fabric-server-launch.jar";
			}
		}
	}
	else {
		if (!boost::filesystem::exists(serverLoc + "\\fabric-server-launch.jar")) {
			if (gui == false) {
				startBat << "java -Xmx" + RAM + " -jar server.jar nogui";
			}
			else {
				startBat << "java -Xmx" + RAM + " -jar server.jar";
			}
		}
		else {
			if (gui == false) {
				startBat << "java -Xmx" + RAM + " -jar fabric-server-launch.jar nogui";
			}
			else {
				startBat << "java -Xmx" + RAM + " -jar fabric-server-launch.jar";
			}
		}
	}
	startBat.close();
}

// edits a server's start.bat file
int editStartBat() {
	editstartbat:
	std::cout << "Enter path to server folder (without a slash at the end): ";
	std::string serverLoc;
	std::string response;
	std::getline(std::cin, serverLoc); // get input of server folder

	// make sure folder is valid
	if (!boost::filesystem::is_directory(serverLoc)) {
		std::cout << "That folder doesn't exist. Make sure the path is correct.\n";
		goto editstartbat;
	}
	if (!boost::filesystem::exists(serverLoc + "\\start.bat")) {
		std::cout << "That folder doesn't contain a Minecraft server\n";
		goto editstartbat;
	}

	// ask start.bat questions
	std::cout << "Would you like a GUI for the server? [y/N] ";
	std::getline(std::cin, response);
	bool gui = false;
	if (response != "y" && response != "Y") {
		gui = false;
	}
	else {
		gui = true;
	}
	std::string RAM;
editEnterRAM:
	std::cout << "How much RAM would you like to allocate to the server? Make sure to enter it like 4G or 1024M: ";
	std::getline(std::cin, RAM);
	bool validRAMChar = false;
	if (RAM.back() == 'M' || RAM.back() == 'm' || RAM.back() == 'G' || RAM.back() == 'g') validRAMChar = true;
	if (!isNumber(RAM.substr(0, RAM.size() - 1)) || validRAMChar == false) {
		cls();
		std::cout << "Invalid amount of RAM. Check that you typed it in correctly.\n";
		goto editEnterRAM;
	}
	std::cout << "Would you like to use Aikars flags? (http://bit.ly/aikarsflags) [Y/n] ";
	std::getline(std::cin, response);
	bool aikarsFlags = false;
	if (response != "n" && response != "N") {
		aikarsFlags = true;
	}
	else {
		aikarsFlags = false;
	}

	// write new start.bat
	writeStartBat(serverLoc, aikarsFlags, gui, RAM);

	// ask user what to do next, same code as what is run when server is created
	std::cout << " Done!\n";
editFinalChoice:
	std::cout << "1) Start server\n";
	std::cout << "2) Edit another server\n";
	std::cout << "3) Exit\n";
	std::cout << "What would you like to do next? ";
	std::getline(std::cin, response);
	std::stringstream responseStr(response);
	int responseInt;
	responseStr >> responseInt;
	cls();
	std::string command;
	switch (responseInt) {
	case 1:
	{
		std::string command = "start /D \"" + serverLoc + "\" \"Minecraft Server\" \"" + serverLoc + "\\start.bat\"";
		system(command.c_str());
		break;
	}
	case 2:
		return 0; // return 0 which indicates to the function to start again instead of exiting
	case 3:
		exit(0); 
	default:
		std::cout << "Invalid option. Please choose either 1, 2 or 3.";
		goto editFinalChoice;
	}
}

int changeServerSoftware() {
	std::string response; // a variable that user input will go in.
changeserversoftware:
	cls();

	// ask user about what server software they are upgrading to/from
	std::cout << "What is the current server software?\n";
	int currentSoftwareIndex = serverSoftware();
	std::cout << "What is the current major version?\n";
	int currentMajorVersionIndex = majorVersions(currentSoftwareIndex);
	std::cout << "What is the current minor version?\n";
	int currentMinorVersionIndex = minorVersions(currentMajorVersionIndex, currentSoftwareIndex);
	std::cout << "What server software do you want to upgrade to?\n";
	int upgradeSoftwareIndex = serverSoftware();
	std::cout << "What major version do you want to upgrade to?\n";
	int upgradeMajorVersionIndex = majorVersions(upgradeSoftwareIndex);
	std::cout << "What minor version do you want to upgrade to?\n";
	int upgradeMinorVersionIndex = minorVersions(upgradeMajorVersionIndex, upgradeSoftwareIndex);

	// get human readable formats of the versions and ask the user if what they selected is correct
	std::string currentHRVersion = getHRVersion(currentSoftwareIndex, currentMajorVersionIndex, currentMinorVersionIndex);
	std::string upgradeHRVersion = getHRVersion(upgradeSoftwareIndex, upgradeMajorVersionIndex, upgradeMinorVersionIndex);
	std::string currentHRSoftware = getHRSoftware(currentSoftwareIndex);
	std::string upgradeHRSoftware = getHRSoftware(upgradeSoftwareIndex);

	// ask user if what they put is what they want	
	std::cout << "You currently have a " << currentHRSoftware << " " << currentHRVersion << " server and you want to upgrade to a " << upgradeHRSoftware << " " << upgradeHRVersion << " server. Is that correct? [Y/n] ";
	std::getline(std::cin, response);
	if (response == "n" || response == "N") {
		goto changeserversoftware; // if not then go back to the start so the user can do it again
	}

	// check if the server can be changed to the version chosen and check if world files need to be rearranged (going from bukkit, spigot or paper to something else)
	bool relocateWorldFiles = false;
	bool installingOldVersion = false;
	bool forgeToNonForge = false;
	bool potentialModIncompatibility = false;

	// convert the version numbers into arrays of numbers (for example 1.8.9 becomes [1, 8, 9])
	std::istringstream currentHRVersionSS(currentHRVersion);
	std::vector<std::string> currentHRVersionSplit;
	for (std::string each; std::getline(currentHRVersionSS, each, '.'); currentHRVersionSplit.push_back(each));
	
	std::istringstream upgradeHRVersionSS(upgradeHRVersion);
	std::vector<std::string> upgradeHRVersionSplit;
	for (std::string each; std::getline(upgradeHRVersionSS, each, '.'); upgradeHRVersionSplit.push_back(each));

	// turn versions like 1.8 into 1.8.0
	if (currentHRVersionSplit.size() == 2) currentHRVersionSplit.insert(currentHRVersionSplit.end(), "0");
	if (upgradeHRVersionSplit.size() == 2) upgradeHRVersionSplit.insert(upgradeHRVersionSplit.end(), "0");

	if (std::stoi(currentHRVersionSplit[0]) > std::stoi(upgradeHRVersionSplit[0])) installingOldVersion = true; // if the first number of the current version is greater than the first number of the version being upgraded to, we are upgrading to an older version
	else if (std::stoi(currentHRVersionSplit[0]) == std::stoi(upgradeHRVersionSplit[0])) { // if they are equal
		if (std::stoi(currentHRVersionSplit[1]) > std::stoi(upgradeHRVersionSplit[1])) installingOldVersion = true; // if the second number of the current version is greater than the second number of the version being upgraded to, we are upgrading to an older version.
		else if (std::stoi(currentHRVersionSplit[1]) == std::stoi(upgradeHRVersionSplit[1])) { // if they are equal
			if (std::stoi(currentHRVersionSplit[2]) > std::stoi(upgradeHRVersionSplit[2])) installingOldVersion = true; // I think you get the idea of what this code does now
		}
	}


	if ((currentSoftwareIndex == 4 || currentSoftwareIndex == 5 || currentSoftwareIndex == 6) && !(upgradeSoftwareIndex == 4 || upgradeSoftwareIndex == 5 || upgradeSoftwareIndex == 6)) relocateWorldFiles = true; // if going from a bukkit based version to non-bukkit based, world files need to be rearranged to not loose the nether and end.
	// paper is missing 1.7 so we have to make sure the indexes are equal (for example paper's major index 1 is equal to spigot's major index 2)
	//if (currentSoftwareIndex != 6 && upgradeSoftwareIndex != 6) { // if not going from paper to paper
	//	if (currentSoftwareIndex == 6) if (upgradeMajorVersionIndex < currentMajorVersionIndex + 1) installingOldVersion = true; // if the current major version index is larger than the one being upgraded to, there is a high chance of world corruption (for example the 1.16 nether is not in 1.15 so can cause issues).  	
	//	if (upgradeSoftwareIndex == 6) if (upgradeMajorVersionIndex + 1 < currentMajorVersionIndex) installingOldVersion = true; // if the current major version index is larger than the one being upgraded to, there is a high chance of world corruption (for example the 1.16 nether is not in 1.15 so can cause issues).  
	//}

	//else if (upgradeMajorVersionIndex == currentMajorVersionIndex) if (if (upgradeMinorVersionIndex < currentMinorVersionIndex) installingOldVersion = true; // if the current major version and the one being upgraded to are the same, check the minor version. If the new minor version is older than the current one, the user is trying to upgrade to an older version.
	if (currentSoftwareIndex == 2 && upgradeSoftwareIndex != 2) forgeToNonForge = true; // if the current software is forge and the one being upgraded to is not forge, there is a high chance of world corruption if there are blocks added by mods.
	if (currentSoftwareIndex == 2 && upgradeSoftwareIndex == 2) if (currentMajorVersionIndex != upgradeMajorVersionIndex) potentialModIncompatibility = true; // if going from forge to a different major version of forge (for example forge 1.15 to 1.16) some mods may be incompatible.

	// confirmation that the user wants to do things that may cause issues
	if (installingOldVersion) {
		std::cout << "You are trying to change your server to an older version than you currently have, this can cause world corruption and even cause your server to not start. A backup is highly recommended. Are you sure you want to do this? [y/N] ";
		std::getline(std::cin, response);
		if (response != "y" && response != "Y") {
			goto changeserversoftware; // if not then go back to the start so the user can do it again
		}
	}
	if (forgeToNonForge) {
		std::cout << "You are trying to change your server from Forge to non-Forge. This can cause world corruption. A backup is highly recommended. Are you sure you want to do this? [y/N] ";
		std::getline(std::cin, response);
		if (response != "y" && response != "Y") {
			goto changeserversoftware; // if not then go back to the start so the user can do it again
		}
	}
	if (potentialModIncompatibility) {
		std::cout << "You are trying to update your server to a new major version of Forge. Make sure your mods are up to date or your server may not start. Are you sure you want to do this? [y/N] ";
		std::getline(std::cin, response);
		if (response != "y" && response != "Y") {
			goto changeserversoftware; // if not then go back to the start so the user can do it again
		}
	}

	// get server path
	std::string serverLoc = getServerLoc(true);

	removeOldJar(serverLoc);

	std::cout << "Updating server...\n";

	if (upgradeSoftwareIndex == 2) { // if it is forge
		std::string command = "del \"" + serverLoc + "\\forge*.jar\" >nul 2>&1"; // put the command to delete any forge jar files in the variable called command
		system(command.c_str()); // run the command
		downloadFile(getDownloadURL(upgradeSoftwareIndex, upgradeHRVersion), serverLoc + "\\forgeinstaller.jar"); // download the forge installer for the version requested
		cls(); // clear screen
		std::cout << "Creating server. This may take a while, please be patient...\n";
		command = serverLoc.substr(0, 2) + "&& cd " + serverLoc + " && java -jar forgeinstaller.jar --installServer"; // run the forge installer
		int exitCode = system(command.c_str());
		if (exitCode != 0) error("Forge installer returned non-zero exit code");
		cls();
		boost::filesystem::remove(serverLoc + "\\forgeinstaller.jar"); // delete the forge installer
		command = "rename \"" + serverLoc + "\\forge*.jar\" server.jar";
		system(command.c_str()); // rename the forge server file to server.jar
	}
	else if (upgradeSoftwareIndex == 3) { // if it is fabric
		std::string command = "del \"" + serverLoc + "\\fabric*.jar\" >nul 2>&1";
		system(command.c_str()); // delete all old fabric versions if there are any
		std::string downloadURL = getDownloadURL(upgradeSoftwareIndex, upgradeHRVersion);
		if (downloadURL == "") error("Error getting fabric URL"); // in case of error getting fabric url, exit.
		downloadFile(downloadURL, serverLoc + "\\fabricinstaller.jar"); // download the fabric installer
		cls(); // clear screen
		std::cout << "Creating server. This may take a while, please be patient...\n";
		command = "java -jar \"" + serverLoc + "\\fabricinstaller.jar\" server -dir \"" + serverLoc + "\" -downloadMinecraft -mcversion " + upgradeHRVersion;
		int exitCode = system(command.c_str()); // run the fabric installer
		if (exitCode != 0) error("Fabric installer returned non-zero exit code");
		cls(); // clear screen
		boost::filesystem::remove(serverLoc + "\\fabricinstaller.jar"); // delete the fabric installer
	}
	else { // if anything else
		downloadFile(getDownloadURL(upgradeSoftwareIndex, upgradeHRVersion), serverLoc + "\\server.jar"); // simply download the server jar file as server.jar
	}

	if (relocateWorldFiles) {
		// find the world name
		std::ifstream file(serverLoc + "\\server.properties");
		std::string line;
		std::string worldName = "";
		while (std::getline(file, line)) {
			if (line.find("level-name=") == 0) {
				worldName = line.substr(line.find("level-name=") + 11);
			}
		}
		if (worldName == "") {
			std::cout << "Unable to automatically find the world name. Enter the world name ('no world' if your server doesn't have a world): ";
			std::getline(std::cin, worldName); // get input
		}
		while (true) {
			if (worldName == "no world") break; // if the user entered 'no world', break out of the while true loop, causing the world to not be touched
			if (boost::filesystem::exists(serverLoc + "\\" + worldName)) {
				if (boost::filesystem::exists(serverLoc + "\\" + worldName + "_nether\\DIM-1")) {
					boost::filesystem::rename(serverLoc + "\\" + worldName + "_nether\\DIM-1", serverLoc + "\\" + worldName + "\\DIM-1");
					boost::filesystem::remove_all(serverLoc + "\\" + worldName + "_nether");
				}
				else error("Nether folder didn't exist when relocating");
				if (boost::filesystem::exists(serverLoc + "\\" + worldName + "_the_end\\DIM1")) {
					boost::filesystem::rename(serverLoc + "\\" + worldName + "_the_end\\DIM1", serverLoc + "\\" + worldName + "\\DIM1");
					boost::filesystem::remove_all(serverLoc + "\\" + worldName + "_the_end");
				}
				else error("End folder didn't exist when relocating");
				break;
			}
			else {
				std::cout << "The world folder doesn't exist. Please enter the name of the world folder ('no world' if your server doesn't have a world): ";
				std::getline(std::cin, worldName); // get input
			}
		}
	}

finalChoice: // create point to be jumped to
	std::cout << "1) Start server\n";
	std::cout << "2) Change new server\n";
	std::cout << "3) Exit\n";
	std::cout << "What would you like to do next? ";
	std::getline(std::cin, response); // get input

	// convert to number
	std::stringstream responseStr(response);
	int responseInt;
	responseStr >> responseInt;

	cls(); // clear screen
	switch (responseInt) {
	case 1: // if they chose start server
	{
		std::string command = "start /D \"" + serverLoc + "\" \"Minecraft Server\" \"" + serverLoc + "\\start.bat\"";
		system(command.c_str()); // start server in the server directory
		break;
	}
	case 2:
	{
		goto changeserversoftware; // go back to start so that another server can be made
	}
	case 3:
	{
		return 0;
	}
	default:
	{
		std::cout << "Invalid option. Please choose either 1, 2 or 3.\n";
		goto finalChoice; // if invalid option, jump back
	}
	}
}

int deleteWorld() {
	std::string response;
	std::cout << "Are you really sure you want to delete your world? [y/N] "; // ask if user really wants to delete their world
	std::getline(std::cin, response);
	if (response != "y" || response != "Y") {
		exit(0); // if not then exit the program
	}
enterpath: // another point that can be jumped to
	std::string serverLoc = getServerLoc(true);
	

	// find the world name
	std::ifstream file(serverLoc + "\\server.properties");
	std::string line;
	std::string worldName = "";
	while (std::getline(file, line)) {
		if (line.find("level-name=") == 0) {
			worldName = line.substr(line.find("level-name=") + 11);
		}
	}
	if (worldName == "") {
		std::cout << "Unable to automatically find the world name. Enter the world name ('no world' if your server doesn't have a world): ";
		std::getline(std::cin, worldName); // get input
	}
	while (true) {
		if (worldName == "no world") break; // if the user entered 'no world', break out of the while true loop, causing the world to not be touched
		if (boost::filesystem::exists(serverLoc + "\\" + worldName)) {
			boost::filesystem::remove_all(serverLoc + "\\" + worldName);
			if (boost::filesystem::exists(serverLoc + "\\" + worldName + "_nether\\DIM-1")) {
				boost::filesystem::remove_all(serverLoc + "\\" + worldName + "_nether");
			}
			if (boost::filesystem::exists(serverLoc + "\\" + worldName + "_the_end\\DIM1")) {
				boost::filesystem::remove_all(serverLoc + "\\" + worldName + "_the_end");
			}
			break;
		}
		else {
			std::cout << "The world folder doesn't exist. Please enter the name of the world folder ('no world' if your server doesn't have a world): ";
			std::getline(std::cin, worldName); // get input
		}
	}
	std::cout << "World deleted!";
finalChoice: // create point to be jumped to
	std::cout << "1) Start server\n";
	std::cout << "2) Delete another world\n";
	std::cout << "3) Exit\n";
	std::cout << "What would you like to do next? ";
	std::getline(std::cin, response); // get input

	// convert to number
	std::stringstream responseStr(response);
	int responseInt;
	responseStr >> responseInt;

	cls(); // clear screen
	switch (responseInt) {
	case 1: // if they chose start server
	{
		std::string command = "start /D \"" + serverLoc + "\" \"Minecraft Server\" \"" + serverLoc + "\\start.bat\"";
		system(command.c_str()); // start server in the server directory
		break;
	}
	case 2:
	{
		goto enterpath; // go back to start so that another server can be made
	}
	case 3:
	{
		return 0;
	}
	default:
	{
		std::cout << "Invalid option. Please choose either 1, 2 or 3.";
		goto finalChoice; // if invalid option, jump back
	}
	}
	return 1;
}

int createServer() {
	std::string response; // a string that user input goes into
create: // create point that can be jumped to
	cls();
	int serverSoftwareIndex = serverSoftware(); // run serverSoftware function (which asks user what server software they want) and saves the value it returns into a variable

	// Get human readable server software
	std::string software = getHRSoftware(serverSoftwareIndex);

	// tell user which one was selected
	std::cout << software << " selected\n";

	int serverVersionIndex = majorVersions(serverSoftwareIndex); // ask user what major version they want and save it in serverVersionIndex
	if (serverVersionIndex == 0) return 1; // if the function returned 0, something went wrong so we exit the program
	cls(); // clear screen

	int serverMinorIndex = minorVersions(serverVersionIndex, serverSoftwareIndex); // get minor server version
	std::string version = getHRVersion(serverSoftwareIndex, serverVersionIndex, serverMinorIndex); // convert all the integers we have collected into a human readable version number


	// ask user if what they put is what they want
	std::cout << "You have chosen a " << software << " " << version << " server. Is that correct? [Y/n] ";
	std::getline(std::cin, response);
	if (response == "n" || response == "N") {
		goto create; // if not then go back to the start so the user can do it again
	}

	// get minecraft major version
	int selectedMajorVersion = 0;
	std::istringstream(version.substr(version.find(".") + 1)) >> selectedMajorVersion;

	int requiredMajorJavaVersion = 8; // a variable for the minimum required java version
	if (selectedMajorVersion >= 17) requiredMajorJavaVersion = 16; // if it is minecraft 1.17 or above, the minimum java version is 16

	if (serverSoftwareIndex == 2) {
		if (javaCheck(true, requiredMajorJavaVersion) == 1) return (1); // if forge is selected and the user chooses not to install java, the program will exit.
	}
	else {
		javaCheck(false, requiredMajorJavaVersion); // check if java is installed
	}
	cls(); // clear screen
	
	std::string serverLoc = getServerLoc(false);


	std::cout << "Would you like a GUI for the server? [y/N] "; // ask if user wants gui (if they answer no, it will put nogui on the end)
	std::getline(std::cin, response); // get input
	bool gui = false;
	if (response != "y" && response != "Y") {
		gui = false;
	}
	else {
		gui = true;
	}
	std::string RAM;

enterRAM: // another point that can be jumped back to
	std::cout << "How much RAM would you like to allocate to the server? Make sure to enter it like 4G or 1024M: "; // ask user for ram
	std::getline(std::cin, RAM); // get input

	// check if input is valid
	if (RAM != "") {
		bool validRAMChar = false;
		if (RAM.back() == 'M' || RAM.back() == 'G' || RAM.back() == 'm' || RAM.back() == 'g') validRAMChar = true;
		if (!isNumber(RAM.substr(0, RAM.size() - 1)) || validRAMChar == false) {
			cls();
			std::cout << "Invalid amount of RAM. Check that you typed it in correctly.\n";
			goto enterRAM;
		}
	}
	else {
		std::cout << "You didn't type anything. You need to type the amount of RAM the server is going to use.\n";
		goto enterRAM;
	}

	std::cout << "Would you like to use Aikars flags? (http://bit.ly/aikarsflags) [Y/n] "; // asks user if they want to use the recommended server flags by Aikar
	std::getline(std::cin, response); // get input
	bool aikarsFlags = false;
	if (response != "n" && response != "N") {
		aikarsFlags = true;
	}
	else {
		aikarsFlags = false;
	}
	bool eula;
	std::cout << "Do you agree to the EULA (https://account.mojang.com/documents/minecraft_eula)? If you don't, the server will not start. [Y/n] "; // ask if the user agrees to Mojang's EULA
	std::getline(std::cin, response);
	if (response != "n" && response != "N") {
		eula = true;
	}
	else {
		eula = false;
	}
	cls();
	std::cout << "Downloading server, please wait...";
	
	removeOldJar(serverLoc);

	if (serverSoftwareIndex == 2) { // if it is forge
		std::string command = "del \"" + serverLoc + "\\forge*.jar\" >nul 2>&1"; // put the command to delete any forge jar files in the variable called command
		system(command.c_str()); // run the command
		downloadFile(getDownloadURL(serverSoftwareIndex, version), serverLoc + "\\forgeinstaller.jar"); // download the forge installer for the version requested
		cls(); // clear screen
		std::cout << "Creating server. This may take a while, please be patient...\n";
		command = serverLoc.substr(0, 2) + "&& cd " + serverLoc + " && java -jar forgeinstaller.jar --installServer"; // run the forge installer
		int exitCode = system(command.c_str());
		if (exitCode != 0) error("Forge installer returned non-zero exit code");
		cls();
		boost::filesystem::remove(serverLoc + "\\forgeinstaller.jar"); // delete the forge installer
		command = "rename \"" + serverLoc + "\\forge*.jar\" server.jar";
		system(command.c_str()); // rename the forge server file to server.jar
	}
	else if (serverSoftwareIndex == 3) { // if it is fabric
		std::string command = "del \"" + serverLoc + "\\fabric*.jar\" >nul 2>&1";
		system(command.c_str()); // delete all old fabric versions if there are any
		std::string downloadURL = getDownloadURL(serverSoftwareIndex, version);
		if (downloadURL == "") error("Error getting Fabric URL"); // in case of error getting fabric url, exit.
		downloadFile(downloadURL, serverLoc + "\\fabricinstaller.jar"); // download the fabric installer
		cls(); // clear screen
		std::cout << "Creating server. This may take a while, please be patient...\n";
		command = "java -jar \"" + serverLoc + "\\fabricinstaller.jar\" server -dir \"" + serverLoc + "\" -downloadMinecraft -mcversion " + version;
		int exitCode = system(command.c_str()); // run the fabric installer
		if (exitCode != 0) error("Fabric installer returned non-zero exit code");
		cls(); // clear screen
		boost::filesystem::remove(serverLoc + "\\fabricinstaller.jar"); // delete the fabric installer
	}
	else { // if anything else
		downloadFile(getDownloadURL(serverSoftwareIndex, version), serverLoc + "\\server.jar"); // simply download the server jar file as server.jar
	}
	writeStartBat(serverLoc, aikarsFlags, gui, RAM);

	// write eula if user agreed
	if (eula) {
		std::ofstream eulaTxt;
		eulaTxt.open(serverLoc + "\\eula.txt");
		eulaTxt << "#By changing the setting below to TRUE you are indicating your agreement to our EULA (https://account.mojang.com/documents/minecraft_eula).\n#Sun Feb 24 09:04:52 GMT 2019\neula=true";
		eulaTxt.close();
	}

	std::cout << " Done!\n";
	std::cout << "If you would like to run the server later, go to the server location and run the start file.\n";
finalChoice: // create point to be jumped to
	std::cout << "1) Start server\n";
	std::cout << "2) Create new server\n";
	std::cout << "3) Exit\n";
	std::cout << "What would you like to do next? ";
	std::getline(std::cin, response); // get input

	// convert to number
	std::stringstream responseStr(response);
	int responseInt;
	responseStr >> responseInt;

	cls(); // clear screen
	switch (responseInt) {
	case 1: // if they chose start server
	{
		std::string command = "start /D \"" + serverLoc + "\" \"Minecraft Server\" \"" + serverLoc + "\\start.bat\"";
		system(command.c_str()); // start server in the server directory
		return 0;
	}
	case 2:
	{
		goto create; // go back to start so that another server can be made
	}
	case 3:
	{
		return 0;
	}
	default:
	{
		std::cout << "Invalid option. Please choose either 1, 2 or 3.\n";
		goto finalChoice; // if invalid option, jump back
	}
	}
}









int editServer() { // edits a server
	std::string response; // a string that user input goes into
editserver: // create point that can be jumped to
	std::cout << "1) Edit RAM allocation and turn Aikar's flags on and off.\n";
	std::cout << "2) Change server software\n";
	std::cout << "3) Delete world\n";
	std::cout << "What would you like to do? [1, 2 or 3] ";
	std::getline(std::cin, response); // get input

	// convert to int
	std::stringstream mainResponseStr(response);
	int mainResponseInt;
	mainResponseStr >> mainResponseInt;

	cls(); // clear screen
	switch (mainResponseInt)
	{
	case 1: // if they selected option 1 (create a server)
	{
		int returnCode = editStartBat(); // call the createServer function and exit when it returns something other than 0
		if (returnCode == 0) goto editserver; // if it returned 0, start again
		return returnCode; // if it didn't return 0, return the exit code which will quit the program with that code.
	}
	case 2: // if the user chose to edit a server (option 2)
	{
		int returnCode = changeServerSoftware(); // call the editServer function and exit when it returns something
		if (returnCode == 0) goto editserver;
		return returnCode;
	}
	case 3: // if user chose to join the discord
	{
		int returnCode = deleteWorld();
		if (returnCode == 0) goto editserver;
		return returnCode;
	}
	default:
	{
		std::cout << "Invalid option: " << response << "\n";
		goto editserver;
	}
	}
	
}