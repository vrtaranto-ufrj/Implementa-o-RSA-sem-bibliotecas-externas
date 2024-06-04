#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "modarit.h"

#define BITS 128
#define NUM_INTS 4

#define NMEMB BITS/(SIZE_INT*8)

uint64_t ipow(uint64_t base, uint64_t expoente) {
	uint64_t resultado = 1;
	for (uint64_t i = 0; i < expoente; i++) {
		resultado *= base;
	}
	return resultado;
}

int main(void) {
	/*uint64_t base, expoente, modulo, resultado;

	base = 27;
	expoente = 40;
	modulo = 57;
	
	resultado = powMod(base, expoente, modulo);
	printf("%lu\n", resultado);

	resultado = ipow(base, expoente) % modulo;
	printf("%lu\n", resultado);*/

	big_int inteiros[NUM_INTS];
		
	for (size_t i = 0; i < NUM_INTS; i++) {
		inicializar(&inteiros[i], NMEMB);
	}

	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < NMEMB/2; j++) {
			if (j >= NMEMB/4) {
				if (i == 0) {
					atribuirValor(rand(), &inteiros[i], j);
				} else {
					atribuirValor(0, &inteiros[i], j);
				}
				
			} else {
				atribuirValor(rand(), &inteiros[i], j);
			}
			
		}
	}

	printf("base = ");
	printIntHexa(&inteiros[0]);
	printf("\n");
	printf("expoente = ");
	printIntHexa(&inteiros[1]);
	printf("\n");
	printf("modulo = ");
	printIntHexa(&inteiros[2]);
	printf("\n");


	bigPowMod(&inteiros[0], &inteiros[1], &inteiros[2], &inteiros[3]);

	
	printf("resposta = ");
	printIntHexa(&inteiros[3]);
	printf("\n");


	
} 
