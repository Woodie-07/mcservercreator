#pragma once
#include <curl.h>
#include <map>
#include <stdlib.h>
#include "userinput.h"


// dont really know what this does, needed it for CURL.
size_t WriteCallback(void* ptr, size_t size, size_t count, void* stream) {
	((std::string*)stream)->append((char*)ptr, 0, size * count);
	return size * count;
}

// downloads a file from a given url to a given path
int downloadFile(std::string url, std::string path) {
	CURL* curl;
	FILE* fp;
	CURLcode res;
	std::stringstream ss;
	std::string s;
	ss << FILENAME_MAX;
	char outfilename[FILENAME_MAX];
	strcpy(outfilename, path.c_str());
	curl = curl_easy_init();
	if (curl)
	{
		fp = fopen(outfilename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}
	if (res == CURLE_OK) return 0;
	else error(curl_easy_strerror(res)); // call the error function 
}

std::string downloadToMemory(std::string url) {
	// create needed variables
	CURL* curl;
	CURLcode res;
	std::string response;
	// download version number from pastebin and save it in string
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	if (res == CURLE_OK) return response; // res is CURLE_OK if success
	else error(curl_easy_strerror(res)); // call the error function 
}

// Returns the latest version of the program
float getLatestVersion() {
	std::string latestVersion = downloadToMemory("https://pastebin.com/raw/YKAwnMNP");
	// String to float conversion
	std::stringstream latestVersionStr(latestVersion);
	float latestVersionFloat;
	latestVersionStr >> latestVersionFloat;

	// return the latest version number
	return latestVersionFloat;
}

// Returns the URL to download the latest version
std::string getLatestURL() {
	return(downloadToMemory("https://pastebin.com/raw/JcBsJBax"));
}

// Returns the URL to download the latest fabric installer
std::string getLatestFabricURL() {
	return(downloadToMemory("https://pastebin.com/raw/2rx8UsTu"));
}

// Returns the direct download link for different server jars
// A lot of if statements, I don't know a better way to do it with version numbers. If it was a simple integer for version numbers I would use switch statements but thats not the case.
std::string getDownloadURL(int serverSoftwareIndex, std::string version) {
	switch (serverSoftwareIndex) {
	case 1: { // vanilla
		return("https://serverjars.com/api/fetchJar/vanilla/" + version);
	}
	case 2: { // forge
		// Not really a good naming scheme for forge so I have to have all of the URLs in the code.
		// Wish there was an API or something for getting the URL of forge versions but there isn't. I have had to go on my browser and find the URL for every version.
		// When forge updates, I will have to update the installer URL here so forge versions may be a little outdated. 

		std::map<std::string, std::string> forgeURLs{ // a map that contains all of the Forge URLs
			{"1.7.10",	"https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.7.10-10.13.4.1558-1.7.10/forge-1.7.10-10.13.4.1558-1.7.10-installer.jar"},
			{"1.8",		"https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.8-11.14.4.1563/forge-1.8-11.14.4.1563-installer.jar"},
			{"1.8.8",	"https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.8.8-11.15.0.1655/forge-1.8.8-11.15.0.1655-installer.jar"},
			{"1.8.9",	"https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.8.9-11.15.1.1722/forge-1.8.9-11.15.1.1722-installer.jar"},
			{"1.9",		"https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.9-12.16.1.1887/forge-1.9-12.16.1.1887-installer.jar"},
			{"1.9.4",	"https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.9.4-12.17.0.1976/forge-1.9.4-12.17.0.1976-installer.jar"},
			{"1.10",	"https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.10-12.18.0.2000-1.10.0/forge-1.10-12.18.0.2000-1.10.0-installer.jar"},
			{"1.10.2",	"https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.10.2-12.18.3.2511/forge-1.10.2-12.18.3.2511-installer.jar"},
			{"1.11",	"https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.11-13.19.1.2189/forge-1.11-13.19.1.2189-installer.jar"},
			{"1.11.2",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.11.2-13.20.1.2386/forge-1.11.2-13.20.1.2386-installer.jar"},
			{"1.12",    "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.12-14.21.1.2387/forge-1.12-14.21.1.2387-installer.jar"},
			{"1.12.1",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.12.1-14.22.1.2478/forge-1.12.1-14.22.1.2478-installer.jar"},
			{"1.12.2",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.12.2-14.23.5.2854/forge-1.12.2-14.23.5.2854-installer.jar"},
			{"1.13.2",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.13.2-25.0.219/forge-1.13.2-25.0.219-installer.jar"},
			{"1.14.2",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.14.2-26.0.63/forge-1.14.2-26.0.63-installer.jar"},
			{"1.14.3",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.14.3-27.0.60/forge-1.14.3-27.0.60-installer.jar"},
			{"1.14.4",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.14.4-28.2.0/forge-1.14.4-28.2.0-installer.jar"},
			{"1.15",    "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.15-29.0.4/forge-1.15-29.0.4-installer.jar"},
			{"1.15.1",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.15.1-30.0.51/forge-1.15.1-30.0.51-installer.jar"},
			{"1.15.2",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.15.2-31.2.0/forge-1.15.2-31.2.0-installer.jar"},
			{"1.16.1",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.16.1-32.0.108/forge-1.16.1-32.0.108-installer.jar"},
			{"1.16.2",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.16.2-33.0.61/forge-1.16.2-33.0.61-installer.jar"},
			{"1.16.3",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.16.3-34.1.0/forge-1.16.3-34.1.0-installer.jar"},
			{"1.16.4",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.16.4-35.1.4/forge-1.16.4-35.1.4-installer.jar"},
			{"1.16.5",  "https://files.minecraftforge.net/maven/net/minecraftforge/forge/1.16.5-36.0.1/forge-1.16.5-36.0.1-installer.jar"},
		};
		return(forgeURLs[version]); // returns the url corresponding to the version
	}
	case 3: { // fabric
		return (getLatestFabricURL());
	}
	case 4: { // bukkit
		// naming scheme changes on different versions of spigot and bukkit so I have to return a different URL for some versions
		if (version == "1.15.1" || version == "1.15" || version == "1.14.4" || version == "1.14.3" || version == "1.14.2" || version == "1.14.1" || version == "1.14") return("https://cdn.getbukkit.org/craftbukkit/craftbukkit-" + version + "-R0.1-SNAPSHOT.jar");
		if (version == "1.10.2" || version == "1.10" || version == "1.9.4" || version == "1.9.2" || version == "1.9" || version == "1.8.8" || version == "1.8.7" || version == "1.8.6" || version == "1.8.5" || version == "1.8.4" || version == "1.8.3" || version == "1.8") return("https://cdn.getbukkit.org/craftbukkit/craftbukkit-" + version + "-R0.1-SNAPSHOT-latest.jar");
		if (version == "1.7.10") return("https://cdn.getbukkit.org/craftbukkit/craftbukkit-1.7.10-R0.1-20140808.005431-8.jar");
		if (version == "1.7.9") return("https://cdn.getbukkit.org/craftbukkit/craftbukkit-1.7.9-R0.2-SNAPSHOT.jar");
		if (version == "1.7.8") return("https://cdn.getbukkit.org/craftbukkit/craftbukkit-1.7.8-R0.1-SNAPSHOT.jar");
		if (version == "1.7.5") return("https://cdn.getbukkit.org/craftbukkit/craftbukkit-1.7.5-R0.1-20140402.020013-12.jar");
		if (version == "1.7.2") return("https://cdn.getbukkit.org/craftbukkit/craftbukkit-1.7.2-R0.4-20140216.012104-3.jar");
		return("https://cdn.getbukkit.org/craftbukkit/craftbukkit-" + version + ".jar");
	}
	case 5: {// spigot
		// naming scheme changes on different versions of spigot and bukkit so I have to return a different URL for some versions
		if (version == "1.10.2" || version == "1.10" || version == "1.9.4" || version == "1.9.2" || version == "1.9" || version == "1.8.8" || version == "1.8.7" || version == "1.8.6" || version == "1.8.5" || version == "1.8.4" || version == "1.8.3" || version == "1.8") return("https://cdn.getbukkit.org/spigot/spigot-" + version + "-R0.1-SNAPSHOT-latest.jar");
		if (version == "1.7.10") return("https://cdn.getbukkit.org/spigot/spigot-1.7.10-SNAPSHOT-b1657.jar");
		if (version == "1.7.9") return("https://cdn.getbukkit.org/spigot/spigot-1.7.9-R0.2-SNAPSHOT.jar");
		if (version == "1.7.8") return("https://cdn.getbukkit.org/spigot/spigot-1.7.8-R0.1-SNAPSHOT.jar");
		if (version == "1.7.5") return("https://cdn.getbukkit.org/spigot/spigot-1.7.5-R0.1-SNAPSHOT-1387.jar");
		if (version == "1.7.2") return("https://cdn.getbukkit.org/spigot/spigot-1.7.2-R0.4-SNAPSHOT-1339.jar");
		return("https://cdn.getbukkit.org/spigot/spigot-" + version + ".jar");
	}
	case 6: { // paper
		return("https://papermc.io/api/v1/paper/" + version + "/latest/download");
	}
	}
}