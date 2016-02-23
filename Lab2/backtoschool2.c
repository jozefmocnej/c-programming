#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 26

typedef struct {
	char original;
	char translated;
} Letter;

void build_ftable(int ftable[]) {
	
	for(int i = 0; i < SIZE; i++) {
		ftable[i] = 0;
	}
	
	char c;
	do {
		c = getchar();
		if(isalpha(c)) {
			ftable[toupper(c) - 'A']++;
		}
	} while(c != EOF);

}


int compar(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}


void build_ttable(const int ftable[], Letter ttable[]) {
	int tempTable[SIZE];
	
	memcpy(tempTable, ftable, SIZE * sizeof(int));
	
	qsort(tempTable, SIZE, sizeof(int), compar);
	
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			if(ftable[i] == tempTable[j]) {
				ttable[i].original = i + 'A';
				ttable[i].translated = j + 'A';
				tempTable[j] = -1;
				break;
			}
		}
	}
	
}

char get_translated_letter(const Letter ttable[], char letter) {
	if(isalpha(letter)) {
/*		for(int i = 0; i < SIZE; i++) {*/
/*			if(ttable[i].original == toupper(letter)) {*/
/*				return ttable[i].translated;*/
/*			}*/
/*		}*/
		return ttable[toupper(letter) - 'A'].translated;
	}
	
	return letter;
}

char get_original_letter(const Letter ttable[], char letter) {
	if(isalpha(letter)) {
		for(int i = 0; i < SIZE; i++) {
			if(ttable[i].translated == toupper(letter)) {
				return ttable[i].original;
			}
		}
	}
	
	return letter;
}


void encrypt(const Letter ttable[], char text[]) {
	for(int i = 0, len = strlen(text); i < len; i++) {
		text[i] = get_translated_letter(ttable, text[i]);
	}
}

void decrypt(const Letter ttable[], char text[]) {
	for(int i = 0, len = strlen(text); i < len; i++) {
		text[i] = get_original_letter(ttable, text[i]);
	}
}

int main() {
	int ftable[SIZE];
	
	build_ftable(ftable);
	
	Letter ttable[SIZE];
	
	build_ttable(ftable, ttable);
	
	char message[512];
	sprintf(message, "Jeden chudobny clovek mal od svojej prvej zeny jednu dceru.");
	encrypt(ttable, message);
	printf("%s\n", message);
	decrypt(ttable, message);
	printf("%s\n", message);


	return 0;
}
