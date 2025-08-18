
#include <iostream>

#include "args.h"
#include "parser.h"
#include "reader.h"


int main(int argc, char *argv[]) {
	int file_index = parse_args(argc, argv);

	std::vector<std::string> program;
	if (file_index == -1) {
		program = get_assembly_from_stdin();
	} else {
		program = get_assembly_from_file(argv[file_index]);
	}

	std::unordered_map<std::string, int> labels = preprocess(program);
	for (size_t ip = 0; ip < program.size(); ip++) {
		std::string line = program[ip];

		if (line.empty() || line.find(':') != std::string::npos)
			continue;

		std::vector<std::string> tokens = tokenizer(line);
		std::string opcode = tokens[0];
		std::vector<std::string> operand;
		for (size_t i = 1; i < tokens.size(); i++) {
			operand.push_back(tokens[i]);
		}
	}
}
