#include "rsa.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Rsa *rsa;
    publicKey *pubKey;
    unsigned char mensagem[] = "mohamed";
    size_t bits = 256;

    unsigned char *cipher, *decriptado;
    
    printf("M = %s\n", mensagem);
    
    
    printf("M = 0x");
    for (size_t i = 0; i < 3; i++) {
        printf("%02x", mensagem[i]);
    }
    printf("\n");
    
    rsa = criarKeys(bits);
    pubKey = getPubKey(rsa);
    cipher = encrypt(mensagem, rsa);
    
    printf("C = 0x");
    for (size_t i = 0; i < bits/8; i++)
        printf("%02x", cipher[i]);
    printf("\n");

    decriptado = decrypt(cipher, rsa);

    printf("M = 0x");
    for (size_t i = 0; i < 8; i++)
        printf("%02x", decriptado[i]);
    printf("\n");
    printf("M = %s\n", decriptado);

    free(decriptado);
    free(cipher);

    freePubKey(pubKey);
    freeRsa(rsa);
}