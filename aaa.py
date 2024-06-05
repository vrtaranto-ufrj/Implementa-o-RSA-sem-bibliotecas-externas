def powMod(base, expoente, modulo):
	atual = base % modulo
	resultado = 1
	n = expoente
	print(f'resultado = {hex(resultado)}\tatual = {hex(atual)}\tn = {hex(n)}\n')

	while (n > 0):
		if (n & 1):
			print('IF')
			resultado = (resultado * atual) % modulo
		atual = (atual * atual) % modulo
		n >>= 1
		
		print(f'resultado = {hex(resultado)}\tatual = {hex(atual)}\tn = {hex(n)}\n')
	
	return resultado % modulo

print(hex(powMod(0x006d6f68616d6564, 0x0000000000010001, 0x0083658f4039b305)))