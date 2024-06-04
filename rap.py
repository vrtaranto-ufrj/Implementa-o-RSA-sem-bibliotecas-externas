'''import rsa                                                              # RSA é assimetrico
  
pubkey, privkey = rsa.newkeys(4096)                  #Geração de chaves 
  
print ("Critografia Assimetrica usando RSA\n")
str1 = input ("Digite Texto para Criptogrfia RSA: ")
  
enctexto = rsa.encrypt(str1.encode(),pubkey)        #Chave Pública Encriptar
dectexto = rsa.decrypt(enctexto, privkey).decode()  #Chave Privada p/ Abrir

print("\nString Original: ", str1, " Tamanho: ", len(str1))
print ("\nChave Pública: ", pubkey, " Tamanho: ", len(str(pubkey)))
print ("\nChave Privada: ", privkey, " Tamanho: ", len(str(privkey)))
print("\nTexto Criptografado: ", enctexto, " Tamanho: ", len(enctexto))  
print("\nTexto Descriptografado: ", dectexto)'''

def powMod(base, expoente, modulo):
	atual = base % modulo
	resultado = 1
	n = expoente


	while (n > 0):
		if (n & 1):
			resultado = (resultado * atual) % modulo
		atual = (atual * atual) % modulo
		n >>= 1
		
		print(f'atual = {hex(atual)}     n = {hex(n)}     resultado = {hex(resultado)}\n')
	
	return resultado % modulo

print(hex(powMod(0x20, 0x47, 0xca1)))