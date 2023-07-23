
#include <check.h>
#include <limits.h>

#include "s21_decimal.h"

s21_decimal first = {{0, 1, 2, 3}};
s21_decimal second = {{0, 3, 2, 1}};
START_TEST(add_dop_1) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b100;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 4
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b11;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b10000000000000000000000000000000;
  //  value = 3
  //  scale = 0
  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(add_1) {
  int exp1 = 0;
  int exp2 = 0;
  int sign1 = 0;
  int sign2 = 0;
  s21_decimal first = {{1, 0, 0, 0}};
  s21_decimal second = {{1, 0, 0, 0}};
  s21_decimal result = {0}, answer = {{2, 0, 0, 0}};

  set_exp(&first, exp1);
  set_sign(&first, sign1);
  set_exp(&second, exp2);
  set_sign(&second, sign2);

  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(add_2) {
  int exp1 = 0;
  int exp2 = 0;
  int sign1 = 1;
  int sign2 = 1;
  s21_decimal first = {{100000, 0, 0, 0}};
  s21_decimal second = {{154, 0, 0, 0}};
  s21_decimal result = {0}, answer = {{100154, 0, 0, 0}};

  set_exp(&first, exp1);
  set_sign(&first, sign1);
  set_exp(&second, exp2);
  set_sign(&second, sign2);
  set_exp(&answer, 0);
  set_sign(&answer, 1);

  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(add_3) {
  int exp1 = 1;
  int exp2 = 1;
  int sign1 = 1;
  int sign2 = 1;
  s21_decimal first = {{12345, 0, 0, 0}};
  s21_decimal second = {{54321, 0, 0, 0}};
  s21_decimal result = {0}, answer = {{66666, 0, 0, 0}};

  set_exp(&first, exp1);
  set_sign(&first, sign1);
  set_exp(&second, exp2);
  set_sign(&second, sign2);
  set_exp(&answer, 1);
  set_sign(&answer, 1);

  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(add_4) {
  int exp1 = 0;
  int exp2 = 0;
  int sign1 = 0;
  int sign2 = 0;
  s21_decimal first = {{0, 0, 0, 0}};
  s21_decimal second = {{0, 0, 0, 0}};
  s21_decimal result = {0}, answer = {{0, 0, 0, 0}};

  set_exp(&first, exp1);
  set_sign(&first, sign1);
  set_exp(&second, exp2);
  set_sign(&second, sign2);
  set_exp(&answer, 0);
  set_sign(&answer, 0);

  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(add_5) {
  int exp1 = 0;
  int exp2 = 0;
  int sign1 = 0;
  int sign2 = 0;
  s21_decimal first = {{4294967295, 0, 0, 0}};
  s21_decimal second = {{0, 0, 0, 0}};
  s21_decimal result = {0}, answer = {{4294967295, 0, 0, 0}};

  set_exp(&first, exp1);
  set_sign(&first, sign1);
  set_exp(&second, exp2);
  set_sign(&second, sign2);
  set_exp(&answer, 0);
  set_sign(&answer, 0);

  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(add_6) {
  int exp1 = 0;
  int exp2 = 0;
  int sign1 = 0;
  int sign2 = 0;
  s21_decimal first = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal second = {{4294967295, 0, 0, 0}};
  s21_decimal result = {0}, answer = {{0, 0, 0, 0}};

  set_exp(&first, exp1);
  set_sign(&first, sign1);
  set_exp(&second, exp2);
  set_sign(&second, sign2);
  set_exp(&answer, 0);
  set_sign(&answer, 0);

  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 1);
}
START_TEST(add_7) {
  int exp1 = 0;
  int exp2 = 0;
  int sign1 = 0;
  int sign2 = 0;
  s21_decimal first = {{0, 4294967295, 4294967295, 0}};
  s21_decimal second = {{4294967295, 0, 0, 0}};
  s21_decimal result = {0}, answer = {{4294967295, 4294967295, 4294967295, 0}};

  set_exp(&first, exp1);
  set_sign(&first, sign1);
  set_exp(&second, exp2);
  set_sign(&second, sign2);
  set_exp(&answer, 0);
  set_sign(&answer, 0);

  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(add_8) {
  int exp1 = 1;
  int exp2 = 1;
  int sign1 = 0;
  int sign2 = 0;
  s21_decimal first = {{5, 0, 0, 0}};
  s21_decimal second = {{5, 0, 0, 0}};
  s21_decimal result = {0}, answer = {{1, 0, 0, 0}};

  set_exp(&first, exp1);
  set_sign(&first, sign1);
  set_exp(&second, exp2);
  set_sign(&second, sign2);
  set_exp(&answer, 0);
  set_sign(&answer, 0);

  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(add_9) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b10101000110011111000010000011110;
  first.bits[1] = 0b100000100110001111100000000000;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000110000000000000000;
  //  value = 2348899887389574174
  //  scale = 3
  s21_decimal second = {0};
  second.bits[0] = 0b110111010111000;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000011000000000000000000;
  //  value = 28344
  //  scale = 12
  s21_decimal answer = {0};
  answer.bits[0] = 0b00100010010011000001101010111000;
  answer.bits[1] = 0b00001010111111011110010101111100;
  answer.bits[2] = 0b111100101101111011011100110;
  answer.bits[3] = 0b00000000000011000000000000000000;
  //  value = 2348899887389574174000028344
  //  scale = 3
  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(add_10) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b10101000110011111000010000011110;
  first.bits[1] = 0b100000100110001111100000000000;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000001010000000000000000;
  //  value = 2348899887389574174
  //  scale = 5
  s21_decimal second = {0};
  second.bits[0] = 0b00110101010110011011101011111100;
  second.bits[1] = 0b11001001011011100000001;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000011000000000000000000;
  //  value = 28348713488988924
  //  scale = 12
  s21_decimal answer = {0};
  answer.bits[0] = 0b10100110010101010101110111111100;
  answer.bits[1] = 0b00101110100101010101010101110101;
  answer.bits[2] = 0b100110110110111111101;
  answer.bits[3] = 0b00000000000011000000000000000000;
  //  value = 23488998902244455228988924
  //  scale = 12
  int f_code = s21_add(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
Suite* test_add(void) {
  Suite* s;
  TCase* tc;
  s = suite_create("s21_add");
  tc = tcase_create("case_add");
  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);
  tcase_add_test(tc, add_3);
  tcase_add_test(tc, add_4);
  tcase_add_test(tc, add_5);
  tcase_add_test(tc, add_6);
  tcase_add_test(tc, add_7);
  tcase_add_test(tc, add_8);
  tcase_add_test(tc, add_9);
  tcase_add_test(tc, add_10);
  tcase_add_test(tc, add_dop_1);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(sub_1) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1010;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 10
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b1001;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 9
  //  scale = 0
  int f_code = s21_sub(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(sub_2) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1010;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000111000000000000000000;
  //  value = 10
  //  scale = 28
  s21_decimal second = {0};
  second.bits[0] = 0b1010;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000111000000000000000000;
  //  value = 10
  //  scale = 28
  s21_decimal answer = {0};
  answer.bits[0] = 0b0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  int f_code = s21_sub(first, second, &result);

  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(sub_3) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1010;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 10
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b1001;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b10000000000000000000000000000000;
  //  value = 9
  //  scale = 0
  int f_code = s21_sub(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(sub_4) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b11111111111111111111111111111111;
  first.bits[1] = 0b11111111111111111111111111111111;
  first.bits[2] = 0b11111111111111111111111111111111;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 79228162514264337593543950335
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b110;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000010000000000000000;
  //  value = 6
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b11111111111111111111111111111110;
  answer.bits[1] = 0b11111111111111111111111111111111;
  answer.bits[2] = 0b11111111111111111111111111111111;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 79228162514264337593543950334
  //  scale = 0
  int f_code = s21_sub(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(sub_5) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b11111111111111111111111111111111;
  first.bits[1] = 0b11111111111111111111111111111111;
  first.bits[2] = 0b11111111111111111111111111111111;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 79228162514264337593543950335
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b100;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000010000000000000000;
  //  value = 4
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b11111111111111111111111111111111;
  answer.bits[1] = 0b11111111111111111111111111111111;
  answer.bits[2] = 0b11111111111111111111111111111111;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 79228162514264337593543950334
  //  scale = 0
  int f_code = s21_sub(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(sub_9) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b11111111111111111111111111111111;
  first.bits[1] = 0b11111111111111111111111111111111;
  first.bits[2] = 0b11111111111111111111111111111111;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 79228162514264337593543950335
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b100;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000010000000000000000;
  //  value = 4
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b11111111111111111111111111111111;
  answer.bits[1] = 0b11111111111111111111111111111111;
  answer.bits[2] = 0b11111111111111111111111111111111;
  answer.bits[3] = 0b10000000000000000000000000000000;
  //  value = 79228162514264337593543950334
  //  scale = 0
  int f_code = s21_sub(second, first, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(sub_6) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b100;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 4
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b101;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 5
  //  scale = 0
  int f_code = s21_sub(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(sub_7) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b100;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 4
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b101;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b10000000000000000000000000000000;
  //  value = 5
  //  scale = 0
  int f_code = s21_sub(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(sub_8) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b11111111111111111111111111111111;
  first.bits[1] = 0b11111111111111111111111111111111;
  first.bits[2] = 0b11111111111111111111111111111111;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 79228162514264337593543950335
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  int f_code = s21_sub(first, second, &result);
  // print_decimal_bits_usual(first);
  // print_decimal_bits_usual(second);
  // print_decimal_bits_usual(result);
  // print_decimal_bits_usual(answer);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 2);
}

START_TEST(sub_10) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b111010110111100110100010101;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000010100000000000000000;
  //  value = 123456789
  //  scale = 10
  s21_decimal second = {0};
  second.bits[0] = 0b111010110111100110100010101;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000010100000000000000000;
  //  value = 123456789
  //  scale = 10
  s21_decimal answer = {0};
  answer.bits[0] = 0b0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  int f_code = s21_sub(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

Suite* test_sub(void) {
  Suite* s;
  TCase* tc;
  s = suite_create("s21_sub");
  tc = tcase_create("case_sub");
  tcase_add_test(tc, sub_1);
  tcase_add_test(tc, sub_2);
  tcase_add_test(tc, sub_3);
  tcase_add_test(tc, sub_4);
  tcase_add_test(tc, sub_5);
  tcase_add_test(tc, sub_6);
  tcase_add_test(tc, sub_7);
  tcase_add_test(tc, sub_8);
  tcase_add_test(tc, sub_9);
  tcase_add_test(tc, sub_10);

  suite_add_tcase(s, tc);
  return s;
}
START_TEST(mul_1) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1010;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000010000000000000000;
  //  value = 10
  //  scale = 1
  s21_decimal second = {0};
  second.bits[0] = 0b1010;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000010000000000000000;
  //  value = 10
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b1;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  int f_code = s21_mul(first, second, &result);
  // print_decimal_bits_usual(first);
  // print_decimal_bits_usual(second);
  // print_decimal_bits_usual(result);
  // print_decimal_bits_usual(answer);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(mul_2) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b0;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  int f_code = s21_mul(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(mul_3) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b00101011110110110111011001110100;
  first.bits[1] = 0b00110100010001010010011101101110;
  first.bits[2] = 0b100111;
  first.bits[3] = 0b00000000000011000000000000000000;
  //  value = 723189478892173489780
  //  scale = 12
  s21_decimal second = {0};
  second.bits[0] = 0b10110101010110010111001110110000;
  second.bits[1] = 0b1000100010001110010100100;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000110000000000000000;
  //  value = 76874162384761776
  //  scale = 3
  s21_decimal answer = {0};
  answer.bits[0] = 0b11001010101110001000010111010100;
  answer.bits[1] = 0b01011110100111101000010101100110;
  answer.bits[2] = 0b10110011101000101100001101100011;
  answer.bits[3] = 0b00000000000001100000000000000000;
  //  value = 55594585435308193668520248788
  //  scale = 6
  int f_code = s21_mul(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(mul_4) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b11001;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000100000000000000000;
  //  value = 25
  //  scale = 2
  s21_decimal second = {0};
  second.bits[0] = 0b11001;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000100000000000000000;
  //  value = 25
  //  scale = 2
  s21_decimal answer = {0};
  answer.bits[0] = 0b1001110001;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000001000000000000000000;
  //  value = 625
  //  scale = 4
  int f_code = s21_mul(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(mul_5) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b11001;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000110000000000000000;
  //  value = 25
  //  scale = 3
  s21_decimal second = {0};
  second.bits[0] = 0b11001;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000010000000000000000;
  //  value = 25
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b1001110001;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000001000000000000000000;
  //  value = 625
  //  scale = 4
  int f_code = s21_mul(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(mul_6) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1001001100101100000001011010010;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000001110000000000000000;
  //  value = 1234567890
  //  scale = 7
  s21_decimal second = {0};
  second.bits[0] = 0b11110001001000000;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000110000000000000000;
  //  value = 123456
  //  scale = 3
  s21_decimal answer = {0};
  answer.bits[0] = 0b10101111000101001100111101000000;
  answer.bits[1] = 0b110111011100;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000010010000000000000000;
  //  value = 15241481342784
  //  scale = 9
  int f_code = s21_mul(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(mul_7) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000101000000000000000000;
  //  value = 1
  //  scale = 20
  s21_decimal second = {0};
  second.bits[0] = 0b1;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000101000000000000000000;
  //  value = 1
  //  scale = 20
  s21_decimal answer = {0};
  answer.bits[0] = 0b0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  int f_code = s21_mul(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 2);
}
START_TEST(mul_8) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b11111111111111111111111111111111;
  first.bits[1] = 0b11111111111111111111111111111111;
  first.bits[2] = 0b11111111111111111111111111111111;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 79228162514264337593543950335
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1010;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 10
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  int f_code = s21_mul(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 1);
}

START_TEST(mul_9) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b11111111111111111111111111111111;
  first.bits[1] = 0b11111111111111111111111111111111;
  first.bits[2] = 0b11111111111111111111111111111111;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 79228162514264337593543950335
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1010;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000000000000000000000;
  //  value = 10
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  int f_code = s21_mul(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 2);
}

Suite* test_mul(void) {
  Suite* s;
  TCase* tc;
  s = suite_create("s21_mul");
  tc = tcase_create("case_mul");
  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(div_1) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b11111111111111111111111111111111;
  first.bits[1] = 0b11111111111111111111111111111111;
  first.bits[2] = 0b11111111111111111111111111111111;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 79228162514264337593543950335
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b10;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 2
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b00000000000000000000000000000000;
  answer.bits[1] = 0b00000000000000000000000000000000;
  answer.bits[2] = 0b10000000000000000000000000000000;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 39614081257132168796771975168
  //  scale = 0
  int f_code = s21_div(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(div_2) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b10010010000101;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 9349
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b0;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  int f_code = s21_div(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 3);
}

START_TEST(div_3) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b10010010000101;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 9349
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b10011001101000;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000110000000000000000;
  //  value = 9832
  //  scale = 3
  s21_decimal answer = {0};
  answer.bits[0] = 0b10011010010001111010011110101110;
  answer.bits[1] = 0b11111000110011001110011100110101;
  answer.bits[2] = 0b11110101110010111001101111100;
  answer.bits[3] = 0b10000000000110010000000000000000;
  //  value = 9508746948738812042310821806
  //  scale = 25
  int f_code = s21_div(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(div_4) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b1;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  int f_code = s21_div(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(div_5) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b1;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  int f_code = s21_div(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(div_6) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b0;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b1;
  second.bits[1] = 0;
  second.bits[2] = 54;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 1
  //  scale = 0
  s21_decimal answer = {0};
  answer.bits[0] = 0b0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 0
  //  scale = 0
  int f_code = s21_div(first, second, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

Suite* test_div(void) {
  Suite* s;
  TCase* tc;
  s = suite_create("s21_div");
  tc = tcase_create("case_div");
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(less_1) {
  s21_decimal first = {0};
  first.bits[0] = 0b1001001100101100000001011010010;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000110000000000000000;
  //  value = 1234567890
  //  scale = 3
  s21_decimal second = {0};
  second.bits[0] = 0b100101101011010000111;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 1234567
  //  scale = 0
  int f_code = s21_is_less(first, second);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(less_11) {
  s21_decimal first = {0};
  first.bits[0] = 0b1001001100101100000001011010010;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1234567890
  //  scale = 3
  s21_decimal second = {0};
  second.bits[0] = 0b100101101011010000111;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1234567
  //  scale = 0
  int f_code = s21_is_less(first, second);
  ck_assert_int_eq(f_code, 1);
}
START_TEST(less_2) {
  s21_decimal first = {0};
  first.bits[0] = 0b11000000111001;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 12345
  //  scale = 0
  s21_decimal second = {0};
  second.bits[0] = 0b11110001001000000;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000010000000000000000;
  //  value = 123456
  //  scale = 1
  int f_code = s21_is_less(first, second);
  ck_assert_int_eq(f_code, 1);
}
START_TEST(less_3) {
  s21_decimal first = {0};
  first.bits[0] = 0b11110001001000000;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000010000000000000000;
  //  value = 123456
  //  scale = 1
  s21_decimal second = {0};
  second.bits[0] = 0b11110001001000000;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000010000000000000000;
  //  value = 123456
  //  scale = 1
  int f_code = s21_is_less(first, second);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(less_4) {
  s21_decimal first = {0};
  first.bits[0] = 0b11110001001000000111111;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000010000000000000000;
  //  value = 123456
  //  scale = 1
  s21_decimal second = {0};
  second.bits[0] = 0b111100010010000001;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000010000000000000000;
  //  value = 123456
  //  scale = 1
  int f_code = s21_is_less(first, second);
  ck_assert_int_eq(f_code, 1);
}
START_TEST(less_eq1) {
  s21_decimal first = {0};
  first.bits[0] = 0b11110001001000000;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000010000000000000000;
  //  value = 123456
  //  scale = 1
  s21_decimal second = {0};
  second.bits[0] = 0b11110001001000000;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000010000000000000000;
  //  value = 123456
  //  scale = 1
  int f_code = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(f_code, 1);
}

START_TEST(less_eq2) {
  s21_decimal first = {0};
  first.bits[0] = 0b11110001001000000;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000010000000000000000;
  //  value = 123456
  //  scale = 1
  s21_decimal second = {0};
  second.bits[0] = 0b11110001001000000;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000010000000000000000;
  //  value = 123456
  //  scale = 1
  int f_code = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(less_eq3) {
  s21_decimal first = {0};
  first.bits[0] = 0b11110001001000000;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 123456
  //  scale = 1
  s21_decimal second = {0};
  second.bits[0] = 0b111100101001000000;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000000000000000000000;
  //  value = 123456
  //  scale = 1
  int f_code = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(f_code, 0);
}
Suite* test_less(void) {
  Suite* s;
  TCase* tc;
  s = suite_create("s21_less");
  tc = tcase_create("case_less");
  tcase_add_test(tc, less_1);
  tcase_add_test(tc, less_2);
  tcase_add_test(tc, less_3);
  tcase_add_test(tc, less_4);
  tcase_add_test(tc, less_11);
  tcase_add_test(tc, less_eq1);
  tcase_add_test(tc, less_eq2);
  tcase_add_test(tc, less_eq3);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(greater_1) {
  s21_decimal first = {0};
  first.bits[0] = 12345;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1234567890
  //  scale = 3
  s21_decimal second = {0};
  second.bits[0] = 12345;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1234567
  //  scale = 0
  int f_code = s21_is_greater(first, second);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(greater_2) {
  s21_decimal first = {0};
  first.bits[0] = 0b01000111010111101000010011001111;
  first.bits[1] = 0b100011000001100000111110011;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000001010000000000000000;
  //  value = 315465224534525135
  //  scale = 5
  s21_decimal second = {0};
  second.bits[0] = 0b10110111101110100000111011110000;
  second.bits[1] = 0b101100111001;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000110000000000000000;
  //  value = 12342523465456
  //  scale = 3
  int f_code = s21_is_greater(first, second);
  ck_assert_int_eq(f_code, 1);
}

START_TEST(greater_3) {
  s21_decimal first = {0};
  first.bits[0] = 0b01000111010111101000010011001111;
  first.bits[1] = 0b100011000001100000111110011;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000001010000000000000000;
  //  value = 315465224534525135
  //  scale = 5
  s21_decimal second = {0};
  second.bits[0] = 0b10110111101110100000111011110000;
  second.bits[1] = 0b101100111001;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000110000000000000000;
  //  value = 12342523465456
  //  scale = 3
  int f_code = s21_is_greater(first, second);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(greater_4) {
  s21_decimal first = {0};
  first.bits[0] = 12345;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1234567890
  //  scale = 3
  s21_decimal second = {0};
  second.bits[0] = 12345;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1234567
  //  scale = 0
  int f_code = s21_is_greater_or_equal(first, second);
  ck_assert_int_eq(f_code, 1);
}
START_TEST(greater_5) {
  s21_decimal first = {0};
  first.bits[0] = 12345;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 1234567890
  //  scale = 3
  s21_decimal second = {0};
  second.bits[0] = 12345;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0b00000000000000000000000000000000;
  //  value = 1234567
  //  scale = 0
  int f_code = s21_is_greater_or_equal(first, second);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(greater_6) {
  s21_decimal first = {0};
  first.bits[0] = 12345;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 1234567890
  //  scale = 3
  s21_decimal second = {0};
  second.bits[0] = 125;
  second.bits[1] = 0;
  second.bits[2] = 0;
  second.bits[3] = 0000000000000000000000000000000000;
  //  value = 1234567
  //  scale = 0
  int f_code = s21_is_greater_or_equal(first, second);
  ck_assert_int_eq(f_code, 1);
}

Suite* test_greater(void) {
  Suite* s;
  TCase* tc;
  s = suite_create("s21_greater");
  tc = tcase_create("case_greater");
  tcase_add_test(tc, greater_1);
  tcase_add_test(tc, greater_2);
  tcase_add_test(tc, greater_3);
  tcase_add_test(tc, greater_4);
  tcase_add_test(tc, greater_5);
  tcase_add_test(tc, greater_6);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(equal_1) {
  s21_decimal first = {0};
  first.bits[0] = 0b01000111010111101000010011001111;
  first.bits[1] = 0b100011000001100000111110011;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000011000000000000000000;
  //  value = 315465224534525135
  //  scale = 12
  s21_decimal second = {0};
  second.bits[0] = 0b01000111010111101000010011001111;
  second.bits[1] = 0b100011000001100000111110011;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000011000000000000000000;
  //  value = 315465224534525135
  //  scale = 12
  int f_code = s21_is_equal(first, second);
  ck_assert_int_eq(f_code, 1);
}
START_TEST(equal_2) {
  s21_decimal first = {0};
  first.bits[0] = 0b01000111010111101000010011001111;
  first.bits[1] = 0b100011000001100000111110011;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000011000000000000000000;
  //  value = 315465224534525135
  //  scale = 12
  s21_decimal second = {0};
  second.bits[0] = 0b01000111010111101000010011001111;
  second.bits[1] = 0b100011000001100000111110011;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000011000000000000000000;
  //  value = 315465224534525135
  //  scale = 12
  int f_code = s21_is_not_equal(first, second);
  ck_assert_int_eq(f_code, 1);
}
START_TEST(equal_3) {
  s21_decimal first = {0};
  first.bits[0] = 0b01000111010111101000010011001111;
  first.bits[1] = 0b100011000001100000111110011;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000011000000000000000000;
  //  value = 315465224534525135
  //  scale = 12
  s21_decimal second = {0};
  second.bits[0] = 0b01000111010111101000010011001111;
  second.bits[1] = 0b100011000001100000111110011;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000011000000000000000000;
  //  value = 315465224534525135
  //  scale = 12
  int f_code = s21_is_not_equal(first, second);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(equal_4) {
  s21_decimal first = {0};
  first.bits[0] = 0b01000111010111101000010011001111;
  first.bits[1] = 0b100011000001100000111110011;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000011000000000000000000;
  //  value = 315465224534525135
  //  scale = 12
  s21_decimal second = {0};
  second.bits[0] = 0b01000111010111101000010011001111;
  second.bits[1] = 0b100011000001100000111110011;
  second.bits[2] = 0;
  second.bits[3] = 0b10000000000011000000000000000000;
  //  value = 315465224534525135
  //  scale = 12
  int f_code = s21_is_equal(first, second);
  ck_assert_int_eq(f_code, 0);
}
Suite* test_equal_and_not(void) {
  Suite* s;
  TCase* tc;
  s = suite_create("s21_inequality");
  tc = tcase_create("case_inequality");
  tcase_add_test(tc, equal_1);
  tcase_add_test(tc, equal_2);
  tcase_add_test(tc, equal_3);
  tcase_add_test(tc, equal_4);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(int_dec_1) {
  int a = INT_MAX;
  unsigned result = a;
  unsigned sign = 0b00000000000000000000000000000000;
  s21_decimal value = {0};
  s21_from_int_to_decimal(a, &value);
  ck_assert_int_eq(result, value.bits[0]);
  ck_assert_int_eq(sign, value.bits[3]);
}
END_TEST

START_TEST(int_dec_2) {
  int a = INT_MIN;
  unsigned result = a * (-1);
  unsigned sign = 0b10000000000000000000000000000000;
  s21_decimal value = {0};
  s21_from_int_to_decimal(a, &value);
  ck_assert_int_eq(result, value.bits[0]);
  ck_assert_int_eq(sign, value.bits[3]);
}
END_TEST

START_TEST(int_dec_3) {
  int a = 0;
  unsigned result = a;
  unsigned sign = 0b00000000000000000000000000000000;
  s21_decimal value = {0};
  s21_from_int_to_decimal(a, &value);
  ck_assert_int_eq(result, value.bits[0]);
  ck_assert_int_eq(sign, value.bits[3]);
}
END_TEST

START_TEST(dec_to_int_1) {
  int a = INT_MAX, b;
  s21_decimal value = {0};
  s21_from_int_to_decimal(a, &value);
  int code = s21_from_decimal_to_int(value, &b);

  ck_assert_int_eq(a, b);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(dec_to_int_2) {
  int a = INT_MIN, b;
  s21_decimal value = {0};
  s21_from_int_to_decimal(a, &value);
  int code = s21_from_decimal_to_int(value, &b);

  ck_assert_int_eq(a, b);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(dec_to_int_3) {
  int a = INT_MIN, b;
  s21_decimal value = {0};
  s21_from_int_to_decimal(a, &value);
  value.bits[1] = 1u;
  int code = s21_from_decimal_to_int(value, &b);

  ck_assert_int_eq(0, b);
  ck_assert_int_eq(code, 1);
}
END_TEST
START_TEST(dec_to_int_4) {
  int a = 0, b;
  s21_decimal value = {0};
  s21_from_int_to_decimal(a, &value);
  int code = s21_from_decimal_to_int(value, &b);

  ck_assert_int_eq(a, b);
  ck_assert_int_eq(code, 0);
}
END_TEST

Suite* test_int_dec(void) {
  Suite* s;
  TCase* tc;
  s = suite_create("s21_converter_int");
  tc = tcase_create("case_converter_int");
  tcase_add_test(tc, int_dec_1);
  tcase_add_test(tc, int_dec_2);
  tcase_add_test(tc, int_dec_3);
  tcase_add_test(tc, dec_to_int_1);
  tcase_add_test(tc, dec_to_int_2);
  tcase_add_test(tc, dec_to_int_3);
  tcase_add_test(tc, dec_to_int_4);
  suite_add_tcase(s, tc);
  return s;
}

/////////////////////////////////////////////////////

START_TEST(floor_1) {
  s21_decimal first = {0};
  first.bits[0] = 0b01000111010111101000010011001111;
  first.bits[1] = 0b100011000001100000111110011;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000010000000000000000;
  //  value = 315465224534525135
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b00100000101111001010011011100001;
  answer.bits[1] = 0b11100000001001101100101;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 31546522453452513
  //  scale = 0
  s21_decimal result = {0};
  int f_code = s21_floor(first, &result);
  ck_assert_int_eq(f_code, 0);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal first = {0};
  first.bits[0] = 0b01000111010111101000010011001111;
  first.bits[1] = 0b100011000001100000111110011;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000010000000000000000;
  //  value = 315465224534525135
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b00100000101111001010011011100010;
  answer.bits[1] = 0b11100000001001101100101;
  answer.bits[2] = 0;
  answer.bits[3] = 0b10000000000000000000000000000000;
  //  value = 31546522453452514
  //  scale = 0
  s21_decimal result = {0};
  int f_code = s21_floor(first, &result);
  ck_assert_int_eq(f_code, 0);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal first = {0};
  first.bits[0] = 0b01000111010111101000010011001111;
  first.bits[1] = 0b100011000001100000111110011;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 315465224534525135
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b01000111010111101000010011001111;
  answer.bits[1] = 0b100011000001100000111110011;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 315465224534525135
  //  scale = 0
  s21_decimal result = {0};
  int f_code = s21_floor(first, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
END_TEST

START_TEST(round_1) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1111;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000010000000000000000;
  //  value = 15
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b10;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 2
  //  scale = 0
  int f_code = s21_round(first, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(round_2) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b1111;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000010000000000000000;
  //  value = 15
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b10;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b10000000000000000000000000000000;
  //  value = 2
  //  scale = 0
  int f_code = s21_round(first, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(round_3) {
  s21_decimal result = {0};
  s21_decimal first = {0};
  first.bits[0] = 0b11001;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000010000000000000000;
  //  value = 25
  //  scale = 1
  s21_decimal answer = {0};
  answer.bits[0] = 0b10;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 2
  //  scale = 0
  int f_code = s21_round(first, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
START_TEST(trun_1) {
  s21_decimal result = {0};

  s21_decimal first = {0};
  first.bits[0] = 0b10111101000111100101000100000110;
  first.bits[1] = 0b10001;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000110000000000000000;
  //  value = 76187324678
  //  scale = 3

  s21_decimal answer = {0};
  answer.bits[0] = 0b100100010101000011010111100;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 76187324
  //  scale = 0
  int f_code = s21_truncate(first, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(trun_2) {
  s21_decimal result = {0};

  s21_decimal first = {0};
  first.bits[0] = 0b10111101000111100101000100000110;
  first.bits[1] = 0b10001;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000011110000000000000000;
  //  value = 76187324678
  //  scale = 3

  s21_decimal answer = {0};
  answer.bits[0] = 0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 76187324
  //  scale = 0
  int f_code = s21_truncate(first, &result);
  ck_assert_int_eq(result.bits[0], answer.bits[0]);
  ck_assert_int_eq(result.bits[1], answer.bits[1]);
  ck_assert_int_eq(result.bits[2], answer.bits[2]);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(negate_1) {
  s21_decimal result = {0};

  s21_decimal first = {0};
  first.bits[0] = 0;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000000000000000000000;
  //  value = 76187324678
  //  scale = 3

  s21_decimal answer = {0};
  answer.bits[0] = 0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b00000000000000000000000000000000;
  //  value = 76187324
  //  scale = 0
  int f_code = s21_negate(first, &result);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}

START_TEST(negate_2) {
  s21_decimal result = {0};

  s21_decimal first = {0};
  first.bits[0] = 0;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000000000000000000000;
  //  value = 76187324678
  //  scale = 3

  s21_decimal answer = {0};
  answer.bits[0] = 0;
  answer.bits[1] = 0;
  answer.bits[2] = 0;
  answer.bits[3] = 0b10000000000000000000000000000000;
  //  value = 76187324
  //  scale = 0
  int f_code = s21_negate(first, &result);
  ck_assert_int_eq(result.bits[3], answer.bits[3]);
  ck_assert_int_eq(f_code, 0);
}
Suite* test_round_floor_trun(void) {
  Suite* s;
  TCase* tc;
  s = suite_create("s21_converter_int");
  tc = tcase_create("case_converter_int");
  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, round_1);
  tcase_add_test(tc, round_2);
  tcase_add_test(tc, round_3);
  tcase_add_test(tc, trun_1);
  tcase_add_test(tc, trun_2);
  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(float_dec_dop1) {
  float a = 1E-28f;
  s21_decimal second = {0};
  int fcode = s21_from_float_to_decimal(a, &second);
  s21_decimal first = {0};
  first.bits[0] = 1;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000111000000000000000000;

  //  value = 1234567
  //  scale = 3
  ck_assert_int_eq(first.bits[0], second.bits[0]);
  ck_assert_int_eq(first.bits[3], second.bits[3]);
  ck_assert_int_eq(fcode, 0);
}
END_TEST
START_TEST(float_dec_dop2) {
  float a = 717212092000000.f;
  s21_decimal second = {0};
  int fcode = s21_from_float_to_decimal(a, &second);
  s21_decimal first = {0};
  first.bits[0] = 0b11110100011100101111100100000000;
  first.bits[1] = 0b00000000000000101000110001001100;
  first.bits[2] = 0;
  first.bits[3] = 0;

  //  value = 1234567
  //  scale = 3
  ck_assert_int_eq(first.bits[0], second.bits[0]);
  ck_assert_int_eq(first.bits[3], second.bits[3]);
  ck_assert_int_eq(fcode, 0);
}
END_TEST

START_TEST(float_dec_1) {
  float a = 1234.5678910;
  s21_decimal second = {0};
  int fcode = s21_from_float_to_decimal(a, &second);
  s21_decimal first = {0};
  first.bits[0] = 0b100101101011010001000;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000110000000000000000;
  //  value = 1234567
  //  scale = 3
  ck_assert_int_eq(first.bits[0], second.bits[0]);
  ck_assert_int_eq(first.bits[3], second.bits[3]);
  ck_assert_int_eq(fcode, 0);
}
END_TEST

START_TEST(float_dec_2) {
  float a = -1234.5678910;
  s21_decimal second = {0};
  int fcode = s21_from_float_to_decimal(a, &second);
  s21_decimal first = {0};
  first.bits[0] = 0b100101101011010001000;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b10000000000000110000000000000000;
  //  value = 1234567
  //  scale = 3
  ck_assert_int_eq(first.bits[0], second.bits[0]);
  ck_assert_int_eq(first.bits[3], second.bits[3]);
  ck_assert_int_eq(fcode, 0);
}
END_TEST

START_TEST(dec_float_1) {
  float a = 1234.567;
  float result;
  s21_decimal first = {0};
  first.bits[0] = 0b100101101011010000111;
  first.bits[1] = 0;
  first.bits[2] = 0;
  first.bits[3] = 0b00000000000000110000000000000000;
  //  value = 1234567
  //  scale = 3
  int fcode = s21_from_decimal_to_float(first, &result);
  ck_assert_float_eq(result, a);
  // ck_assert_int_eq(first.bits[3], second.bits[3]);
  ck_assert_int_eq(fcode, 0);
}
END_TEST

Suite* test_float_dec(void) {
  Suite* s;
  TCase* tc;
  s = suite_create("s21_converter_float");
  tc = tcase_create("case_converter_float");
  tcase_add_test(tc, float_dec_1);
  tcase_add_test(tc, float_dec_2);
  tcase_add_test(tc, dec_float_1);
  tcase_add_test(tc, float_dec_dop1);
  tcase_add_test(tc, float_dec_dop2);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  int failed = 0;
  Suite* s21_decimal_tests[] = {test_add(),
                                test_sub(),
                                test_mul(),
                                test_div(),
                                test_less(),
                                test_greater(),
                                test_equal_and_not(),
                                test_int_dec(),
                                test_float_dec(),
                                test_round_floor_trun(),
                                NULL};

  for (int i = 0; s21_decimal_tests[i] != NULL; i++) {  // (&& failed == 0)
    SRunner* sr = srunner_create(s21_decimal_tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    printf("\n");

    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
// printf("TEST #%ld\n", i);
// printf("my_result:\n");
// print_decimal_bits_usual(tmp);
// printf("c# result:\n");
// print_decimal_bits_usual(result[i]);
// printf("\n");
