def powMod(base, expoente, modulo):
	atual = base % modulo
	resultado = 1
	n = expoente
	print(f'atual = {hex(atual)}\tresultado = {hex(resultado)}\tn = {hex(n)}\n')

	while (n > 0):
		if (n & 1):
			print('IF')
			resultado = (resultado * atual) % modulo
		atual = (atual * atual) % modulo
		n >>= 1
		
		print(f'atual = {hex(atual)}\tresultado = {hex(resultado)}\tn = {hex(n)}\n')
	
	return resultado % modulo

print(hex(powMod(0x0000000000000000006d6f68616d6564, 0x00000000000000000000000000010001, 0x00003413e8c1b13785c6829093740e99)))