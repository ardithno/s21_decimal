#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int main() {
    s21_decimal value = {{10}};
    
    printf("%d\n", value.bits[1]);
    return 0;
}