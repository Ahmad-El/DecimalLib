#include "../s21_decimal.h"

int s21_get_bit(s21_big_decimal value, int bit) {
  unsigned int mask = 1u << (bit % 32);
  return (value.bits[bit / 32] & mask) ? 1 : 0;
}

void s21_set_bit(s21_big_decimal *result, int bit, int value) {
  unsigned int mask = 1u << (bit % 32);
  if (value)
    result->bits[bit / 32] |= mask;
  else
    result->bits[bit / 32] &= ~mask;
}

int s21_get_bit_small(s21_decimal value, int bit) {
  unsigned int mask = 1u << (bit % 32);
  return (value.bits[bit / 32] & mask) ? 1 : 0;
}

void s21_set_bit_small(s21_decimal *result, int bit, int value) {
  unsigned int mask = 1u << (bit % 32);
  if (value)
    result->bits[bit / 32] |= mask;
  else
    result->bits[bit / 32] &= ~mask;
}

int s21_get_exp(s21_big_decimal value) {
  unsigned int mask = 255 << 16;
  mask = value.bits[7] & mask;
  mask = mask << 1;
  mask = mask >> 17;
  return mask;
}

void s21_set_exp(s21_big_decimal *result, int new_exp) {
  unsigned int mask = new_exp;
  int sign = s21_get_sign(*result);
  mask = mask << 16;
  result->bits[7] = 0;
  result->bits[7] |= mask;
  if (sign) s21_set_sign(result);
  result->exp = s21_get_exp(*result);
}

int s21_get_sign(s21_big_decimal value) {
  unsigned int mask = value.bits[7] >> 31;
  return (mask) ? 1 : 0;
}

void s21_set_sign(s21_big_decimal *value) {
  unsigned int mask = 1u << 31;
  value->bits[7] |= mask;
  value->sign = 1;
}

void s21_shift_right(s21_big_decimal *origin, int shift) {
  s21_big_decimal value = *origin;
  int i = 0;
  for (; i < (32 * 7) - shift; i++) {
    s21_set_bit(&value, i, s21_get_bit(value, i + shift));
  }
  for (; i < 32 * 7; i++) s21_set_bit(&value, i, 0);
  *origin = value;
}

void s21_shift_left(s21_big_decimal *origin, int shift) {
  s21_big_decimal value = *origin;
  int last = 7 * 32 - 1;
  for (; last >= shift; last--) {
    s21_set_bit(&value, last, s21_get_bit(value, last - shift));
  }
  for (int i = 0; i < shift; i++) {
    s21_set_bit(&value, i, 0);
  }
  *origin = value;
}

s21_big_decimal to_big(s21_decimal value) {
  s21_big_decimal export = {0};
  for (int i = 0; i < 3; i++) export.bits[i] = value.bits[i];
  export.bits[7] = value.bits[3];
  export.exp = s21_get_exp(export);
  export.sign = s21_get_sign(export);
  return export;
}

int normalize_to_usual(s21_big_decimal result_big, s21_decimal *result) {
  int exp = result_big.exp, sign = result_big.sign, error = 0;
  s21_set_exp(&result_big, 0);
  int flag = 0;
  if (not_normal(result_big) || (get_last(result_big) % 10 == 0 && exp > 0) ||
      exp > 28)
    flag = 1;
  while (flag && exp > 0) {
    int two_last = get_last(result_big);
    int remainder = two_last % 10, even = two_last / 10;
    s21_div_big(result_big, (s21_big_decimal){{10u, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
                &result_big);
    if (even % 2 == 0 && remainder == 5) remainder--;
    if (remainder >= 5)
      s21_add_big(result_big,
                  (s21_big_decimal){{1u, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
                  &result_big);
    exp--;
    if (exp > 28 && big_is_zero(result_big))
      flag = 0;
    else if (not_normal(result_big))
      flag = 1;
    else if (get_last(result_big) % 10 == 0 && exp > 0)
      flag = 1;
    else if (exp > 28)
      flag = 1;
    else
      flag = 0;
  }
  if (!not_normal(result_big) && exp <= 28) {
    *result = (s21_decimal){{0, 0, 0, 0}};
    s21_set_exp(&result_big, exp);
    if (sign) s21_set_sign(&result_big);
    result->bits[0] = result_big.bits[0];
    result->bits[1] = result_big.bits[1];
    result->bits[2] = result_big.bits[2];
    result->bits[3] = result_big.bits[7];
  } else {
    if (exp == 0 && not_normal(result_big) && sign == 0)
      error = 1;
    else
      error = 2;
  }
  return error;
}

int get_last(s21_big_decimal value) {
  s21_big_decimal temp = value;
  s21_div_big(temp, (s21_big_decimal){{100u, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
              &temp);
  s21_mul_big(temp, (s21_big_decimal){{100u, 0, 0, 0, 0, 0, 0, 0}, 0, 0},
              &temp);
  s21_sub_big(value, temp, &temp);
  return temp.bits[0];
}

int not_normal(s21_big_decimal value) {
  int error = 0;
  for (int i = 3; i < 7; i++) {
    if (value.bits[i] != 0) error = 1;
  }
  return error;
}

s21_big_decimal clean_up() {
  s21_big_decimal new = {0};
  return new;
}

void set_exp(s21_decimal *result, int new_exp) {
  unsigned int mask = new_exp;
  mask = mask << 16;
  result->bits[3] = 0;
  result->bits[3] |= mask;
}

void set_sign(s21_decimal *value, int sign) {
  if (sign) {
    unsigned int mask = 1u << 31;
    value->bits[3] |= mask;
  }
}

int is_zero(s21_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) ? 1
                                                                          : 0;
}

int big_is_zero(s21_big_decimal value) {
  int flag = 1;
  for (int i = 0; i < 7; i++) {
    if (value.bits[i] != 0) flag = 0;
  }
  return flag;
}

// void print_decimal_bits(s21_big_decimal decimal){
//     for (int i = 32 * 8 -1; i >= 0; i--){
//         printf("%d", s21_get_bit(decimal, i));
//         if(i % 32 == 0) printf(" ");
//     }
//     printf("\n");
//     printf("exponent = %d\n", decimal.exp);
//     printf("sign = %d\n", decimal.sign);
//     printf("\n");
// }

// void print_decimal_bits_usual(s21_decimal decimal){
//     for (int i = 32 * 4 -1; i >= 0; i--){
//         printf("%d", s21_get_bit_small(decimal, i));
//         if(i % 32 == 0) printf(" ");
//     }
//     printf("\n");
// }