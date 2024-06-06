#include "modarit.h"
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

uint64_t powMod(uint64_t base, uint64_t expoente, uint64_t modulo) {	
	uint64_t atual = base % modulo;
	uint64_t resultado = 1;
	uint64_t n = expoente;


	while (n > 0) {
		if (n & 1) {
			resultado = (resultado * atual) % modulo;
		}
		atual = (atual * atual) % modulo;
		n >>= 1;

		printf("atual = %lu\t\tn = 0x%016" PRIx64 "\t\tresultado = %lu\n", atual, n, resultado);
	}

	return resultado % modulo;
}

void bigPowMod(big_int *base, big_int *expoente, big_int *modulo, big_int *resposta) {
	big_int atual, resultado, n, auxiliar;
	size_t tamanho = base->nmemb;

	inicializar(&atual, tamanho);
	inicializar(&resultado, tamanho);
	inicializar(&n, tamanho);
	inicializar(&auxiliar, tamanho);
	

	dividir(base, modulo, &auxiliar, &atual);  // atual = base % modulo;

	atribuirValor(1, &resultado, 0);  // resultado = 1;

	copiar(&n, expoente);  // n = expoente;

	while (!eZero(&n)) {

		if (n.array[0] & 1) {
			multiplicar(&resultado, &atual, &auxiliar);
			dividir(&auxiliar, modulo, &auxiliar, &resultado);
		}
		multiplicar(&atual, &atual, &auxiliar);
		dividir(&auxiliar, modulo, &auxiliar, &atual);
		metade(&n);
	}
	dividir(&resultado, modulo, &auxiliar, resposta);

	freeInt(&atual);
	freeInt(&resultado);
	freeInt(&n);
	freeInt(&auxiliar);
}