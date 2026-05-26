#include <stdio.h>

int main() {
    int a = 10;
    float b = 20.5;
    char c = 'x';

    a = a + 5;
    b = b * 2.0;

    if (a >= b) {
        printf("A is greater or equal\n");
    } else {
        printf("B is greater\n");
    }

    return 0;
}
