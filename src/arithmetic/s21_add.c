#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_big_decimal first = to_big(value_1), second = to_big(value_2),
                  result_big = {0};
  if (first.sign == second.sign) {
    if (first.exp != second.exp) normalize_exp(&first, &second, 1);
    error = s21_add_big(first, second, &result_big);
    if (!error) error = normalize_to_usual(result_big, result);
  } else {
    s21_negate(value_2, &value_2);
    s21_sub(value_1, value_2, result);
  }

  return error;
}

int s21_add_big(s21_big_decimal first, s21_big_decimal second,
                s21_big_decimal *result) {
  int sign = s21_get_sign(first);
  unsigned int keeper = 0;
  for (int i = 0; i < 7 * 32; i++) {
    unsigned int value =
        s21_get_bit(second, i) + keeper + s21_get_bit(first, i);
    keeper = value / 2;
    s21_set_bit(result, i, value % 2);
  }
  s21_set_exp(result, s21_get_exp(first));
  if (sign) s21_set_sign(result);
  return 0;
}
