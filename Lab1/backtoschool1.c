#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 26

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


int compar(const void * a, const void * b) {
	return *(int*)a - *(int*)b;
}


void build_ttable(const int ftable[], int ttable[]) {
	int tempTable[SIZE];
	
	memcpy(tempTable, ftable, SIZE * sizeof(int));
	
	qsort(tempTable, SIZE, sizeof(int), compar);
	
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			if(ftable[i] == tempTable[j]) {
				ttable[i] = j;
				tempTable[j] = -1;
				break;
			}
		}
	}
}

void encrypt(const int ttable[], char text[]) {
	for(int i = 0, len = strlen(text); i < len; i++) {
		if(isalpha(text[i])) {
			text[i] = ttable[toupper(text[i]) - 'A'] + 'A';
		}
	}
}

void decrypt(const int ttable[], char text[]) {
	for(int i = 0, len = strlen(text); i < len; i++) {
		if(isalpha(text[i])) {
			for(int j = 0; j < SIZE; j++) {
				if(toupper(text[i] - 'A') == ttable[j]) {
					text[i] = j + 'A';
					break;
				}
			}
		}
	}
}

int main() {
	int ftable[SIZE];
	
	build_ftable(ftable);
	
	
	
	int ttable[SIZE];
	
	build_ttable(ftable, ttable);
	
	char message[512];
	sprintf(message, "Jeden chudobny clovek mal od svojej prvej zeny jednu dceru.");
	encrypt(ttable, message);
	printf("%s\n", message);
	decrypt(ttable, message);
	printf("%s\n", message);


	return 0;
}
