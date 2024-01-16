# Um versão artesanal da função `printf`


Venho estudado a linguagem C ultimamente e suas funções básicas que todo programador utiliza no dia a dia. 

De grosso modo, achei PDFS da Escola 42 no Github e venho praticando os exercícios propostos. 

Nesse sentido, resolvi entender e implementar um versão simplória da função `printf`. É bem simples, apenas para se ter uma noção de como é a sua implementação. Bem como, observar uma implementação prática dos macros `va_arg, va_copy, va_end, va_start`, que ja escrevi a respeito neste [texto](https://pliniohavila.hashnode.dev/introducao-aos-macros-vastart-vaarg-vaend-vacopy-na-linguagem-c). 

Também, implementar _dispatch tables_, as quais estudei recentemente e resolvi implementar no código da minha implementação.
Escrevi a respeito delas neste [texto](https://pliniohavila.hashnode.dev/estudos-de-c-breves-notas-sobre-dispatch-tables). 

Não vou entrar em detalhes sobre o funcionamento da função, `printf`. Mas basicamente, a função funciona da seguinte forma. 

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

Caso queira, tem as seguintes referências para a compreensão desta função:

1. https://www.academia.edu/10297206/Secrets_of_printf
2. https://www.lix.polytechnique.fr/~liberti/public/computing/prog/c/C/FUNCTIONS/format.html
3. https://pt.wikipedia.org/wiki/Printf#:~:text=printf%20(print%20formatted)%20é%20um,comparação%20aos%20programas%20em%20C.
4. https://en.wikipedia.org/wiki/Printf

# Implementação 

Bem, feita essas considerações, vamos agora conhecer a minha versão de estudos escrita. 

Dois novos tipos são definidos: `fptr` e `spec_opt`. O primeiro, trata-se de um tipo de uma função, que recebe um ponteiro `va_list` e retorna um inteiro. O segundo, `spec_opt`, é uma estrutura cujos membros são um `char` e um `fptr`. 

Estes tipos são necessários para a implementação da _dispatch table_, a qual será explicada linhas abaixo. 

Temos a função `ft_printf` e suas funções auxiliares: `get_spec_func` e `count_digits_in_base`. Por vim, as funções responsáveis por imprimir os valores a depender do seu tipo. 

```c
// file ft_printf.h
typedef int     (*fptr) (va_list);
typedef struct  spec_opt
{
    char        spec;
    fptr        spec_func;
}               SPEC_OPT;

int     ft_printf(const char *fmt, ...);
// Funções auxiliares 
fptr    get_spec_func(char spec);
int     count_digits_in_base(int, int);
// Funções de impressão 
int     print_converted_n(int, int);
int     print_int(va_list);  
int     print_char(va_list); 
int     print_str(va_list);  
int     print_float(va_list);  
int     print_octal(va_list);  
int     print_hex(va_list);
int     print_pointer(va_list);
```

# Funções

Segue abaixo, uma explicação sobre as funções escritas para a implementação desta minha simple versão da função `printf`. 

### int ft_printf(const char *fmt, ...)

Esta é função por imprimir a `string`, seja ela, literal ou a ser formatada com os valores informados. 

Inicialmente, ela faz uma verificação da `string fmt`, caso ela não seja nula, incia-se um _loop_ para a impressão do conteúdo da `string`, bem como a inserção e impressão dos valores dos argumentos, a depender dos especificadores  de formato. 
Caso, encontre o caractere `%`, o fluxo de execução passa para dentro de contexto da condicional. Há outra condicional que verifica se o próximo caractere é um `%`, caso for, imprime-o e segue o fluxo do _loop_ para o próximo elemento da `string fmt`. 
Agora, caso o elemento subsequente ao `%` não for, também, um `%`, o fluxo, segue para o próximo contexto alternativo: _else_. 
Nesse, é realizada uma chamada à função `get_spec_func()`, passando o caractere subsequente ao `%`, que nesse caso é especificador de formato. Com base nele, a função retorna um ponteiro para função responsável por imprimir dados do tipo relativo ao especificador, ou nulo, caso não haja uma função para o especificador informado. 

Se for caso de um retorno nulo da função `get_spec_func`, a execução da aplicação é interrompida e `-1` é retornado.

Ressaltando que a cada impressão de um caractere, é incrementado o valor da variável `count_printed`, que retorna este valor ao final da execução.

Segue o código da função:

```c
int     ft_printf(const char *fmt, ...)
{
    int     i;
    int     count_printed;
    fptr    print_func;
    va_list argptr;

    i = 0; 
    count_printed = 0;
    if (fmt == NULL && (fmt[i] == '%' && fmt[i+1] == '\0'))
        return (-1);
    va_start(argptr, fmt);
    while (fmt[i] != '\0')
    {
        print_func = NULL;
        if (fmt[i] == '%')
        {
            if (fmt[i + 1] == '%')
            {
                i++; 
                ft_putchar(fmt[i]);       
            }
            else 
            {
                print_func = get_spec_func(fmt[i + 1]);
                if (!print_func)
                    return (-1);
                count_printed += print_func(argptr);
                i++; 
            }
        }
        else 
        {
            ft_putchar(fmt[i]);
        }
        i++;
        count_printed++;
    }
    va_end(argptr);
    return (count_printed);
}
```

### fptr get_spec_func(char spec)

Esta função é responsável por retornar um ponteiro para uma função relativa ao especificado de conteúdo informado.
Temos aqui a implementação de uma _dispatch table_, que retorna ponteiros de funções.
Sua implementação é simples. Temos um vetor composto de estruturas `SPEC_OPT`, cujo cada elemento de cada estrutura é um caractere o ponteiro para a sua função respectiva.

Após, temos um _loop_ responsável procurar o ponteiro da função desejada, ou retornar `NULL`, caso não encontre.

```c
fptr    get_spec_func(char spec)
{
    int         i;
    SPEC_OPT    spec_opts[7] = {
        {'d', print_int}, 
        {'c', print_char}, 
        {'s', print_str}, 
        {'f', print_float}, 
        {'o', print_octal}, 
        {'x', print_hex}, 
        {'p', print_pointer}, 
    }; 

    i = 0;
    while (i < 7)
    {
        if (spec == spec_opts[i].spec)
            return (spec_opts[i].spec_func);
        i++;
    }   
    return (NULL);
}
```

### int count_digits_in_base(int, int);

Outra função auxiliar. Esta é mais simples. Sua única responsabilidade é retornar a quantidade de dígitos de dado número em dada base. 

```c
int     count_digits_in_base(int nbr, int base)
{
    int     count;

    count = 0;
    if (nbr == 0)
        return ++count;
    if (nbr < 0)
        nbr *= (-1);
    while (nbr != 0)
    {
        count++;
        nbr /= base;
    }
    return (count);
}
```

### Funções de impressão

Estas função são responsáveis por imprimir, em formato de `string`, o conteúdo dos argumentos informados. São implementações simples, mais como prova de conceito mesmo, a exemplo, são as funções `print_hex()` e `print_float`. 

Recebem como argumento um ponteiro `va_list`, de onde recuperam os respectivos valores.

E retornam um inteiro cujo valor é a quantidade de caracteres impressos. 

```c
int     print_int(va_list argptr)
{
    int     n;

    n = va_arg(argptr, int);
    return print_converted_n(n, 10);
}

int     print_char(va_list argptr)
{
    char    c;

    c = (char)va_arg(argptr, int);
    ft_putchar(c);
    return (1);
}

int     print_str(va_list argptr)
{
    int     len;
    char    *str;

    str = va_arg(argptr, char*);
    len = ft_strlen(str);
    if ((len == 0) || (!str))
    {
        ft_putstr("(null)");
        return (6);
    }
    ft_putstr(str);
    return (len);
}

// // Handle only float numbers with numbers which has two precision numbers
// // This function is POV 
int     print_float(va_list argptr)
{
    int     aux;
    int     len;
    int     p_int;
    int     p_dec;
    double  f;

    f = va_arg(argptr, double);
    len = 0;
    if (f < 0)
    {
        f *= (-1);
        ft_putchar('-');
        len++;
    }
    aux = (int)(f * 100);
    p_int = (aux - ((aux % 100))) / 100;
    p_dec = aux % 100;
    len += print_converted_n(p_int, 10);
    ft_putchar('.');
    len++;
    len += print_converted_n(p_dec, 10);
    return (len);
}

int     print_octal(va_list argptr)
{
    int     n;
    int     len;

    n = va_arg(argptr, int);
    len = 0;
    ft_putstr("0o");
    len += (2 + print_converted_n(n, 8));
    return (len);
}

int     print_hex(va_list argptr)
{
    int     n;
    int     len;

    n = va_arg(argptr, int);
    len = 0;
    ft_putstr("0x");
    len += (2 + print_converted_n(n, 16));
    return (len);
}

int     print_pointer(va_list argptr)
{
    uintptr_t   pointer_int;
    char        address[16];
    int         i;
    void        *pointer;

    pointer = va_arg(argptr, void*);
    pointer_int = (uintptr_t)pointer;
    i = 0;
    while (i++ < 16) 
    {
        address[15 - i] = "0123456789abcdef"[pointer_int & 0xf];
        pointer_int >>= 4;
    }
    ft_putstr("0x");
    ft_putstr(address);
    return (18);
}
```

# Repositório 

Para ver o código completo da implementação, acesse-o no Github: https://github.com/pliniohavila/ft_printf 

# Conclusão 

Bem, esta foi uma implementação simples, cujo intuito foi basicamente praticar o uso dos macros `va_arg, va_copy, va_end, va_start` e entender como é a função `printf` por debaixo dos planos. 

Pretendo volta e meia voltar ao código da minha implementação para realizar correções, conforme vou estudando mais e ganhando mais prática com a linguagem C. Temos, por exemplo, a implementação de `flags` para uma melhor impressão dos dados, dentre outras alterações que permitam ter um funcionamento semelhante as atuais implementações da função `printf`. 


# Referências

- https://pliniohavila.hashnode.dev/introducao-aos-macros-vastart-vaarg-vaend-vacopy-na-linguagem-c
- https://pliniohavila.hashnode.dev/estudos-de-c-breves-notas-sobre-dispatch-tables
- https://medium.com/@HackerSa3edy/printf-the-art-of-crafting-a-custom-function-in-c-programming-a3e3ec06bdb8
- https://www.academia.edu/10297206/Secrets_of_printf_
- https://github.com/Tahani-Saber/printf
- https://opensource.apple.com/source/xnu/xnu-201/osfmk/kern/printf.c.auto.html
- https://delicious-caraway-75c.notion.site/printf-project-d4808647995045d7ad0c9716e0b287be
- https://opensource.apple.com/source/xnu/xnu-201/osfmk/kern/printf.c.auto.html