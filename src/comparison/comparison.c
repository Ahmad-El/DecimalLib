#include "../s21_decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
  if (is_zero(a)) set_exp(&a, 0);
  if (is_zero(b)) set_exp(&b, 0);
  s21_big_decimal first = to_big(a), second = to_big(b);
  int value = 0;
  if (first.sign != second.sign)
    value = (first.sign == 1) ? 1 : 0;
  else if (first.sign == 0)
    value = s21_is_less_big(first, second);
  else
    value = s21_is_less_big(second, first);
  return value;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  if (is_zero(a)) set_exp(&a, 0);
  if (is_zero(b)) set_exp(&b, 0);
  s21_big_decimal first = to_big(a), second = to_big(b);
  int value = 0;
  if (first.sign != second.sign)
    value = (first.sign == 1) ? 1 : 0;
  else if (first.sign == 0)
    value = s21_is_less_or_equal_big(first, second);
  else
    value = s21_is_less_or_equal_big(second, first);
  return value;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  if (is_zero(a)) set_exp(&a, 0);
  if (is_zero(b)) set_exp(&b, 0);
  s21_big_decimal first = to_big(a), second = to_big(b);
  int value = 0;
  if (first.sign != second.sign)
    value = (first.sign == 1) ? 0 : 1;
  else if (first.sign == 0)
    value = s21_is_greater_big(first, second);
  else
    value = s21_is_greater_big(second, first);
  return value;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  if (is_zero(a)) set_exp(&a, 0);
  if (is_zero(b)) set_exp(&b, 0);
  s21_big_decimal first = to_big(a), second = to_big(b);
  int value = 0;
  if (first.sign != second.sign)
    value = (first.sign == 1) ? 0 : 1;
  else if (first.sign == 0)
    value = s21_is_greater_or_equal_big(first, second);
  else
    value = s21_is_greater_or_equal_big(second, first);
  return value;
}
int s21_is_equal(s21_decimal a, s21_decimal b) {
  s21_big_decimal first = to_big(a), second = to_big(b);
  int value = 0;
  if (first.sign != second.sign)
    value = 0;
  else
    value = s21_is_equal_big(first, second);
  return value;
}
int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  s21_big_decimal first = to_big(a), second = to_big(b);
  int value = 0;
  if (first.sign != second.sign)
    value = 1;
  else
    value = s21_is_not_equal_big(first, second);
  return value;
}