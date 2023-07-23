#include "../s21_decimal.h"

int s21_is_less_big(s21_big_decimal first, s21_big_decimal second) {
  return basic_compare(first, second) == 1 ? 1 : 0;
}

int s21_is_less_or_equal_big(s21_big_decimal first, s21_big_decimal second) {
  return basic_compare(first, second) >= 0 ? 1 : 0;
}

int s21_is_greater_big(s21_big_decimal first, s21_big_decimal second) {
  return basic_compare(first, second) == -1 ? 1 : 0;
}

int s21_is_greater_or_equal_big(s21_big_decimal first, s21_big_decimal second) {
  return basic_compare(first, second) <= 0 ? 1 : 0;
}
int s21_is_equal_big(s21_big_decimal first, s21_big_decimal second) {
  return basic_compare(first, second) == 0 ? 1 : 0;
}
int s21_is_not_equal_big(s21_big_decimal first, s21_big_decimal second) {
  return basic_compare(first, second) != 0 ? 1 : 0;
}

/// @brief universal function for comparing;
/// @param first
/// @param second
/// @return -1 - first is greater, 0- equal, 1-second is greater;
int basic_compare(s21_big_decimal first, s21_big_decimal second) {
  normalize_exp(&first, &second, 1);
  int flag = 0;
  for (int i = 7 * 32 - 1; i >= 0; i--) {
    if (s21_get_bit(first, i) ^ s21_get_bit(second, i)) {
      if (s21_get_bit(first, i)) {
        flag = -1;
      } else {
        flag = 1;
      }
      i = 0;
    }
  }
  return flag;
}