#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	const char* out;
	const char* filein[argc];
	const char* css;
	int to = 0;
	
	/*
	 * to == 0 	-	html
	 * to == 1	-	md
	 *
	 */

	int hf = 0;

	int i = 1;
	while (i < argc) {
	if (strcmp(argv[i], "--css") == 0) {
			if (argv[i+1] != NULL) {
				css = argv[i+1];
				i++;
			} else {
				printf("fatal error while parsing arguments: expected argument after %s\n", argv[i]);
				return 1;
			}
		} else if (strcmp(argv[i], "--help") == 0) {
			printf(
					"indexer [--css] [--help] [-T md, html] dir/ file1 file2...\n"
			      );
			return 0;
		} else if (strcmp(argv[i], "-T") == 0) {
			if (argv[i+1] != NULL) {
				if (strcmp(argv[i+1], "md") == 0) {
					to = 1;
					i++;
				} else if (strcmp(argv[i+1], "html") == 0) {
					to = 0;
					i++;
				} else {
					printf("fatal error while parsing arguments: invalid argument after %s\n", argv[i]);
					return 1;
				}
			} else {
				printf("fatal error while parsing arguments: expected argument after %s\n", argv[i]);
				return 1;
			}
		} else {
			filein[hf] = argv[i];
			hf++;
		}
		i++;
	}


		

	return 0;
}
