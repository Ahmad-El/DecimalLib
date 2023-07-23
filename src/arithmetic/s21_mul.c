#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_big_decimal first = to_big(value_1), second = to_big(value_2),
                  result_big = {0};
  error = s21_mul_big(first, second, &result_big);
  error = normalize_to_usual(result_big, result);
  if (result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0)
    result->bits[3] = 0;
  return error;
}

int s21_mul_big(s21_big_decimal first, s21_big_decimal second,
                s21_big_decimal *result) {
  s21_big_decimal temp_result = {0};
  int new_sign = s21_get_sign(first) + s21_get_sign(second);
  int new_exp = s21_get_exp(first) + s21_get_exp(second);
  s21_set_exp(&temp_result, new_exp);
  if (new_sign % 2 == 1) s21_set_sign(&temp_result);

  for (int i = 0; i < 7 * 32; i++) {
    s21_big_decimal temp = {0};
    temp = second;
    int bit = s21_get_bit(first, i);
    if (bit) {
      s21_shift_left(&temp, i);
      s21_add_big(temp_result, temp, &temp_result);
    }
  }
  *result = temp_result;
  return 1;
}
