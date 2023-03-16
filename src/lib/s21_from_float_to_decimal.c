#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int scale = 0;
    if ((fabs(src) >= 0 && fabs(src) < 1) || fabs(src) >= 1000000) {
        scale = 7;
    }
    if (fabs(src) < 10 && fabs(src) >=1 ) {
        scale = 6;
    }

    if (fabs(src) < 100 && fabs(src) >= 10) {
        scale = 5;
    }

    if (fabs(src) < 1000 && fabs(src) >= 100) {
        scale = 4;
    }

     if (fabs(src) < 10000 && fabs(src) >= 1000) {
        scale = 3;
    }

     if (fabs(src) < 100000 && fabs(src) >= 10000) {
        scale = 2;
    }

     if (fabs(src) < 1000000 && fabs(src) >= 100000) {
        scale = 1;
    }
    int scale_2 = scale;
    while (scale != 0) {
        src *= 10;
        scale--;
    }
    
    src = round(src);
    long double new_src = src;
    // if (scale == 0) {
        
    // } else {
    s21_from_int_to_decimal(new_src, dst);
    //}

    s21_set_power(dst, scale_2);

    return 1;
}   
