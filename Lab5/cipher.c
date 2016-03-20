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
        result[i] = (text[i] - 'A' + 26 - 5) % 26 + 'A';
	}
	result[length] = '\0';
}
