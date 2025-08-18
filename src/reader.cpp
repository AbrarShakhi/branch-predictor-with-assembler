#include "reader.h"

#include <fstream>
#include <iostream>


std::vector<std::string> get_assembly_from_file(std::string file) {
	std::ifstream in(file);
	if (!in) {
		std::cout << "Could not open: " << file << "\n";
		exit(-1);
	}
	std::vector<std::string> lines;
	lines.reserve(20);

	std::string line;
	while (std::getline(in, line)) {
		lines.emplace_back(line);
	}

	return lines;
}

std::vector<std::string> get_assembly_from_stdin() {
	std::vector<std::string> lines;
	std::string line;
	std::cout << "Write your assemply code here: (Enter empty line to finish)"
	          << std::endl;
	while (true) {
		if (!std::getline(std::cin, line) || line.empty()) {
			break;
		}
		lines.emplace_back(line);
	}

	return lines;
}