#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  *result = (s21_decimal){{0, 0, 0, 0}};
  if (is_zero(value_2)) {
    error = 3;
  } else if (is_zero(value_1)) {
    error = 0;
  } else {
    s21_big_decimal first = to_big(value_1), second = to_big(value_2),
                    result_big = {0};
    s21_add_accurance(first, &first);
    s21_div_big(first, second, &result_big);
    error = normalize_to_usual(result_big, result);
  }
  return error;
}

int s21_add_accurance(s21_big_decimal first, s21_big_decimal *result) {
  int exp = first.exp, sign = s21_get_sign(first);
  s21_set_exp(&first, 0);
  for (int i = 0; i < 35; i++) {
    s21_mul_big(first, (s21_big_decimal){{10u, 0, 0, 0, 0, 0, 0}, 0, 0},
                &first);
    exp++;
  }
  s21_set_exp(&first, exp);
  if (sign) s21_set_sign(&first);
  *result = first;
  return 0;
}

// div v.2
int s21_div_big(s21_big_decimal first, s21_big_decimal second,
                s21_big_decimal *result) {
  *result = clean_up();
  int new_exp = abs(s21_get_exp(first) - s21_get_exp(second));
  int new_sign = s21_get_sign(first) + s21_get_sign(second);
  s21_set_exp(&first, 0);
  s21_set_exp(&second, 0);
  int flag = 0;
  s21_big_decimal temp = second;
  int temp_pos = get_pos_of(first) - get_pos_of(second);
  if (temp_pos > 0) s21_shift_left(&temp, temp_pos);

  s21_set_exp(&first, 0);
  s21_set_exp(&second, 0);
  s21_set_exp(&temp, 0);
  while (s21_is_greater_or_equal_big(temp, second)) {
    flag = 1;
    if (s21_is_greater_or_equal_big(first, temp)) {
      s21_set_bit(result, temp_pos, 1);
      s21_sub_big(first, temp, &first);
    } else {
      s21_set_bit(result, temp_pos, 0);
    }
    temp_pos--;
    s21_shift_right(&temp, 1);
  }
  if (flag) {
    s21_set_exp(result, new_exp);
    if (new_sign % 2 == 1) s21_set_sign(result);
  }
  return flag;
}

int get_pos_of(s21_big_decimal temp) {
  int temp_pos = 0;
  for (int i = 7 * 32 - 1; i >= 0; i--) {
    if (s21_get_bit(temp, i)) {
      temp_pos = i;
      i = -1;
    }
  }
  return temp_pos;
}
