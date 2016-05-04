#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <stdbool.h>

void process_file(char *filename, bool l_flag, bool w_flag, bool c_flag) {
	FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("No such file or directory: '%s'\n", filename);
		exit(EXIT_FAILURE);
	}
	
	if(l_flag) {
		int l_counter = 0;
		char buffer[1000];
		while(fgets(buffer, 1000, fp) != NULL) {
			l_counter++;
		}
		printf("%d ", l_counter);
	}
	if(w_flag) {
		rewind(fp);
		int w_counter = 0;
		char word[100];
		while(fscanf(fp, "%100s", word) != EOF) {
			w_counter++;
		}
		printf("%d ", w_counter);
	}
	if(c_flag) {
		rewind(fp);
		int c_counter = 0;
		while(fgetc(fp) != EOF) {
			c_counter++;
		}
		printf("%d ", c_counter);
	}
	printf("%s\n", filename);
	
	fclose(fp);
}

void compile_regex(regex_t *restrict regex, char *pattern) {
	if(regcomp(regex, pattern, REG_ICASE | REG_EXTENDED) != 0) {
		printf("The regular expression could not be compiled.\n");
		exit(EXIT_FAILURE);
	}
}

void process_parameters(int argc, char *argv[]) {
	
	bool l_flag;
	bool w_flag;
	bool c_flag;
	if(argc > 2) {
		l_flag = false;
		w_flag = false;
		c_flag = false;
	} else {
		l_flag = true;
		w_flag = true;
		c_flag = true;
	}
	char *filename = NULL;
	
	regex_t regex_flag;
	compile_regex(&regex_flag, "^-.+$");
	regex_t regex_filename;
	compile_regex(&regex_filename, "^[a-zA-Z0-9_. -]+$");

	for(int i = 1; i < argc; i++) {
		if(regexec(&regex_flag, argv[i], 0, NULL, 0) == 0) {
			for(int j = 1, len = strlen(argv[i]); j < len; j++) {
				switch(argv[i][j]) {
					case 'l':
						l_flag = true;
						break;
					case 'w':
						w_flag = true;
						break;
					case 'c':
						c_flag = true;
						break;
					default:
						printf("Invalid option: '-%c'\n", argv[i][j]);
						exit(EXIT_FAILURE);
				}
			}
		} else if(regexec(&regex_filename, argv[i], 0, NULL, 0) == 0) {
			if(filename == NULL) {
				filename = argv[i];
			} else {
				printf("The filename has already been specified. There is no support for more files in this version.\n");
				exit(EXIT_FAILURE);
			}
		} else {
			printf("Invalid argument: %s\n", argv[i]);
			exit(EXIT_FAILURE);
		}
	}
	
	regfree(&regex_flag);
	regfree(&regex_filename);
	
	
	process_file(filename, l_flag, w_flag, c_flag);
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Invalid usage. Arguments missing.\n");
		return 1;
	}
	
	process_parameters(argc, argv);


	return 0;
}
