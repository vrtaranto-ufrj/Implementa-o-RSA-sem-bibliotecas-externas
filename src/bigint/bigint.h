#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>

#define int_usado uint32_t
#define SIZE_INT sizeof(int_usado)

typedef struct {
	int_usado *array;
	size_t nmemb;

} big_int;

typedef enum {
	MENOR = -1,
	IGUAL = 0,
	MAIOR = 1
} comparacao;

void inicializar(big_int *bigInt, size_t nmemb);
void setZero(big_int *bigInt);
void freeInt(big_int *bigInt);
void atribuirValor(int_usado inteiro, big_int *bigInt, size_t pos);
void printIntHexa(big_int *bigInt);
void copiar(big_int *int1, big_int *int2);
void incrementar1(big_int *bigInt);
void decrementar1(big_int *bigInt);
size_t checaTamanho(big_int *int1, big_int *int2, big_int *int3);
bool eZero(big_int *bigInt);
bool eUm(big_int *bigInt);
void inverter(big_int *bigInt);
void complemento2(big_int *bigInt);
void somar(big_int *int1, big_int *int2, big_int *resultado);
void subtrair(big_int *int1, big_int *int2, big_int *resultado);
void multiplicar(big_int *int1, big_int *int2, big_int *resultado);
void dividir(big_int *int1, big_int *int2, big_int *resultado, big_int *resto);
comparacao compara(big_int *int1, big_int *int2);
void shiftLeft(big_int *bigInt);
void dobrar(big_int *bigInt);
void metade(big_int*bigInt);
void bsearchDiv(big_int *target, big_int *divisor, big_int *index, big_int *resultado);
void potencia(big_int *base, int_usado expoente, big_int *resultado);
void bigPowMod(big_int *base, big_int *expoente, big_int *modulo, big_int *resposta);
bool ePar(big_int *bigInt);
void randInt(big_int *min, big_int *max, big_int *resposta);
void generate_random_bytes(big_int *n);