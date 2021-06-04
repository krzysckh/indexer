#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	const char* filein[argc];
	const char* css = "";
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

	if (to == 1 && strcmp(css, "")) {
		printf("fatal error: css file cannot be added to md output\n");
		return 1;
	}

	switch(to) {
		case 0:
			printf(
					"<!DOCTYPE html>\n"
					"<html>\n"
					"<head>\n"
					"<title> index </title>\n"
					"</head>\n"
					"<body>\n"
					"<h1> index </h1>\n"
			      );
			break;
		case 1:
			printf("# index\n\n");
			break;
	}

	for (int i = 0; i < hf; i++) {
		switch(to) {
			case 0:
				printf("<p> <a href=%s%s%s%s\n", filein[i], "> ", filein[i], " </a> </p>");
				break;
			case 1:
				printf("[%s%s%s%s\n\n", filein[i], "](", filein[i], ")");
				break;
		}
	}

	switch(to) {
		case 0:
			printf(
					"</body>\n"
					"</html>\n"
			      );
			break;
		case 1:
			break;
	}
		

	return 0;
}
