#include "s21_decimal.h"
#include <limits.h>


int main(){
    s21_decimal first = {0};
    s21_decimal second = {0};
    s21_decimal result_sum = {0};
    first.bits[0] = 0b1111111111111;
    first.bits[1] = 0b1111111111111;
    first.bits[2] = 0b1;
    first.bits[3] = 0b10000000100000010000000000000000;
    s21_add(first, second, &result_sum);
    return 0;

}