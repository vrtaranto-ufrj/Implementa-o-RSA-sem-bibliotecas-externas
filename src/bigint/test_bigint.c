#include "bigint.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define BITS 256
#define NUM_INTS 3

#define NMEMB BITS/(SIZE_INT*8)

int main(void) {
	big_int inteiros[3];
		
	for (size_t i = 0; i < NUM_INTS; i++) {
		inicializar(&inteiros[i], NMEMB);
	}

	for (size_t i = 0; i < 2; i++) {
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
	
	printf("a = ");
	printIntHexa(&inteiros[0]);
	printf("\n");
	printf("b = ");
	printIntHexa(&inteiros[1]);
	printf("\n");
	//atribuirValor(0xffffffffffffffff, &int1, 0);
	//atribuirValor(0xffffffffffffffff, &int1, 1);
	//atribuirValor(0x0000000000000000, &int1, 2);
	//atribuirValor(0x0000000000000000, &int1, 3);
	
	//atribuirValor(0x0000000000ffffff, &int2, 0);	
	//atribuirValor(0x0000000000000000, &int2, 1);
	//atribuirValor(0x0000000000000000, &int2, 2);
	//atribuirValor(0x0000000000000000, &int2, 3);
	
	//somar(&int1, &int2, &int3);
	//subtrair(&int1, &int2, &int3);
	//multiplicar(&int1, &int2, &int3);
	//decrementar1(&int1);
	//somar(&inteiros[0], &inteiros[1], &inteiros[2]);
	//subtrair(&inteiros[0], &inteiros[1], &inteiros[2]);
	multiplicar(&inteiros[0], &inteiros[1], &inteiros[2]);
	//dividir(&inteiros[0], &inteiros[1], &inteiros[2], &inteiros[0]);
	//bsearchDiv(&inteiros[0], &inteiros[1], &inteiros[2], &inteiros[0]);
	
	printf("resultado = ");
	printIntHexa(&inteiros[2]);
	printf("\n");

	printf("resto = ");
	printIntHexa(&inteiros[0]);
	printf("\n");

	
	for (size_t i = 0; i < 3; i++) {
		freeInt(&inteiros[i]);
	}

	return 0;
}