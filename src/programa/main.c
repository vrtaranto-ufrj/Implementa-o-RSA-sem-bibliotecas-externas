#include "../rsa/rsa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    Rsa *rsa;
    publicKey *pubKey;
    unsigned char *mensagem, *cifrado, *decriptado;

    unsigned int numero_bits;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s \"<mensagem>\" <num-bits-chave>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    numero_bits = (unsigned int) atoi(argv[2]);

    mensagem = (unsigned char*) malloc(strlen(argv[1]) + 1);
    if (mensagem == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy((char*) mensagem, argv[1]);

    printf("mensagem = %s\n", mensagem);

    printf("M = 0x");
    for (size_t i = 0; i < strlen((char*)mensagem) + 1; i++) {
        printf("%02x", mensagem[i]);
    }
    printf("\n");

    rsa = criarKeys(numero_bits);
    pubKey = getPubKey(rsa);
    cifrado = encrypt(mensagem, rsa);

    printf("\nC = 0x");
    for (size_t i = 0; i < numero_bits/8; i++)
        printf("%02x", cifrado[i]);
    printf("\n\n");

    decriptado = decrypt(cifrado, rsa);

    printf("D = 0x");
    for (size_t i = 0; i < strlen((char*)decriptado); i++)
        printf("%02x", decriptado[i]);
    printf("\n");
    printf("descriptografado = %s\n", decriptado);

    free(decriptado);
    free(cifrado);
    free(mensagem);

    freePubKey(pubKey);
    freeRsa(rsa);

    return 0;
}
