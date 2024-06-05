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

'''def powMod(base, expoente, modulo):
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

print(hex(powMod(0x20, 0x47, 0xca1)))'''

def iterative_egcd(a, b):
    x0, x1 = 1, 0
    y0, y1 = 0, 1
    while b != 0:
        q = a // b  # Calcula o quociente
        temp_a = a  # Armazena valor antigo de a
        temp_b = b  # Armazena valor antigo de b
        a = temp_b  # Atualiza a
        b = temp_a % temp_b  # Atualiza b com o resto

        temp_x0 = x0  # Armazena valor antigo de x0
        x0 = x1  # Atualiza x0
        x1 = temp_x0 - q * x1  # Atualiza x1

        temp_y0 = y0  # Armazena valor antigo de y0
        y0 = y1  # Atualiza y0
        y1 = temp_y0 - q * y1  # Atualiza y1
        print(f'a = {hex(a)}, b = {hex(b)}, q = {hex(q)}, x0 = {hex(x0)}, temp_x0 = {hex(temp_x0)}, x1 = {hex(x1)}, y0 = {hex(y0)}, temp_y0 = {hex(temp_y0)}, y1 = {hex(y1)}')

    return a, x0, y0

def modinv(e, phi):
    g, x, y = iterative_egcd(e, phi)
    if g != 1:
        raise Exception('O inverso modular não existe')
    else:
        print(f'x = {hex(x)}, phi = {hex(phi)}, return = {hex(x % phi)}')
        return x % phi

e = 65537
phi = 0x00000f73c00ae48ccb059dd5026a49e78d99dad1e796d4ffa9327a86be5b2160

d = modinv(e, phi)
print(f'O valor de d é: {hex(d)}, e = {hex(e)}, phi = {hex(phi)}')
'''from sympy import isprime

# Números fornecidos
num1 = 0x00000000000000000000000000000000004900e452dc70c7b5b41b5f4f1b89a1
num2 = 0x00000000000000000000000000000000000b6302ec3c57ef31b7ea6d5331fbe3

# Verificação de primalidade
is_prime_num1 = isprime(num1)
is_prime_num2 = isprime(num2)

print(f"O número {hex(num1)} é primo? {is_prime_num1}")
print(f"O número {hex(num2)} é primo? {is_prime_num2}")
'''
