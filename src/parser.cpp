#include "parser.h"

#include <sstream>

#include "virtual_cpu.h"


std::vector<std::string> tokenizer(const std::string& line) {
	std::stringstream ss(line);
	std::string token;
	std::vector<std::string> tokens;
	while (ss >> token) {
		if (!token.empty() && token.back() == ',') {
			token.pop_back();
		}
		tokens.push_back(token);
	}
	return tokens;
}

std::unordered_map<std::string, int> preprocess(
    const std::vector<std::string>& program) {

	std::unordered_map<std::string, int> labels;

	for (size_t i = 0; i < program.size(); ++i) {
		std::string line = program[i];
		if (line.empty())
			continue;
		auto colon_pos = line.find(':');
		if (colon_pos != std::string::npos) {
			std::string label = line.substr(0, colon_pos);
			labels[label] = i;
		}
	}
	return labels;
}