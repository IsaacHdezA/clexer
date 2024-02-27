# clexer
I'm trying to create a lexer in C. Following the steps of Robert Nystrom (Crafting Interpreters). This is my own implementation, not his.

## Compile (I don't know how to use make)

```sh
gcc src/utilities.c src/token.c src/list.c main.c -o run && valgrind --leak-check=yes --track-origins=yes -s ./run
```
