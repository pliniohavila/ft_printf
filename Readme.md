# Um versão artesanal da função `printf`


Venho estudado um a linguagem C ultimamente e suas funções básicas que todo programador utiliza no dia a dia. 

Nesse sentido, resolvi entender e implementar um versão simplória da função `printf`. É bem simples, apenas para se ter uma noção de como é a sua implementação. Bem como, observar uma implementação prática dos macros `va_arg, va_copy, va_end, va_start`, que ja escrevi a respeito neste [texto](https://pliniohavila.hashnode.dev/introducao-aos-macros-vastart-vaarg-vaend-vacopy-na-linguagem-c). 

Também, como estudar sobre _dispatch tables_ recentemente, resolvi implementar no código da minha implementação.
Escrevi a respeito delas neste [texto](https://pliniohavila.hashnode.dev/estudos-de-c-breves-notas-sobre-dispatch-tables). 

Não vou entrar em detalhes sobre o funcionamento da função, `printf`. Mas basicamente, a função funciona da seguinte forma. 

Caso queira, tem a as seguintes referências para a compreensão desta função:

1. https://www.academia.edu/10297206/Secrets_of_printf
2. https://www.lix.polytechnique.fr/~liberti/public/computing/prog/c/C/FUNCTIONS/format.html
3. https://pt.wikipedia.org/wiki/Printf#:~:text=printf%20(print%20formatted)%20é%20um,comparação%20aos%20programas%20em%20C.
4. https://en.wikipedia.org/wiki/Printf

Ela tem recebe como primeiro argumento uma `string` de formatação, que é obrigatória, seguida, ou não, por uma lista de argumentos referentes aos dados que serão utilizado na construção da `string` que será impressa na tela. 

Por meio dela, é definido como a `string` final será impressa na tela, preenchida com os dados informados nos argumentos subsequentes. 

A construção dessa `string` se dá mediante utilização de especificadores de formatos presentes na `string` de formatação. Há também `flags`, que adiciona detalhes na formatação final. 

Esses especificadores define quais dados devem ser inseridos naquele local. São exemplos:

- `%d` para inteiros
- `%f` para para números decimais
- `%c` para para caracteres
- `%s` para `strings`

Uma observação. Podemos utilizar a função `printf` para imprimir apenas um `string` literal:
```c
printf("Hello, world!\n");
```

Uma vez chamada a função com os argumentos, iniciar-se-á a construção da `string` formatada. 

Essa atividade de dá da seguinte forma. 

A `string` de formatação é percorrida, uma vez encontrada um especificador de formato, faz-se uso dos macros `va_arg, va_copy, va_end, va_start` para acessar os dados do argumento respectivo, seguindo a ordem em que foram informados. 

![](https://upload.wikimedia.org/wikipedia/commons/thumb/2/2c/Printf.svg/1920px-Printf.svg.png)

Em resumo rápido, assim é o funcionamento da função `printf`.

## Implementação 

O artigo será estruturado da seguinte forma 

[Apresentar os tipos e os protótipos das funções]

[explicar cada função]

[mostrar o código completo]

# Repositório 

https://github.com/pliniohavila/ft_printf 

# Referências

- https://pliniohavila.hashnode.dev/introducao-aos-macros-vastart-vaarg-vaend-vacopy-na-linguagem-c
- https://pliniohavila.hashnode.dev/estudos-de-c-breves-notas-sobre-dispatch-tables