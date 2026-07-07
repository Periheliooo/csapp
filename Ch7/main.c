#include <stdio.h>

extern int global_var;

void foo(void);

int main(void)
{
    printf("global_var = %d\n", global_var);

    foo();

    return 0;
}
