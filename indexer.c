#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

typedef int bool;
#define true 1
#define false 0

void checkIfDir(const char* name);

char *file = "📝 ";
char *dir = "📁 ";
char *parentDir = "..";

bool showParentDir = false;

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
				fprintf(stderr, "fatal error while parsing arguments: expected argument after %s\n", argv[i]);
				return 1;
			}
		} else if (strcmp(argv[i], "--help") == 0) {
			printf(
					"synopsis:\n"
					"\tindexer [arguments] files\n"
					"\n"
					"flags:\n"
					"\t--css file\t\t-\tadds a single css file\n"
					"\t-T\t\t\t-\tsets output format. supported: md, html\n"
					"\t-d / --dir-emoji str\t-\tsets an emoji/str for directories\n"
					"\t-f / --file-emoji str\t-\tsets an emoji/str for files\n"
					"\t-p / --show-parent\t-\tshows \"..\"at the top of index (back to parent dir)\n"
					"\t--parent-emoji str\t-\tsets an emoji/str for <back to parent dir>\n"
					"\t--help\t\t\t-\tshows help end exits\n"
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
					fprintf(stderr, "fatal error while parsing arguments: invalid argument after %s\n", argv[i]);
					return 1;
				}
			} else {
				fprintf(stderr, "fatal error while parsing arguments: expected argument after %s\n", argv[i]);
				return 1;
			}
		} else if (strcmp(argv[i], "--dir-emoji") == 0 || strcmp(argv[i], "-d") == 0) {
			if (argv[i+1] != NULL) {
				dir = argv[i+1];
				i++;
			} else {
				fprintf(stderr, "fatal error while parsing arguments: expected string after %s\n", argv[i]);
				return 1;
			}
		} else if (strcmp(argv[i], "--file-emoji") == 0 || strcmp(argv[i], "-f") == 0) {
			if (argv[i+1] != NULL) {
				file = argv[i+1];
				i++;
			} else {
				fprintf(stderr, "fatal error while parsing arguments: expected string after %s\n", argv[i]);
				return 1;
			}
		} else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--show-parent") == 0) {
			showParentDir = true;
		} else if (strcmp(argv[i], "--parent-emoji") == 0) {
			if (argv[i+1] != NULL) {
				parentDir = argv[i+1];
				i++;
			} else {
				fprintf(stderr, "fatal error while parsing arguments: expected string after %s\n", argv[i]);
				return 1;
			}
		} else {
			filein[hf] = argv[i];
			hf++;
		}
		i++;
	}

	if (to == 1 && strcmp(css, "")) {
		fprintf(stderr, "fatal error: css file cannot be added to md output\n");
		return 1;
	}

	switch(to) {
		case 0:
			printf(
					"<!DOCTYPE html>\n"
					"<html>\n"
					"<head>\n"
					"<title> index </title>\n"
					"<meta charset=\"UTF-8\">\n"
					"<style>\n"
			      );
			if (strcmp(css, "")) {
					FILE *cssf;
					cssf = fopen(css, "r");
	
					int c = 0;
	
					while (c != EOF) {
						if (c != 0) {
							printf("%c", c);
						}
						c = fgetc(cssf);
					}
				}
			printf(
					"</style>\n"
					"</head>\n"
					"<body>\n"
					"<h1> index </h1>\n"
					"<ul>\n"
			      );
			break;
		case 1:
			printf("# index\n\n");
			break;
	}

	if (showParentDir) {
		switch(to) {
			case 0:
				printf("<li> <a href=\"..\"> %s </a> </li>\n", parentDir);
				break;
			case 1:
				printf("[%s](..)\n\n", parentDir);
				break;
		}
	}

	for (int i = 0; i < hf; i++) {
		switch(to) {
			case 0:
				printf("<li> <a href=\"%s%s\"", filein[i], "> ");
				checkIfDir(filein[i]);
				printf("%s%s\n", filein[i], " </a> </li>");
				break;
			case 1:
				printf("[");
				checkIfDir(filein[i]);
				printf("%s%s%s%s\n\n", filein[i], "](", filein[i], ")");
				break;
		}
	}

	switch(to) {
		case 0:
			printf(
					"</ul>\n"
					"</body>\n"
					"</html>\n"
			      );
			break;
		case 1:
			break;
	}
		

	return 0;
}

void checkIfDir(const char* name) {
	struct stat path_stat;
	stat(name, &path_stat);
	if(S_ISREG(path_stat.st_mode) == 0) {
		printf("%s", dir);
	} else {
		printf("%s", file);
	}
}
