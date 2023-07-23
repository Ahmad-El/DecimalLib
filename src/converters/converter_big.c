#include "../s21_decimal.h"

int s21_from_int_to_decimal_big(int src, s21_big_decimal *dst) {
  *dst = clean_up();
  int sign = src < 0 ? 1 : 0;
  if (sign) src *= -1;
  dst->bits[0] = src;
  if (sign) s21_set_sign(dst);
  return 0;
}
int s21_from_decimal_to_int_big(s21_big_decimal src, int *dst) {
  int flag = 0;
  int sign = s21_get_sign(src);
  s21_truncate_big(src, &src);
  for (int i = 1; i < 7; i++) {
    if (src.bits[i] > 0) flag = 1;
  }
  if (!flag) {
    *dst = src.bits[0];
    if (sign) *dst = -(*dst);
  }
  return flag;
}

int s21_from_decimal_to_float_big(s21_big_decimal src, float *dst) {
  int exp = s21_get_exp(src);
  double result = 0;
  for (int i = 0; i < 7 * 32; i++) {
    result = result + s21_get_bit(src, i) * pow(2, i);
  }
  while (exp > 0) {
    result = result / 10;
    exp--;
  }
  if (s21_get_sign(src)) result *= -1;
  *dst = (float)result;
  return 0;
}

int get_float_exp(char *str) {
  int flag = 0, exp = 0, len = 0, flag_len = 0, cnt = 0;
  for (int i = 0; i < (int)strlen(str) && cnt < 28; i++) {
    if (str[i] == '.') {
      flag = 1;
    } else if (flag) {
      cnt++;
      exp++;
      if (str[i] != '0') flag_len = 1;
      if (flag_len) len++;
    }
    if (len >= 7) i = (int)strlen(str);
  }
  return -exp;
}
int get_float_exp_2(char *str) {
  int cnt = 0, flag = 0, exp = 0;
  for (int i = 0; i < (int)strlen(str) && cnt <= 28; i++) {
    cnt++;
    if (str[i] == '.') flag = 1;
    if (cnt >= 7 && flag) i = strlen(str);
    if (flag) exp--;
    if (exp >= 0) exp++;
  }
  return exp;
}
int check_error_code(float src) {
  int flag = 0;
  if (isinf(src) || isnan(src)) flag = 1;
  if (-1e-28 < src && src < 1e-28 && src != 0) flag = 1;
  if ((-DECIMAL_MAX - src) >= 0 || (src - DECIMAL_MAX) >= 0) flag = 1;
  return flag;
}

int s21_from_float_to_decimal_big(float src, s21_big_decimal *dst) {
  if (check_error_code(src)) return 1;
  char str[100];
  int sign = 0, flag = 0, len = 0;
  double x = 0, divider = 10;
  sprintf(str, "%.35f", src);
  if (str[0] == '-') {
    sign = 1;
    int length = (int)strlen(str);
    for (int i = 0; i < length; i++) {
      str[i] = str[i + 1];
    }
  }
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == '.') continue;
    if (!flag && str[i] != '0') flag = 1;
    double d = str[i] - '0';
    if (flag) {
      len++;
      if (len <= 7 && i <= 29)
        x = x * 10 + d;
      else if (len <= 10) {
        x = x + d / divider;
        divider *= 10;
      } else
        i = strlen(str);
    }
  }
  int exp = -1;
  if (str[0] == '0' && str[1] == '.')
    exp = get_float_exp(str);
  else
    exp = get_float_exp_2(str);
  *dst = clean_up();
  dst->bits[0] = (unsigned int)round(x);
  int new_exp;
  if (exp > 0)
    new_exp = exp - 7;
  else
    new_exp = exp;
  if (new_exp < 0) {
    s21_set_exp(dst, -new_exp);
  } else {
    for (int i = 0; i < new_exp; i++)
      s21_mul_big(*dst, (s21_big_decimal){{10u, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
                  dst);
  }
  if (sign) s21_set_sign(dst);
  return 0;
}
