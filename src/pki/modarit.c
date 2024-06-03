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
