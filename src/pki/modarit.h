#pragma once

#include "../bigint/bigint.h"

#include <stdint.h>

#define INT_SIZE sizeof(uint64_t) * 8

uint64_t powMod(uint64_t base, uint64_t expoente, uint64_t modulo);
void bigPowMod(big_int *base, big_int *expoente, big_int *modulo, big_int *resposta);