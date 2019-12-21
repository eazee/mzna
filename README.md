# mzna
My attempt at a proper compiler for a simplistic programming language.

## Prerequisites
* GNU GCC (or other C compiler & linker, this can be configured in the Makefile)
* GNU Make

## Installation
If you have all the necessary prerequisites, then you should be ready to go!
```
git clone https://github.com/fl3ur/mzna.git
cd mzna
make prepare
make
```

## Roadmap
* :white_large_square: Preprocessor
* :heavy_check_mark: Lexer (→ `token_stream_t`)
* :construction: Parser (→ `ast_node_t`)
* :white_large_square: Semantic analysis
* :white_large_square: Intermediate code generator
* :white_large_square: Code optimiser
* :white_large_square: Code generator