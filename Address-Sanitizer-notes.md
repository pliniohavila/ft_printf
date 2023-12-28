
# Um introdução ao Address Sanitizer

**Notas introdutórias:**    
O compilador utilizado é o `gcc version 10.2.1 20210110 (Debian 10.2.1-6)`. 
Executado em um ambiente WSL versão 2.0.9.0.

O Address Sanitizer, ASan, é um ferramenta que permite indentificar erros de memória, e relacionados, em tempo de execução. 
Por meio dele é possível identificar os seguintes erros:

- Use after free (dangling pointer dereference)
- Heap buffer overflow
- Stack buffer overflow
- Global buffer overflow
- Use after return
- Use after scope
- Initialization order bugs
- Memory leaks

Já vem disponível nos dois compiladores mais utilizados GCC e CLANG. Sua utilização é por meio de _flags_, conforme o tópico 
Uso explica.  

Sua utilização é por meio de _flags_, 

TO READ
https://sergioprado.org/identificando-problemas-de-acesso-memoria-com-o-addresssanitizer/
https://diveintosystems.org/book/C1-C_intro/getting_started.html
https://medium.com/nebula-graph/an-introduction-to-googles-memory-error-detect-tool-addesssanitizer-fb211d1c8ef1
https://www.usenix.org/system/files/conference/atc12/atc12-final39.pdf
https://emscripten.org/docs/debugging/Sanitizers.html
https://maskray.me/blog/2023-02-12-all-about-leak-sanitizer
https://lemire.me/blog/2016/04/20/no-more-leaks-with-sanitize-flags-in-gcc-and-clang/
https://girishjoshi.io/post/using-address-sanitizer-with-gcc/
https://azure.microsofts.workers.dev/en-us/cpp/sanitizers/

## Uso

Para habilitar o ASan, adicione a seguinte flag quando estiver compilando o progama. 

`-fsanitize=address (clang)`

`gcc app.c -fsanitize=address -o app`

Tem outras _flgas_ que podem serem consultadas na [documentação](https://github.com/google/sanitizers/wiki/AddressSanitizerCallStack).


# Referências:

https://clang.llvm.org/docs/AddressSanitizer.html
https://developer.apple.com/documentation/xcode/diagnosing-memory-thread-and-crash-issues-early
https://sergioprado.org/identificando-problemas-de-acesso-memoria-com-o-addresssanitizer/