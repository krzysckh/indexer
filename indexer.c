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
	const char *filein[argc];
	const char *css = "", *linkcss = "", *title = "index";
	int to = 0;
	
	/*
	 * to == 0 	-	html
	 * to == 1	-	md
	 * to == 2	-	upup B)
	 */

	int hf = 0;

	int i = 1;
	/* wow that's a real bad piece of code to takie arguments from argv[]. really sorry for that */

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
			printf("indexer [arguments] <files>\n");
			return 0;
		} else if (strcmp(argv[i], "-T") == 0) {
			if (argv[i+1] != NULL) {
				if (strcmp(argv[i+1], "md") == 0) {
					to = 1;
					i++;
				} else if (strcmp(argv[i+1], "html") == 0) {
					to = 0;
					i++;
				} else if (strcmp(argv[i+1], "upup") == 0) {
					to = 2;
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
		} else if (strcmp(argv[i], "-t") == 0) {
			if (argv[i+1] != NULL) {
				title = argv[i+1];
				i++;
			} else {
				fprintf(stderr, "fatal error while parsing arguments: expected string after %s\n", argv[i]);
				return 1;
			}
		} else if (strcmp(argv[i], "-l") == 0) {
			if (argv[i+1] != NULL) {
				linkcss = argv[i+1];
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

	switch(to) {
		case 0:
			printf(
					"<!DOCTYPE html>\n"
					"<html>\n"
					"<head>\n"
					"<title> %s </title>\n"
					"<meta charset=\"UTF-8\">\n"
					"<style>\n",
					title
			      );
			if (strcmp(css, "")) {
					FILE *cssf;
					cssf = fopen(css, "r");
					if (cssf == NULL) {
						fprintf(stdout, "file %s doesn't exist\n", css);
						return 1;
					}
	
					int c = 0;
	
					while (c != EOF) {
						if (c != 0) {
							printf("%c", c);
						}
						c = fgetc(cssf);
					}
				}
			printf("</style>\n");
			if (strcmp(linkcss, "")) {
				printf("<link rel=\"stylesheet\" href=\"%s\">\n", linkcss);
			}
			printf(
					"</head>\n"
					"<body>\n"
					"<h1> %s </h1>\n"
					"<ul>\n",
					title
			      );
			break;
		case 1:
			printf("# %s\n\n", title);
			break;
		case 2:
			printf("+%s\n", title);
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
			case 2:
				printf("&..[%s]\n", parentDir);
				break;
		}
	}

	for (int i = 0; i < hf; i++) {
		switch(to) {
			case 0:
				printf("<li> <a href=\"%s\"%s", filein[i], "> ");
				checkIfDir(filein[i]);
				printf("%s%s\n", filein[i], " </a> </li>");
				break;
			case 1:
				printf("[");
				checkIfDir(filein[i]);
				printf("%s%s%s%s\n\n", filein[i], "](", filein[i], ")");
				break;
			case 2:
				printf("\\- &%s[", filein[i]);
				checkIfDir(filein[i]);
				printf("%s]\n", filein[i]);
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
		case 2:
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
