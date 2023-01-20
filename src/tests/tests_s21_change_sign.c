#include <check.h>

#include "../s21_decimal.h"

START_TEST(zero_decimal_set_31_bit_to_one) {
  s21_decimal decimal = S21_DECIMAL_NULL;

  s21_change_sign(&decimal);

  ck_assert_int_eq(decimal.bits[3], 1);  // Comparing with 1 cuz other bit 0
}
END_TEST

START_TEST(zero_negative_decimal_set_31_bit_to_zero) {
  s21_decimal decimal = S21_DECIMAL_NULL;
  s21_change_sign(&decimal);

  s21_change_sign(&decimal);  // Change sign twice

  ck_assert_int_eq(decimal.bits[3], 0);  // Comparing with 1 cuz other bit 0
}
END_TEST

// You may want rewrite it when decimal comparing will be ready
START_TEST(do_not_change_any_other_bits) {
  s21_decimal decimal = {{20, 2, 34, 30}};  // Other bits are filled
  s21_decimal same_value_decimal = {{20, 2, 34, 30}};

  s21_change_sign(&decimal);
  s21_change_sign(&decimal);

  ck_assert_int_eq(decimal.bits[0], same_value_decimal.bits[0]);
  ck_assert_int_eq(decimal.bits[1], same_value_decimal.bits[1]);
  ck_assert_int_eq(decimal.bits[2], same_value_decimal.bits[2]);
  ck_assert_int_eq(decimal.bits[3], same_value_decimal.bits[3]);
}
END_TEST

TCase *tcase_s21_change_sign(void) {
  TCase *tc;

  tc = tcase_create("Test for `s21_change_sign` implementation");

  tcase_add_test(tc, zero_decimal_set_31_bit_to_one);
  tcase_add_test(tc, zero_negative_decimal_set_31_bit_to_zero);
  tcase_add_test(tc, do_not_change_any_other_bits);

  return tc;
}
