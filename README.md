## Implementa-o-RSA-sem-bibliotecas-externas
Implementação do algoritmo RSA em C sem utilização de bibliotecas externas. Foi implementado a struct big_int que é responsável por armazenar os números inteiros de grande magnitude, e as funções de multiplicação, divisão, exponenciação e geração de chaves. O programa irá gerar um par de chaves pública e privada, e irá criptografar e descriptografar uma mensagem. Para utilizar essa bilbioteca, basta incluir o arquivo `rsa.h` no seu código que está na pasta `src/rsa`.

## Compilação
Para compilar o programa, basta executar o comando `make` no terminal. Será gerado um arquivo executável chamado `rsa`.

```bash
$ make
```

## Execução
Para executar o programa, basta rodar o arquivo `rsa` no terminal com os argumentos necessários.

```bash
$ ./rsa <mensagem> <num-bits-chave>
```

A mensagem deve ser passada entre aspas duplas. O número de bits da chave deve ser um número inteiro pelo menos 64 e multiplo de 2. A mensagem também deve ser menor que o número de bits da chave, caso contrário, dará erro.

## Exemplo
```bash
$ ./rsa "Hello, World!" 128
```

O programa irá gerar dois números primos aleatórios, e quanto maior o número de bits da chave, maior será o tempo de execução. Após a geração das chaves, os atributos da chave gerada serão exibidos no terminal. A mensagem será criptografada e descriptografada, e o resultado será exibido no terminal.

## A melhorar
- Documentação do código e comentários
- Melhorar a eficiência do código nos cálculos de multiplicação e divisão
- Implementar a função de assinatura digital
- Implementar a função de verificação de assinatura digital

## Autores
- Vitor Taranto


Obs: Deu muito dor de cabeça fazer esse projeto, mas foi muito gratificante. Aprendi muito sobre criptografia e sobre a linguagem C.
