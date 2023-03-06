#include <check.h>

#include "../s21_decimal.h"

_s21_big_decimal big_decimal;
int is_big_equal;

void setup_test__s21_decimal_to_big_decimal(void) {
  // Set any not zero but predefined value to big_decimal
  big_decimal = (_s21_big_decimal){{900, 900, 900, 900, 900, 900, 900, 0}};

  // Set equality to any non zero
  is_big_equal = 999;
}

int _is_two_big_decimals_equal(_s21_big_decimal const *first_ptr,
                               _s21_big_decimal const *second_ptr) {
  return (_s21_big_decimal_compare(first_ptr, second_ptr) == 0) ? S21_TRUE
                                                                : S21_FALSE;
}

START_TEST(zero_is_converted_to_big_zero) {
  s21_decimal decimal = S21_DECIMAL_NULL;
  _s21_big_decimal big_zero = S21_DECIMAL_NULL;

  _s21_decimal_to_big_decimal(&decimal, &big_decimal);

  is_big_equal = _is_two_big_decimals_equal(&big_decimal, &big_zero);
  ck_assert_int_eq(is_big_equal, S21_TRUE);
}
END_TEST

START_TEST(negative_zero_is_converted_to_negative_big_zero) {
  s21_decimal negative_zero = {{0, 0, 0, 0x80000000}};
  _s21_big_decimal big_negative_zero = {{0, 0, 0, 0, 0, 0, 0, 0x80000000}};

  _s21_decimal_to_big_decimal(&negative_zero, &big_decimal);

  is_big_equal = _is_two_big_decimals_equal(&big_decimal, &big_negative_zero);
  ck_assert_int_eq(is_big_equal, S21_TRUE);
}
END_TEST

START_TEST(max_decimal_converted_without_overflow) {
  s21_decimal max_decimal = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  _s21_big_decimal converted_big_decimal = S21_DECIMAL_NULL;
  _s21_big_decimal expected = {.bits = {0xf0000000, 0xc1dafd9e, 0xdfb031a1,
                                        0xfffffff, 0x3e250261, 0x204fce5e, 0,
                                        0}};
  int is_equal = 99;

  _s21_decimal_to_big_decimal(&max_decimal, &converted_big_decimal);

  is_equal = _s21_big_decimal_compare_bits(&converted_big_decimal, &expected);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
}
END_TEST

START_TEST(same_decimals_different_scale_converts_to_same_values) {
  s21_decimal decimal = {{0xffffffff, 0, 0, 0}};
  s21_decimal decimal_scale_one = {{0xfffffff6, 0x9, 0, 0x10000}};  // scale 1

  _s21_big_decimal big;
  _s21_big_decimal big_from_scale_one;
  _s21_decimal_to_big_decimal(&decimal, &big);
  _s21_decimal_to_big_decimal(&decimal_scale_one, &big_from_scale_one);

  is_big_equal = _is_two_big_decimals_equal(&big, &big_from_scale_one);

  ck_assert_int_eq(is_big_equal, S21_TRUE);
}

START_TEST(save_scale_in_same_way_as_decimal) {
  s21_decimal decimal_scale_one = {{0xfffffff6, 0x9, 0, 0x10000}};  // scale 1

  _s21_big_decimal big_from_scale_one;
  _s21_decimal_to_big_decimal(&decimal_scale_one, &big_from_scale_one);

  ck_assert_int_eq(big_from_scale_one.bits[BIG_SCALE], 0x10000);
}

TCase *tcase__s21_decimal_to_big_decimal(void) {
  TCase *tc;

  tc = tcase_create("Tests for _s21_decimal_to_big_decimal");
  tcase_add_checked_fixture(tc, setup_test__s21_decimal_to_big_decimal, NULL);

  tcase_add_test(tc, zero_is_converted_to_big_zero);
  tcase_add_test(tc, negative_zero_is_converted_to_negative_big_zero);
  tcase_add_test(tc, max_decimal_converted_without_overflow);
  tcase_add_test(tc, same_decimals_different_scale_converts_to_same_values);
  tcase_add_test(tc, save_scale_in_same_way_as_decimal);

  return tc;
}
