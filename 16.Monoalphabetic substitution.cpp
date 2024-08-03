#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define NUM_TOP_PLAINTEXTS 10

float english_freq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};
void decrypt(char *ciphertext, char *key, char *plaintext) {
    int i;
    int len = strlen(ciphertext);
    
    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {  
            plaintext[i] = key[tolower(ciphertext[i]) - 'a'];
        } else {
            plaintext[i] = ciphertext[i];  
        }
    }
    plaintext[len] = '\0';
}
void calculate_letter_frequencies(char *plaintext, float *freq) {
    int i, total_letters = 0;
    int len = strlen(plaintext);
    
    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int index = tolower(plaintext[i]) - 'a';
            freq[index]++;
            total_letters++;
        }
    }
    for (i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (freq[i] / total_letters) * 100.0;
    }
}
float calculate_score(float *plaintext_freq) {
    float score = 0.0;
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += english_freq[i] * plaintext_freq[i];
    }
    
    return score;
}
void find_top_plaintexts(char *ciphertext, char *top_plaintexts[]) {
    char key[ALPHABET_SIZE + 1]; 
    char plaintext[strlen(ciphertext) + 1];
    float freq[ALPHABET_SIZE];
    float plaintext_freq[ALPHABET_SIZE];
    float score;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = 'a' + i;
    }
    key[ALPHABET_SIZE] = '\0';
    
    calculate_letter_frequencies(ciphertext, freq);
    
    for (int k = 0; k < ALPHABET_SIZE; k++) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            key[i] = 'a' + (key[i] - 'a' + 1) % ALPHABET_SIZE;
        }
        decrypt(ciphertext, key, plaintext);
        calculate_letter_frequencies(plaintext, plaintext_freq);
        score = calculate_score(plaintext_freq);
        int j;
        for (j = NUM_TOP_PLAINTEXTS - 1; j >= 0; j--) {
            if (j > 0 && score > calculate_score(plaintext_freq)) {
                strcpy(top_plaintexts[j], top_plaintexts[j - 1]);
            } else {
                break;
            }
        }
        strcpy(top_plaintexts[j], plaintext);
    }
}
int main() {
    char ciphertext[] = "?‘@;M …@^—J^"; 
    char *top_plaintexts[NUM_TOP_PLAINTEXTS];
    for (int i = 0; i < NUM_TOP_PLAINTEXTS; i++) {
        top_plaintexts[i] = (char *) malloc(strlen(ciphertext) + 1);
    }
    
    find_top_plaintexts(ciphertext, top_plaintexts);
    
    printf("Top %d possible plaintexts:\n", NUM_TOP_PLAINTEXTS);
    for (int i = 0; i < NUM_TOP_PLAINTEXTS; i++) {
        printf("%d. %s\n", i + 1, top_plaintexts[i]);
        free(top_plaintexts[i]);
    }
    
    return 0;
}

