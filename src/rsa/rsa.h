#pragma once

#include <stdint.h>

typedef struct structRsa Rsa;

typedef struct structpublicKey publicKey;

// Construtor e destrutores
Rsa * criarKeys(uint32_t numero_bits);
void freeRsa(Rsa *rsa);
void freePubKey(publicKey *pubKey);
void freeCipher(unsigned char *cipher);

publicKey * getPubKey(Rsa *rsa);
unsigned char * encrypt(unsigned char *message, Rsa *rsa);
unsigned char * decrypt(unsigned char *cipher, Rsa *rsa);