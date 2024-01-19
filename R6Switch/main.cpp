#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

// Function to swap the content of two lines in a file
bool swapLines(const std::string& filePath, const std::string& lineA, const std::string& lineB) {
	std::ifstream inputFile(filePath);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open the file " << filePath << std::endl;
		return false;
	}

	std::string fileContents;
	std::string line;

	while (std::getline(inputFile, line)) {
		if (line == lineA) {
			line = lineB;
		}
		else if (line == lineB) {
			line = lineA;
		}
		fileContents += line + "\n";
	}

	inputFile.close();

	std::ofstream outputFile(filePath);
	if (!outputFile.is_open()) {
		std::cerr << "Error: Unable to open the file " << filePath << " for writing" << std::endl;
		return false;
	}

	outputFile << fileContents;
	outputFile.close();

	return true;
}

void lineStatus(const std::string& filePath) {
	std::ifstream file(filePath);
	std::string line;

	//std::cout << "DataCenterHint Lines:" << std::endl;
	while (std::getline(file, line)) {
		if (line.find("DataCenterHint=") != std::string::npos) {
			std::cout << line << std::endl;
			std::cout << "\n";
		}
	}
	file.close();
}

int main() {
	std::string filePath = "GameSettings.ini";
	std::string lineA = "DataCenterHint=default";
	std::string lineB = "DataCenterHint=playfab/uaenorth";

	std::cout << "Before Swap:" << std::endl;
	lineStatus(filePath);

	if (swapLines(filePath, lineA, lineB)) {
		std::cout << "After Swap:" << std::endl;
		lineStatus(filePath);
		std::cout << "Lines swapped in the file. Press Enter to exit." << std::endl;
	}
	else {
		std::cerr << "Failed to swap lines. Press Enter to exit." << std::endl;
	}

	// Pause and wait for Enter key press before exiting
	std::cin.get();

	return 0;
}
