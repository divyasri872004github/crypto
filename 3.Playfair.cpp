#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define SIZE 5
void generateKeyTable(const char*key,char keyTable[SIZE][SIZE],int*positions){
    int i,j,k,index = 0;
    int used[26]={0};
    for(i=0;key[i]!='\0';i++){
        if(key[i]=='J') key[i]=='I';
        if(!used[key[i]-'A']){
            keyTable[index/SIZE][index%SIZE]=key[i];
            positions[key[i]-'A']=index;
            used[key[i]-'A']=1;
            index++;
        }
    }
    for(k=0;k<26;k++){
        if(k+'A'=='J') continue;
        if(!used[k]){
            keyTable[index/SIZE][index%SIZE]=k+'A';
            positions[k]=index;
            index++;
        }
    }
}
void preprocessText(char*text){
    int i,j=0;
    for(i=0;text[i]!='\0';i++){
        if(isalpha(text[i])){
            text[j++]=toupper(text[i]=='J'?'I':text[i]);
        }
    }
    text[j] = '\0';
    for (i = 0; i < j; i += 2){
        if (text[i] == text[i + 1]){
            for (int k = j; k > i; k--){
                text[k] = text[k - 1];
            }
            text[i + 1] = 'X';
            j++;
        }
    }
    if (j % 2 != 0){
        text[j++] = 'X';
    }
    text[j] = '\0';
}
void playfairEncrypt(const char* plaintext, char* ciphertext, const char keyTable[SIZE][SIZE], const int* positions){
    int i, a, b, a_row, a_col, b_row, b_col;
    for (i = 0; plaintext[i] != '\0' && plaintext[i + 1] != '\0'; i += 2){
        a = plaintext[i] - 'A';
        b = plaintext[i + 1] - 'A';
        a_row = positions[a] / SIZE;
        a_col = positions[a] % SIZE;
        b_row = positions[b] / SIZE;
        b_col = positions[b] % SIZE;
        if (a_row == b_row){
            ciphertext[i] = keyTable[a_row][(a_col + 1) % SIZE];
            ciphertext[i + 1] = keyTable[b_row][(b_col + 1) % SIZE];
        } 
		else if (a_col == b_col){
            ciphertext[i] = keyTable[(a_row + 1) % SIZE][a_col];
            ciphertext[i + 1] = keyTable[(b_row + 1) % SIZE][b_col];
        } 
		else{
            ciphertext[i] = keyTable[a_row][b_col];
            ciphertext[i + 1] = keyTable[b_row][a_col];
        }
    }
    ciphertext[i] = '\0';
}
int main(){
    char key[100], plaintext[100], ciphertext[100];
    char keyTable[SIZE][SIZE];
    int positions[26];
    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    generateKeyTable(key, keyTable, positions);
    printf("Key Table:\n");
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%c ", keyTable[i][j]);
        }
        printf("\n");
    }
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    preprocessText(plaintext);
    playfairEncrypt(plaintext, ciphertext, keyTable, positions);
    printf("Encrypted text: %s\n", ciphertext);
    return 0;
}
