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
// enum rounding{ Trunc = 1, Floor, Round};

/// @brief
/// @param value
/// @param result
/// @param  type "0 for round" and "1 for floor" and "2 for truncate"
/// @return
int round_or_floor(s21_big_decimal value, s21_big_decimal *result, int type) {
  *result = clean_up();
  int last = 0, bifo_last = 0, exp = value.exp, sign = s21_get_sign(value);
  s21_set_exp(&value, 0);
  while (exp > 0) {
    last = get_last(value);
    bifo_last = last / 10;
    last = last % 10;
    s21_div_big(value, (s21_big_decimal){{10u, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
                &value);
    if (type == 0) {
      if (bifo_last % 2 == 0 && last == 5) last--;
      if (last >= 5)
        s21_add_big(value, (s21_big_decimal){{1u, 0, 0, 0, 0, 0, 0}, 0, 0},
                    &value);
    } else if (type == 1) {
      if (sign && last != 0) {
        s21_add_big(value, (s21_big_decimal){{1u, 0, 0, 0, 0, 0, 0}, 0, 0},
                    &value);
      }
    }
    exp--;
  }
  *result = value;
  return 0;
}

int s21_truncate_big(s21_big_decimal value, s21_big_decimal *result) {
  s21_big_decimal temp = {0};
  temp.bits[0] = 10u;
  int exponent = value.exp, sign = s21_get_sign(value);
  s21_set_exp(&value, 0);
  while (exponent > 0) {
    s21_div_big(value, temp, &value);
    exponent--;
  }
  *result = value;
  if (sign) s21_set_sign(result);
  return 0;
}

// int s21_floor_big(s21_big_decimal value, s21_big_decimal *result){
//     s21_big_decimal temp = {0};
//     temp.bits[0] = 10u;
//     int last = 0, value_exp = value.exp, sign = s21_get_sign(value);
//     s21_set_exp(&value, 0);
//     while (value_exp > 0)
//     {
//         last = value.bits[0] % 10;
//         s21_div_big(value, temp, &value);
//         if (sign && last != 0) {
//             temp.bits[0] = 1u;
//             s21_add_big(value, temp, &value);
//             temp.bits[0] = 10u;
//         }
//         value_exp --;
//     }
//     *result = value;
//     if(sign) s21_set_sign(result);
//     return 1;
// }

// int s21_round_big(s21_big_decimal value, s21_big_decimal *result){
//     s21_big_decimal temp = {0}; temp.bits[0] = 10u;
//     int exponent = value.exp, sign = s21_get_sign(value); s21_set_exp(&value,
//     0); while(exponent > 0){
//         int last = value.bits[0] % 10, bifo_last = (value.bits[0] % 100) /
//         10; s21_div_big(value, temp, &value); if(bifo_last % 2 == 0 && last
//         == 5) last --; if(last >= 5) {temp.bits[0] = 1u; s21_add_big(value,
//         temp, &value); temp.bits[0] = 10u;} exponent --;
//     }
//     *result = value;
//     if(sign) s21_set_sign(result);
//     return 1;
// }
