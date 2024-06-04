#include "bigint.h"

#include <bits/floatn-common.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <sys/types.h>

typedef struct {
        uint64_t *array;
        size_t nmemb;

} big_int_ext;

void inicializar(big_int *bigInt, size_t nmemb) {
	if (nmemb == 0) {
		fprintf(stderr, "Tamanho deve ser maior que zero!\n");
		exit(EXIT_FAILURE);
	}
	bigInt->array = (int_usado*) calloc(nmemb, SIZE_INT);
	if (bigInt->array == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	bigInt->nmemb = nmemb;
}

void setZero(big_int *bigInt) {
	memset(bigInt->array, 0, bigInt->nmemb*SIZE_INT);
}

void inicializarExt(big_int_ext *bigInt, size_t nmemb) {
	if (nmemb == 0) {
		fprintf(stderr, "Tamanho deve ser maior que zero!\n");
		exit(EXIT_FAILURE);
	}
	bigInt->array = (uint64_t*) calloc(nmemb, sizeof(uint64_t));
	if (bigInt->array == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	bigInt->nmemb = nmemb;
}

void freeInt(big_int *bigInt) {
	free(bigInt->array);
}

void atribuirValor(int_usado inteiro, big_int *bigInt, size_t pos) {
	if (pos >= bigInt->nmemb) {
		fprintf(stderr, "Tentando acessar posição %zu. Número de elementos: %zu\n", pos, bigInt->nmemb);
		exit(EXIT_FAILURE);
	}
	
	bigInt->array[pos] = inteiro;
}

void printIntHexa(big_int *bigInt) {
	if (bigInt->nmemb == 0) return;
	
	printf("0x");
	if (sizeof(int_usado) == 8) {
		for (size_t i = bigInt->nmemb - 1;; i--) {
			printf("%016" PRIx64, (int64_t)bigInt->array[i]);
			if (i == 0) return;
		}
	} else if (sizeof(int_usado) == 4) {
		for (size_t i = bigInt->nmemb - 1;; i--) {
			printf("%08" PRIx32, (uint32_t)bigInt->array[i]);
			if (i == 0) return;
		}

	}
}

void copiar(big_int *int1, big_int *int2) {
	size_t tamanho;
	//tamanho = checaTamanho(int1, int2, int2);
	tamanho = int1->nmemb;
	memcpy(int1->array, int2->array, tamanho * SIZE_INT);
}

void copiarExt(big_int *int1, big_int_ext *int2) {
	size_t tamanho;
	tamanho = int1->nmemb;
	for (size_t i = 0; i < tamanho; i++) {
		int1->array[i] = int2->array[i];
	}
}

void incrementar1(big_int *bigInt) {
	big_int temp;
	
	inicializar(&temp, bigInt->nmemb);
	
	atribuirValor(1, &temp, 0);
	
	somar(bigInt, &temp, bigInt);

	freeInt(&temp);
}

void decrementar1(big_int *bigInt) {
	big_int temp;

	if (eZero(bigInt)) {
		fprintf(stderr, "Não é permitido negativos\n");
		exit(EXIT_FAILURE);
	}

	inicializar(&temp, bigInt->nmemb);
	
	atribuirValor(1, &temp, 0);
	
	subtrair(bigInt, &temp, bigInt);

	freeInt(&temp);
}

size_t checaTamanho(big_int *int1, big_int *int2, big_int *int3) {
	if (int1->nmemb != int2->nmemb || int1->nmemb != int3->nmemb) {
		fprintf(stderr, "Tamanhos distintos dos inteiros: %zu e %zu\n", int1->nmemb, int2->nmemb);
		exit(EXIT_FAILURE);
	}

	return int1->nmemb;
}

bool eZero(big_int *bigInt) {
	for (size_t i = 0; i < bigInt->nmemb; i++) {
		if (bigInt->array[i] != 0) return false;
	}
	return true;
}

bool eUm(big_int *bigInt) {
	if (bigInt->array[0] != 1) return false;
	for (size_t i = 1; i < bigInt->nmemb; i++) {
		if (bigInt->array[i] != 0) return false;
	}
	return true;
}

void inverter(big_int *bigInt) {
	for (size_t i = 0; i < bigInt->nmemb; i++) {
		bigInt->array[i] = ~bigInt->array[i];
	}
}

void complemento2(big_int *bigInt) {
	inverter(bigInt);
	incrementar1(bigInt);
}

void somar(big_int *int1, big_int *int2, big_int *resultado) { // esquisito o comportamento do builtin. migrar para o mesmo algoritmo de big_int_ext da multiplicao
	size_t tamanho;
	int_usado *a, *b, *r, c_in;
	big_int temp, tempA, tempB;
	
	tamanho = int1->nmemb;
	//tamanho = checaTamanho(int1, int2, resultado);

	inicializar(&temp, tamanho);
	inicializar(&tempA, tamanho);
	inicializar(&tempB, tamanho);

	copiar(&tempA, int1);
	copiar(&tempB, int2);
	
	a = tempA.array;
	b = tempB.array;
	r = temp.array;
	c_in = 0;
	
	for (size_t i = 0; i < tamanho; i++) {
		if (__builtin_add_overflow(a[i], c_in, &a[i])) {
			c_in = 1;
			r[i] = b[i];
		} else {
			if (__builtin_add_overflow(a[i], b[i], &r[i])) {
				c_in = 1;
			} else {
				c_in = 0;
			}
		}

	}
	copiar(resultado, &temp);
	freeInt(&temp);
	freeInt(&tempA);
	freeInt(&tempB);
}

void subtrair(big_int *int1, big_int *int2, big_int *resultado) {
	//checaTamanho(int1, int2, resultado);
	big_int temp;

	inicializar(&temp, int1->nmemb);
	copiar(&temp, int2);

	complemento2(&temp);

	somar(int1, &temp, resultado);

	freeInt(&temp);
}

void multiplicarSomando(big_int *int1, big_int *int2, big_int *resultado) {
	big_int contador, temp;
	size_t tamanho;

	tamanho = int1->nmemb;
	//tamanho = checaTamanho(int1, int2, resultado);
	
	inicializar(&contador, tamanho);
	inicializar(&temp, tamanho);

	copiar(&contador, int2);

	while (!eZero(&contador)) {
		somar(&temp, int1, &temp);
		decrementar1(&contador);
	}
	
	copiar(resultado, &temp);
	freeInt(&temp);
	freeInt(&contador);	
}

void multiplicarPalavra(big_int *int1, big_int *int2, big_int_ext *resultado, size_t pos_int2) {
	int_usado *a, *b, carry;
	uint64_t *r;


	a = int1->array;
	b = int2->array;
	r = resultado->array;
	carry = 0;

	for (size_t i = 0; i < int1->nmemb/2; i++) {
		r[pos_int2+i] += (uint64_t) a[i] * (uint64_t) b[pos_int2] + carry;
		//printf("r[%zu] = %016" PRIx64 "\n", i, r[pos_int2+i]);
		//carry = r[pos_int2+i] & 0xffffffff00000000;
		carry = r[pos_int2+i] >> 32;
		//printf("carry = %u\n", carry);
	}
	r[pos_int2+int1->nmemb/2] += carry;

}

void multiplicar(big_int *int1, big_int *int2, big_int *resultado) {
	big_int_ext temp;
	size_t tamanho;
	printf("Entrou!\n");
	printf("int1 = ");
	printIntHexa(int1);
	printf("\t");
	printf("int2 = ");
	printIntHexa(int2);
	printf("\t");
	printf("resultado = ");
	printIntHexa(int2);
	printf("\n");

	tamanho = int1->nmemb;

	inicializarExt(&temp, tamanho);

	for(size_t i = 0; i < tamanho/2; i++) {
		//printf("i = %zu\n", i);
		multiplicarPalavra(int1, int2, &temp, i);
	}

	copiarExt(resultado, &temp);
	freeInt((big_int*)&temp);
	printf("Saiu!\n");
	printf("int1 = ");
	printIntHexa(int1);
	printf("\t");
	printf("int2 = ");
	printIntHexa(int2);
	printf("\t");
	printf("resultado = ");
	printIntHexa(resultado);
	printf("\n");

}

void dividir(big_int *int1, big_int *int2, big_int *resultado, big_int *resto) {
	big_int temp, respostaBsearch, tempResultado;
	size_t tamanho;
	int_usado *dividendo;

	tamanho = int1->nmemb;

	inicializar(&temp, tamanho);
	inicializar(&respostaBsearch, tamanho);
	inicializar(&tempResultado, tamanho);


	dividendo = int1->array;


	for (size_t i = tamanho - 1;; i--) {
		atribuirValor(dividendo[i], &temp, 0);
		printf("temp = ");
		printIntHexa(&temp);
		printf("\n");
		printf("i = %zu\n", i);
		//if (!eZero(&temp)) return;
		
		printf("comparacao = %d\n", compara(&temp, int2));
		if (compara(&temp, int2) >= IGUAL) {  // Se for maior ou igual
			printf("MAIOR\n");
			shiftLeft(&tempResultado);

			printf("target = ");
			printIntHexa(&temp);
			printf("\t");
			printf("divisor = ");
			printIntHexa(int2);
			printf("\t");
			printf("tempResultado = ");
			printIntHexa(&tempResultado);
			printf("\t");
			printf("respostaBsearch = ");
			printIntHexa(&respostaBsearch);
			printf("\n");

			bsearchDiv(&temp, int2, &tempResultado, &respostaBsearch);

			printf("tempResultado = ");
			printIntHexa(&tempResultado);
			printf("\t");
			printf("respostaBsearch = ");
			printIntHexa(&respostaBsearch);
			printf("\n");

			subtrair(&temp, &respostaBsearch, &temp);
		}
		if (i == 0) break;
		shiftLeft(&temp);
	}
	copiar(resultado, &tempResultado);
	copiar(resto, &temp);
}

comparacao compara(big_int *int1, big_int *int2) {
	for (size_t i = int1->nmemb - 1;; i--) {
		if (int1->array[i] > int2->array[i]) {
			return MAIOR;
		} else if (int1->array[i] < int2->array[i]) {
			return MENOR;
		}
		if (i == 0) break;
	}
	return IGUAL;
}

void shiftLeft(big_int *bigInt) {
	for(size_t i = bigInt->nmemb - 2;; i--) {
		bigInt->array[i + 1] = bigInt->array[i];
		if (i == 0) break;
	}
	bigInt->array[0] = 0;
}

void dobrar(big_int *bigInt) {
	int_usado ultimo, temp;

	ultimo = 0;
	for(size_t i = 0; i < bigInt->nmemb; i++) {
		temp = (bigInt->array[i] & 0x80000000) >> 31;
		bigInt->array[i] = (bigInt->array[i] << 1) + ultimo;
		ultimo = temp;
	}
}

void metade(big_int*bigInt) {
	int_usado primeiro, temp;

	primeiro = 0;
	for(size_t i = bigInt->nmemb - 1;; i--) {
		temp = (bigInt->array[i] & 0x00000001) << 31;
		bigInt->array[i] = (bigInt->array[i] >> 1) + primeiro;
		primeiro = temp;
		if (i == 0) break;
	}

}

void bsearchDiv(big_int *target, big_int *divisor, big_int *index, big_int *resultado) {
	big_int valorMul, right, left, mid;
	//int_usado right, left, mid;
	size_t tamanho;
	comparacao c, left_comparado_right;

	tamanho = divisor->nmemb;
	inicializar(&valorMul, tamanho);
	inicializar(&right, tamanho);
	inicializar(&left, tamanho);
	inicializar(&mid, tamanho);

	atribuirValor(1, &right, 0);  //right = 1;
	
	copiar(&valorMul, divisor);
	c = compara(&valorMul, target);
	while (c == MENOR) {
		dobrar(&right);  //right *= 2;
		dobrar(&valorMul);
		c = compara(&valorMul, target);
	}
	
	if (c == IGUAL) {
		copiar(resultado, &valorMul);
		copiar(index, &right);
		freeInt(&mid);
		freeInt(&valorMul);
		freeInt(&left);
		freeInt(&right);
		
		return;
	}
	
	// left = right / 2;
	copiar(&left, &right);
	metade(&left);

	int i = 0;
	left_comparado_right = compara(&left, &right);
	while (left_comparado_right <= IGUAL) {

		//mid = left + (right - left) / 2;
		//subtrair(&right, &left, &mid);
		//metade(&mid);
		//somar(&left, &mid, &mid);

		// mid = (right + left) / 2;
		somar(&right, &left, &mid);
		metade(&mid);

		if (++i < 40)
			{printf("left = ");
			printIntHexa(&left);
			printf("\t");
			printf("right = ");
			printIntHexa(&right);
			printf("\t");
			printf("mid = ");
			printIntHexa(&mid);
			printf("\n");}


		multiplicar(divisor, &mid, &valorMul);

		if (i < 40)
			{
			printf("valorMul = ");
			printIntHexa(&valorMul);
			printf("\t");
			printf("target = ");
			printIntHexa(target);
			printf("\n");}

		c = compara(&valorMul, target);
		if (c == IGUAL) {
			copiar(index, &mid);
			copiar(resultado, &valorMul);

			freeInt(&mid);
			freeInt(&valorMul);
			freeInt(&left);
			freeInt(&right);
			return;
		} else if (c == MENOR) {
			if (i < 40)printf("Menor!\n");
			//left = mid + 1;
			incrementar1(&mid);
			copiar(&left, &mid);
			
		} else {
			if (i < 40)printf("Maior!\n");
			//right = mid - 1;
			decrementar1(&mid);
			copiar(&right, &mid);
			
		}
		left_comparado_right = compara(&left, &right);
	}
	copiar(index, &right);
	multiplicar(divisor, index, resultado);
	freeInt(&mid);
	freeInt(&valorMul);
	freeInt(&left);
	freeInt(&right);
}