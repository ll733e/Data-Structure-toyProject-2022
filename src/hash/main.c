#include "KISA_SHA256.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    //unsigned char buffer[1024] = { 0, };
    unsigned char result[32] = { 0, };
    unsigned int len = 0;
    int i = 0;

    //scanf("%s", buffer);

    len = strlen(argv[1]);
    SHA256_Encrpyt(argv[1], len, result);

    for (i = 0; i < 32; i++)
        printf("%02x", result[i]);
    puts("");
    return 0;
}