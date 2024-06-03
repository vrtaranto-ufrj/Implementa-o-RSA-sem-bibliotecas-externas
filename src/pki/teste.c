#include <stdint.h>
#include <stdio.h>

#include "modarit.h"

uint64_t ipow(uint64_t base, uint64_t expoente) {
	uint64_t resultado = 1;
	for (uint64_t i = 0; i < expoente; i++) {
		resultado *= base;
	}
	return resultado;
}

int main(int argc, char *argv[]) {
	uint64_t base, expoente, modulo, resultado;

	base = 27;
	expoente = 40;
	modulo = 57;
	
	resultado = powMod(base, expoente, modulo);
	printf("%lu\n", resultado);

	resultado = ipow(base, expoente) % modulo;
	printf("%lu\n", resultado);

	
} 
