
# Um introdução à Address Sanitizer

**Notas introdutórias:**    
O compilador utilizado é o `gcc version 10.2.1 20210110 (Debian 10.2.1-6)`. 
Executado em um ambiente WSL versão 2.0.9.0.

A Address Sanitizer, ASan, é uma ferramenta que permite indentificar erros de memória em tempo de execução. 
Em outras palavras, quando executamos nossos programa e ocorre algum erro de memória, não vazamento — tem 
outra ferramenta para identificar vazamentos —, a ASan acusa a ocorrência do problema. 

Segundo o descrito no _paper_ "_AddressSanitizer: A Fast Address Sanity Checker_", ela é:

> a new memory error detector. Our tool finds out-of-bounds accesses to heap, stack, and global objects, as well as use-after-free bugs. It employs a specialized memory allocator and code instrumentation that is simple enough to be implemented in any compiler, binary translation system, or even in hardware.

Por meio dela é possível identificar os seguintes erros:

- Use after free (dangling pointer dereference)
- Heap buffer overflow
- Stack buffer overflow
- Global buffer overflow
- Use after return
- Use after scope
- Initialization order bugs
- Memory leaks

Ela já vem disponível nos dois compiladores mais utilizados GCC e CLANG. Sua utilização é por meio de _flags_, 
definidas durante a compilação. Assim, a ASan insere no código da aplicação, que está sendo compilada, mecanismos que permite "_identificar diversos problemas de acesso à memória, incluindo o uso de memória desalocada, estouros de buffer no stack e no heap, acesso à memória não inicializada e vazamentos de memória_" [^1].

A sua forma de atuação pode ser consultada na [documentação](https://github.com/google/sanitizers/wiki/AddressSanitizerCallStack). Mas, basicamente, a ASan atua trocando as chamadas `malloc/free` do código pelas suas versões. 

A utilização dessa ferramenta é fundamental para identificar problemas/erros escondidos. Por que escondidos? pois, pode ocorrer que o programa seja executado em sua totalidade com aparente estado de normalidade, todavia, sem que seja disparada e interrompido a execução. E que alguns erros podem estarem ocorrendo e que terão consequências em outras execuções ou exporem alguma vulnerabilidade no código.   

Deve ressaltar que o seu uso provoca uma sobrecarga na execução e processamento da aplicação. Em razão disso recomenda-se sua utilização apenas em versões de desenvolvimento e testes.

## Uso

Para habilitar o ASan, adicione a seguinte flag quando estiver compilando o progama. 

`-fsanitize=address (clang)`

`gcc app.c -fsanitize=address -o app`

Tem outras _flgas_ que podem serem consultadas na [documentação](https://github.com/google/sanitizers/wiki/AddressSanitizerCallStack).

## Exemplos de usos

[Stack buffer overflow]


[Heap buffer overflow]


[Use After Free]

[Memory leaks]

Um exmplo de _Memory leaks_. _Memory leaks_ ou vazamento de memória, é segundo a Wikipédia, "_um fenômeno que ocorre quando um programa de computador gerencia incorretamente alocações de memória de maneira que certa memória não é liberada quando não é mais necessária_". 

Veja-se o exemplo abaixo:

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
   char     *buffer;
   
   buffer = malloc(1024);
   sprintf(buffer, "%s", argv[1]);
   printf("%s\n", buffer);
   return (0);
}
```
Quando compilado e executado, não é apresentado qualquer erro;

```shell 
> gcc test.c -o test 
> ./test hello
> hello
```
Agora, quando compilado com a _flag_ `-fsanitize=address` e executado, a ASan entra em ação para apresenta os erros encontrados.

```shel 
> gcc test.c -fsanitize=address -o test
> ./test hello                                                                                                                                                         hello                                                                                                                                                                                                                                                                                                                                         =================================================================                                                      ==822==ERROR: LeakSanitizer: detected memory leaks                                                                                                                                                                                                                                                                                            Direct leak of 1024 byte(s) in 1 object(s) allocated from:                                                                                                                 #0 0x7f5f09215e8f in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145                                                                  #1 0x5624c33ff1bd in main (/home/senhor/School42/ft_printf/test+0x11bd)                                                                                                #2 0x7f5f08fbbd09 in __libc_start_main ../csu/libc-start.c:308                                                                                                                                                                                                                                                                            SUMMARY: AddressSanitizer: 1024 byte(s) leaked in 1 allocation(s).    

```


TO READ

https://girishjoshi.io/post/using-address-sanitizer-with-gcc/
https://azure.microsofts.workers.dev/en-us/cpp/sanitizers/



# Referências:
https://www.usenix.org/system/files/conference/atc12/atc12-final39.pdf
[^1] https://sergioprado.org/identificando-problemas-de-acesso-memoria-com-o-addresssanitizer/
https://pt.wikipedia.org/wiki/Vazamento_de_memória

https://clang.llvm.org/docs/AddressSanitizer.html
https://developer.apple.com/documentation/xcode/diagnosing-memory-thread-and-crash-issues-early
https://sergioprado.org/identificando-problemas-de-acesso-memoria-com-o-addresssanitizer/