
# Notas introdutórias à ferramenta Address Sanitizer

A Address Sanitizer, ASan, é uma ferramenta que permite identificar erros de memória em tempo de execução. 
Em outras palavras, quando executamos nossos programa e ocorre algum erro de memória: a ASan acusa a ocorrência do problema, bem como interrompendo a sua execução. 

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

Ela já vem disponível nos dois compiladores mais utilizados GCC e CLANG. Sua utilização é por meio de _flags_ 
definidas durante a compilação. Assim, a ASan insere no código da aplicação, que está sendo compilada, mecanismos que permite "_identificar diversos problemas de acesso à memória, incluindo o uso de memória desalocada, estouros de buffer no stack e no heap, acesso à memória não inicializada e vazamentos de memória_" (PRADO, 2018).

A sua forma de atuação pode ser consultada na [documentação](https://github.com/google/sanitizers/wiki/AddressSanitizerCallStack). Mas, basicamente, a ASan atua trocando as chamadas `malloc/free` do código pelas suas próprias versões de gerenciadores de acesso/uso de memória. 

A utilização dessa ferramenta é fundamental para identificar problemas/erros escondidos. Por que escondidos? Pois, pode ocorrer que o programa seja executado em sua totalidade com aparente estado de normalidade, todavia, sem que seja disparado algum erro ou interrompido a sua execução. Sendo que, há alguns erros que podem estarem ocorrendo e que terão consequências em outras execuções ou exporem o software à alguma vulnerabilidade.   

Deve-se ressaltar que o seu uso provoca uma sobrecarga na execução e processamento da aplicação. Em razão disso, é recomenddo a sua utilização apenas em versões de desenvolvimento e testes.

## Uso

Para habilitar o ASan, adicione a seguinte flag quando estiver compilando o progama. 

`-fsanitize=address (clang)`

`gcc app.c -fsanitize=address -o app`

Tem outras _flgas_ que podem serem consultadas na [documentação](https://github.com/google/sanitizers/wiki/AddressSanitizerCallStack).

## Exemplos de usos

###  Erro Stack buffer overflow
"_Buffer Overflow, também chamado de Buffer Overrun, é uma anomalia em um programa em que, ao escrever dados em um buffer (armazenamento temporário de dados), a escrita ultrapassa o tamanho do buffer e começa a escrever nos espaços adjacentes._"

Veja-se o exemplo abaixo:

```c
#include <stdio.h>
#include <string.h>

int main(void) 
{
   char     str[2];

   str[0] = 'O';
   str[1] = 'l';
   str[2] = 'a';
   str[3] = '\0';
   printf("%s\n", str);
   return (0);
}
```
Quando compilado e executado, não é apresentado qualquer erro;

```shell 
> gcc test.c -o test 
> ./test
> Ola
```
Agora, quando compilado com a _flag_ `-fsanitize=address` e executado, a ASan entra em ação para apresentar os erros encontrados e interromper a respectiva execução.

```shel 
> gcc test.c -fsanitize=address -o test
> ./test

=================================================================
==389==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffe948a7662 at pc 0x55d86850528f bp 0x7ffe948a7630 sp 0x7ffe948a7628
WRITE of size 1 at 0x7ffe948a7662 thread T0
    #0 0x55d86850528e in main (/home/senhor/School42/ft_printf/test+0x128e)
    #1 0x7f06f5c9cd09 in __libc_start_main ../csu/libc-start.c:308
    #2 0x55d8685050b9 in _start (/home/senhor/School42/ft_printf/test+0x10b9)

Address 0x7ffe948a7662 is located in stack of thread T0 at offset 34 in frame
    #0 0x55d868505184 in main (/home/senhor/School42/ft_printf/test+0x1184)

  This frame has 1 object(s):
    [32, 34) 'str' (line 6) <== Memory access at offset 34 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow (/home/senhor/School42/ft_printf/test+0x128e) in main
Shadow bytes around the buggy address:
  0x10005290ce70: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10005290ce80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10005290ce90: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10005290cea0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10005290ceb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x10005290cec0: 00 00 00 00 00 00 00 00 f1 f1 f1 f1[02]f3 f3 f3
  0x10005290ced0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10005290cee0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10005290cef0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10005290cf00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10005290cf10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==389==ABORTING

```

### Erro Memory leaks

Outro exemplo é com _Memory leaks_. _Memory leaks_ ou vazamento de memória, é segundo a Wikipédia, "_um fenômeno que ocorre quando um programa de computador gerencia incorretamente alocações de memória de maneira que certa memória não é liberada quando não é mais necessária_". 

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
Quando compilado e executado, novamente, não é apresentado qualquer erro;

```shell 
> gcc test.c -o test 
> ./test hello
> hello
```
Agora, quando compilado com a _flag_ `-fsanitize=address` e executado, a ASan entra em ação para apresentar os erros encontrados.

```shel 
> gcc test.c -fsanitize=address -o test
> ./test hello                                                                                                                                                         hello                                                                                                                                                                                                                                                                                                                                         =================================================================                                                      ==822==ERROR: LeakSanitizer: detected memory leaks                                                                                                                                                                                                                                                                                            Direct leak of 1024 byte(s) in 1 object(s) allocated from:                                                                                                                 #0 0x7f5f09215e8f in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145                                                                  #1 0x5624c33ff1bd in main (/home/senhor/School42/ft_printf/test+0x11bd)                                                                                                #2 0x7f5f08fbbd09 in __libc_start_main ../csu/libc-start.c:308                                                                                                                                                                                                                                                                            SUMMARY: AddressSanitizer: 1024 byte(s) leaked in 1 allocation(s).    

```


# Referências:

- https://www.usenix.org/system/files/conference/atc12/atc12-final39.pdf
- https://sergioprado.org/identificando-problemas-de-acesso-memoria-com-o-addresssanitizer/
- https://pt.wikipedia.org/wiki/Vazamento_de_memória
- https://girishjoshi.io/post/using-address-sanitizer-with-gcc/
- https://azure.microsofts.workers.dev/en-us/cpp/sanitizers/
- https://clang.llvm.org/docs/AddressSanitizer.html
- https://developer.apple.com/documentation/xcode/diagnosing-memory-thread-and-crash-issues-early
- https://gitbook.ganeshicmc.com/pwning/buffer-overflow-e-a-stack