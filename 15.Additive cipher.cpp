#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>?
#define ALPHABET_SIZE 26
#define NUM_TOP_PLAINTEXTS 10
void decrypt(char *ciphertext, int *keystream, int keystream_len, char *plaintext) {
    int i;
    int len = strlen(ciphertext);
    
    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {  
            int key = keystream[i % keystream_len];
            char decrypted_char = ciphertext[i] - key;
    
            if (islower(ciphertext[i]) && decrypted_char < 'a') {
                decrypted_char += ALPHABET_SIZE;
            }
            else if (isupper(ciphertext[i]) && decrypted_char < 'A') {
                decrypted_char += ALPHABET_SIZE;
            }
            
            plaintext[i] = decrypted_char;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[len] = '\0';
}
void calculate_letter_frequencies(char *plaintext, int *freq) {
    int i;
    int len = strlen(plaintext);
    
    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int index = tolower(plaintext[i]) - 'a';
            freq[index]++;
        }
    }
}
void find_top_plaintexts(char *ciphertext, int *keystream, int keystream_len, int num_top, char *top_plaintexts[]) {
    char plaintext[strlen(ciphertext) + 1];
    int freq[ALPHABET_SIZE] = {0};
    calculate_letter_frequencies(ciphertext, freq);
    for (int k = 0; k < ALPHABET_SIZE; k++) {
        decrypt(ciphertext, keystream, keystream_len, plaintext);
        
        calculate_letter_frequencies(plaintext, freq);
        
        if (k == 0 || freq[k] > freq[k - 1]) {
            strcpy(top_plaintexts[k], plaintext);
        }
        for (int i = 0; i < keystream_len; i++) {
            keystream[i] = (keystream[i] + 1) % ALPHABET_SIZE;
        }
    }
}

int main() {
    char ciphertext[] = "?Ô@;MÊÉ@^ÑJ^"; 
    int keystream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int keystream_len = sizeof(keystream) / sizeof(keystream[0]);
    
    char *top_plaintexts[NUM_TOP_PLAINTEXTS];
    for (int i = 0; i < NUM_TOP_PLAINTEXTS; i++) {
        top_plaintexts[i] = (char *) malloc(strlen(ciphertext) + 1);
    }
    
    find_top_plaintexts(ciphertext, keystream, keystream_len, NUM_TOP_PLAINTEXTS, top_plaintexts);
    
    printf("Top %d possible plaintexts:\n", NUM_TOP_PLAINTEXTS);
    for (int i = 0; i < NUM_TOP_PLAINTEXTS; i++) {
        printf("%d. %s\n", i + 1, top_plaintexts[i]);
        free(top_plaintexts[i]);
    }
    
    return 0;
}

