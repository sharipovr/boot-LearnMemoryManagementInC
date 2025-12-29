Learn how to manually manage memory in C and build a garbage collector from scratch.

### Build & run

This repo includes a tiny embedded test runner (`munit.h`). To compile and run:

```bash
clang main.c exercise.c -o main.out -lm
./main.out
```
After addition of munit we need also add a small compatibility header munit_bootdev_compat.h and you compile with -include so it’s injected before main.c:

```bash
clang -I. -Imunit -include munit_bootdev_compat.h \
  main.c exercise.c munit/munit.c -o main.out

./main.out
```