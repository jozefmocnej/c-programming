#include <string.h>
#include "cipher.h"


void encrypt_text(const char *text, char *result) {
	int length = strlen(text);
	for(int i = 0; i < length; i++) {
		result[i] = (text[i] - 'A' + 5) % 26 + 'A';
	}
	result[length] = '\0';
}

void decrypt_text(const char *text, char *result) {
	int length = strlen(text);
	for(int i = 0; i < length; i++) {
		int num = text[i] - 5;
		if(num < 'A') {
			num = 'Z' - 'A' + num + 1;
		}
		result[i] = num;
	}
	result[length] = '\0';
}
