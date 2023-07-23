#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECIMAL_MAX 79228162514264337593543950335.f

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
  int exp;
  int sign;
} s21_big_decimal;

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// (AO) help operators
int s21_add_big(s21_big_decimal first, s21_big_decimal second,
                s21_big_decimal *result);
int s21_mul_big(s21_big_decimal first, s21_big_decimal second,
                s21_big_decimal *answer);
int s21_div_big(s21_big_decimal first, s21_big_decimal second,
                s21_big_decimal *result);
int s21_sub_big(s21_big_decimal first, s21_big_decimal second,
                s21_big_decimal *result);
// 0 - OK
// 1 - the number is too large or equal to infinity
// 2 - the number is too small or equal to negative infinity
// 3 - division by 0

// Comparison Operators
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);
// (CO) help operators
int s21_is_less_big(s21_big_decimal first, s21_big_decimal second);
int s21_is_less_or_equal_big(s21_big_decimal first, s21_big_decimal second);
int s21_is_greater_big(s21_big_decimal first, s21_big_decimal second);
int s21_is_greater_or_equal_big(s21_big_decimal first, s21_big_decimal second);
int s21_is_equal_big(s21_big_decimal first, s21_big_decimal second);
int s21_is_not_equal_big(s21_big_decimal first, s21_big_decimal second);
// 0 - FALSE
// 1 - TRUE

// Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
// (CP) help operators
int s21_from_int_to_decimal_big(int src, s21_big_decimal *dst);
int s21_from_float_to_decimal_big(float src, s21_big_decimal *dst);
int s21_from_decimal_to_int_big(s21_big_decimal src, int *dst);
int s21_from_decimal_to_float_big(s21_big_decimal src, float *dst);
// 0 - OK
// 1 - convertation error

// Another functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
// (AF) help functions
int s21_floor_big(s21_big_decimal value, s21_big_decimal *result);
int s21_round_big(s21_big_decimal value, s21_big_decimal *result);
int s21_truncate_big(s21_big_decimal value, s21_big_decimal *result);
// 0 - OK
// 1 - calculation error

// Extra Operations
int s21_get_bit(s21_big_decimal value, int bit);
void s21_set_bit(s21_big_decimal *result, int bit, int value);
int s21_get_exp(s21_big_decimal value);
void s21_set_exp(s21_big_decimal *result, int new_exp);
int s21_get_sign(s21_big_decimal value);
void s21_set_sign(s21_big_decimal *dst);
void s21_shift_right(s21_big_decimal *value, int shift);
void s21_shift_left(s21_big_decimal *value, int shift);
s21_big_decimal to_big(s21_decimal value);
int basic_compare(s21_big_decimal first, s21_big_decimal second);
int normalize_exp(s21_big_decimal *first, s21_big_decimal *second, int to_big);
int s21_get_bit_small(s21_decimal value, int bit);
void s21_set_bit_small(s21_decimal *result, int bit, int value);
s21_big_decimal clean_up();
int s21_negate(s21_decimal value, s21_decimal *result);
int normalize_to_usual(s21_big_decimal result_big, s21_decimal *result);
int not_normal(s21_big_decimal value);
int s21_add_accurance(s21_big_decimal first, s21_big_decimal *result);
void set_exp(s21_decimal *result, int new_exp);
void set_sign(s21_decimal *value, int sign);
int get_last(s21_big_decimal value);
int is_zero(s21_decimal value);
int round_or_floor(s21_big_decimal value, s21_big_decimal *result, int type);
int get_pos_of(s21_big_decimal temp);
int big_is_zero(s21_big_decimal value);
int get_float_exp(char *str);
int get_float_exp_2(char *str);
int check_error_code(float src);
// void print_decimal_bits_usual(s21_decimal decimal);
// void print_decimal_bits(s21_big_decimal decimal);

#endif  // S21_DECIMAL_H_