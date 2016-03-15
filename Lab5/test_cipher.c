#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "cipher.h"

void test_encrypt_text() {
	printf("Encrypting const string...\n");

	char *text = "HELLO";
	char result[20];
	encrypt_text(text, result);
	assert(strcmp(result, "MJQQT") == 0);
	
	printf("Passed.\n");
	
	printf("Encrypting a set of strings...\n");

	const char words[10][10] = {"SEPTEMBER","THOUSAND","CASSOVIA","NEPAL","EVEREST","CAESAR","ZONE","YES","ANDERSON","KEY"};
const char en_words[10][10] = {"XJUYJRGJW","YMTZXFSI","HFXXTANF","SJUFQ","JAJWJXY","HFJXFW","ETSJ","DJX","FSIJWXTS","PJD"};

	for(int i = 0, size = sizeof(words)/sizeof(words[0]); i < size; i++) {
		encrypt_text(words[i], result);\
		assert(strcmp(result, en_words[i]) == 0);
	}

	printf("Passed.\n");
}

void test_decrypt_text() {
	printf("Decrypting const string...\n");

	char *text = "MJQQT";
	char result[20];
	decrypt_text(text, result);
	assert(strcmp(result, "HELLO") == 0);
	
	printf("Passed.\n");
	
	
	printf("Decrypting a set of strings...\n");

	const char words[10][10] = {"SEPTEMBER","THOUSAND","CASSOVIA","NEPAL","EVEREST","CAESAR","ZONE","YES","ANDERSON","KEY"};
const char en_words[10][10] = {"XJUYJRGJW","YMTZXFSI","HFXXTANF","SJUFQ","JAJWJXY","HFJXFW","ETSJ","DJX","FSIJWXTS","PJD"};

	for(int i = 0, size = sizeof(words)/sizeof(words[0]); i < size; i++) {
		decrypt_text(en_words[i], result);\
		assert(strcmp(result, words[i]) == 0);
	}

	printf("Passed.\n");
}

int main() {
	printf("Tests have started...\n");
	
	test_encrypt_text();
	
	test_decrypt_text();
	
	printf("All tests passed.\n");
}
