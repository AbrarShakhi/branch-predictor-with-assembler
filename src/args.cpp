#include "args.h"

#include <iostream>
#include <string>

void missing_filename_error() {
	std::cerr << "File name required!" << std::endl;
}

int parse_args(const int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		if (std::string(argv[i]) == "-i") {
			if (i + 1 < argc) {
				return i + 1;
				break;
			} else {
				missing_filename_error();
				exit(-1);
			}
		}
	}

	return -1;
}