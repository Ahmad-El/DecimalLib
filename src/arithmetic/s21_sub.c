#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  s21_negate(value_2, &value_2);
  s21_big_decimal first = to_big(value_1), second = to_big(value_2),
                  result_big = {0};
  if (first.sign != second.sign) {
    if (first.exp != second.exp) normalize_exp(&first, &second, 1);
    if (s21_is_less_big(second, first))
      s21_sub_big(first, second, &result_big);
    else
      s21_sub_big(second, first, &result_big);
    code = normalize_to_usual(result_big, result);
    if (result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0) {
      result->bits[3] = 0;
    }
  } else
    code = s21_add(value_1, value_2, result);
  return code;
}

int s21_sub_big(s21_big_decimal first, s21_big_decimal second,
                s21_big_decimal *result) {
  int sign = s21_get_sign(first);
  unsigned int keeper = 0;
  for (int i = 0; i < 7 * 32; i++) {
    int bit1 = s21_get_bit(first, i);
    int bit2 = s21_get_bit(second, i);
    bit1 += keeper;
    if (bit1 == 2) {
      bit1 = 0;
      keeper = 0;
    }
    if (bit2 > bit1) {
      bit1 = 2;
      keeper = 1;
    }
    s21_set_bit(result, i, (bit1 - bit2));
  }
  if (sign) s21_set_sign(result);
  s21_set_exp(result, s21_get_exp(first));
  return 0;
}
