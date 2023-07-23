#include "../s21_decimal.h"

int normalize_exp(s21_big_decimal *first, s21_big_decimal *second, int to_big) {
  s21_big_decimal a = *first, b = *second, temp = {0};
  temp.bits[0] = 10u;

  int exp1 = a.exp, exp2 = b.exp, sign1 = a.sign, sign2 = b.sign;
  int shift = exp1 - exp2;

  if (shift == 0) {
    return 1;
  }
  if (shift < 0) {
    exp1 += 1;
    s21_set_exp(first, s21_get_exp(temp));
    s21_mul_big(*first, temp, &a);
  } else if (shift > 0) {
    exp2 += 1;
    s21_set_exp(second, s21_get_exp(temp));
    s21_mul_big(*second, temp, &b);
  }

  s21_set_exp(&a, exp1);
  s21_set_exp(&b, exp2);
  if (sign1) s21_set_sign(&a);
  if (sign2) s21_set_sign(&b);
  *first = a;
  *second = b;
  return normalize_exp(first, second, to_big);
}
