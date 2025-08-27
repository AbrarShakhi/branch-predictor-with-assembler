#include "args.h"

#include <string.h>

#include "miscs.h"


char *parse_args(const int argc, char *argv[])
{
	for (int i = 0; i < argc; i++) {
		if (strncmp(argv[i], "-i", 2) == 0) {
			if (i + 1 < argc) {
				return argv[i + 1];
			} else {
				missing_filename_error();
			}
		}
	}
	return NULL;
}
