#include "../s21_decimal.h"

/*
-3        -2        -1         0         1         2         3
+--|------+---------+----|----+--|------+----|----+-------|-+
   a                     b       c           d            e

                        a=-2.7  b=-0.5  c=0.3  d=1.5  e=2.8
                        ======  ======  =====  =====  =====
Floor                    -3      -1      0      1      2
Ceiling                  -2       0      1      2      3
Truncate                 -2       0      0      1      2
Round (ToEven)           -3       0      0      2      3
Round (AwayFromZero)     -3      -1      0      2      3
*/
int s21_floor(s21_decimal value, s21_decimal *result) {
  int code = 0;
  s21_big_decimal temp = to_big(value);
  round_or_floor(temp, &temp, 1);
  code = normalize_to_usual(temp, result);
  return code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int code = 0;
  s21_big_decimal temp = to_big(value);
  round_or_floor(temp, &temp, 0);
  code = normalize_to_usual(temp, result);
  return code;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int code = 0;
  s21_big_decimal temp = to_big(value);
  s21_truncate_big(temp, &temp);
  code = normalize_to_usual(temp, result);
  return code;
}
int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  int sign = s21_get_bit_small(value, 4 * 32 - 1) == 1 ? 0 : 1;
  s21_set_bit_small(result, 4 * 32 - 1, sign);
  return 0;
}