#include <stdio.h>
#include <stdint.h>
int initial_permutation[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1,  58, 50, 42, 34, 26, 18,
    10, 2,  59, 51, 43, 35, 27,
    19, 11, 3,  60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7,  62, 54, 46, 38, 30, 22,
    14, 6,  61, 53, 45, 37, 29,
    21, 13, 5,  28, 20, 12, 4
};
int left_shifts[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};
int pc1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1,  58, 50, 42, 34, 26, 18,
    10, 2,  59, 51, 43, 35, 27,
    19, 11, 3,  60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7,  62, 54, 46, 38, 30, 22,
    14, 6,  61, 53, 45, 37, 29,
    21, 13, 5,  28, 20, 12, 4
};
int pc2[48] = {
    14, 17, 11, 24, 1,  5,
    3,  28, 15, 6,  21, 10,
    23, 19, 12, 4,  26, 8,
    16, 7,  27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};
uint32_t left_rotate(uint32_t value, int shift) {
    return ((value << shift) | (value >> (28 - shift))) & 0x0FFFFFFF;
}
void generate_subkeys(uint64_t key, uint64_t subkeys[16]) {
    uint32_t C = 0, D = 0;
    uint64_t permuted_key = 0;
    int i;
    for ( i = 0; i < 56; i++) {
        permuted_key |= ((key >> (64 - pc1[i])) & 1) << (55 - i);
    }
    C = (permuted_key >> 28) & 0x0FFFFFFF;
    D = permuted_key & 0x0FFFFFFF;
    for (i = 0; i < 16; i++) {
        C = left_rotate(C, left_shifts[i]);
        D = left_rotate(D, left_shifts[i]);
        uint64_t combined_key = ((uint64_t)C << 28) | D;
        uint64_t subkey = 0;
        int i,j;
        for (j = 0; j < 48; j++) {
            subkey |= ((combined_key >> (56 - pc2[j])) & 1) << (47 - j);
        }
        subkeys[i] = subkey;
    }
}
int main() {
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t subkeys[16];
    generate_subkeys(key, subkeys);
    int i;
    for (i = 0; i < 16; i++) {
        printf("Subkey %d: %012llX\n", i + 1, subkeys[i]);
    }
    return 0;
}
