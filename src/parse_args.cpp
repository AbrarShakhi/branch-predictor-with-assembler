#include "../headers/parse_args.h"

#include <iostream>
#include <string>

int parse_args(const int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		if (std::string(argv[i]) == "-i") {
			if (i + 1 < argc) {
				return i + 1;
				break;
			} else {
				std::cout << "File name required!" << std::endl;
				exit(-1);
			}
		}
	}

	return -1;
}