#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

typedef struct 
{
    unsigned int bits[4];
} s21_decimal;

typedef struct
{
    unsigned int bits[8];
    int exp;
    int sign;
} s21_big_decimal;


int s21_get_bit(s21_big_decimal value, int bit);
void s21_set_bit(s21_big_decimal *result, int bit, int value);
int s21_get_exp(s21_big_decimal value);
void s21_set_exp(s21_big_decimal *result, int new_exp);
int s21_get_sign(s21_big_decimal value);
void s21_set_sign(s21_big_decimal *dst);
void s21_copy_decimal(s21_decimal import, s21_big_decimal *export);
void s21_shift_right(s21_big_decimal *value, int shift);
void s21_shift_left(s21_big_decimal *value, int shift);


int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif // S21_DECIMAL_H_