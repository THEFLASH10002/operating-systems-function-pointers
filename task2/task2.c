#include <stdio.h>
#include <stdlib.h>

/* All operations share one signature for the function pointer dispatch table. */
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int exit_program(int a, int b);
int invalid_operation(int a, int b);

int main(void)
{
    const int a = 6;
    const int b = 3;
    unsigned char operation = '4';
    int (*operations[256])(int, int);

    /* A full character-indexed table safely handles every possible byte,
       without if, else, switch, goto, or the conditional operator. */
    for (int i = 0; i < 256; i++) {
        operations[i] = invalid_operation;
    }
    operations['0'] = add;
    operations['1'] = subtract;
    operations['2'] = multiply;
    operations['3'] = divide;
    operations['4'] = exit_program;

    printf("Operand 'a' : %d | Operand 'b' : %d\n", a, b);
    printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit): ");
    scanf(" %c", (char *)&operation);

    /* The character's byte value directly selects its function. */
    int x = operations[operation](a, b);
    printf("x = %d\n", x);
    return 0;
}

int add(int a, int b)
{
    printf("Adding 'a' and 'b'\n");
    return a + b;
}

int subtract(int a, int b)
{
    printf("Subtracting 'b' from 'a'\n");
    return a - b;
}

int multiply(int a, int b)
{
    printf("Multiplying 'a' and 'b'\n");
    return a * b;
}

int divide(int a, int b)
{
    printf("Dividing 'a' by 'b'\n");
    return a / b;
}

int exit_program(int a, int b)
{
    (void)a;
    (void)b;
    exit(0);
}

int invalid_operation(int a, int b)
{
    (void)a;
    (void)b;
    fprintf(stderr, "Invalid operation. Choose 0, 1, 2, 3, or 4.\n");
    exit(1);
}
