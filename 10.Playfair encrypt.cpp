#include <stdio.h>
#include <string.h>

int find_position(char key[5][5], char letter, int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (key[i][j] == letter) {
                *row = i;
                *col = j;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    char key[5][5] = { {'M', 'F', 'H', 'I', 'K'}, 
                       {'U', 'N', 'O', 'P', 'Q'},
                       {'Z', 'V', 'W', 'X', 'Y'}, 
                       {'E', 'L', 'A', 'R', 'G'},
                       {'D', 'S', 'T', 'B', 'C'} };
    
    char msg[] = "MUSTSEEYOUOVERCADOGANWESTCOMINGATONCE";
    char enc[100] = "";
    int len = strlen(msg), i, j, r1, c1, r2, c2;

    for (i = 0; i < len; i += 2) {
        if (msg[i] == msg[i + 1]) {
            memmove(&msg[i + 1], &msg[i], len - i);
            msg[i + 1] = 'X';
            len++;
        }
        if (i + 1 >= len) {
            msg[i + 1] = 'X';
            len++;
        }
        find_position(key, msg[i], &r1, &c1);
        find_position(key, msg[i + 1], &r2, &c2);
        
        if (r1 == r2) {
            enc[i] = key[r1][(c1 + 1) % 5];
            enc[i + 1] = key[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            enc[i] = key[(r1 + 1) % 5][c1];
            enc[i + 1] = key[(r2 + 1) % 5][c2];
        } else {
            enc[i] = key[r1][c2];
            enc[i + 1] = key[r2][c1];
        }
    }
    enc[len] = '\0'; 
    printf("Encrypted: %s\n", enc);
    return 0;
}
