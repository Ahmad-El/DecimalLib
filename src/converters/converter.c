#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_big_decimal value = {0};
  s21_from_int_to_decimal_big(src, &value);
  int code = normalize_to_usual(value, dst);
  return code;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_big_decimal value = to_big(src);
  int code = s21_from_decimal_to_int_big(value, dst);
  if (code) *dst = 0;
  return code;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_big_decimal temp = {0};
  int code = s21_from_float_to_decimal_big(src, &temp);
  normalize_to_usual(temp, dst);
  return code;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  s21_big_decimal value = to_big(src);
  int code = s21_from_decimal_to_float_big(value, dst);
  if (code) *dst = 0;
  return code;
}
