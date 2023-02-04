#include <check.h>

#include "../s21_decimal.h"

START_TEST(zero_scale_return_zero) {
  s21_decimal x = S21_DECIMAL_NULL;
  uint8_t scale = 99;  // Any not possible value

  scale = _s21_get_scale(&x);

  ck_assert_int_eq(scale, 0);
}
END_TEST

START_TEST(one_scale_return_one) {
  s21_decimal x = {{0, 0, 0, 0b00000000000000010000000000000000}};  // scale 1
  uint8_t scale = 99;  // Any not possible value

  scale = _s21_get_scale(&x);

  ck_assert_int_eq(scale, 1);
}
END_TEST

START_TEST(twenty_eight_scale_return_twenty_eight) {
  s21_decimal x = {{0, 0, 0, 0b00000000000111000000000000000000}};  // scale 28
  uint8_t scale = 99;  // Any not possible value

  scale = _s21_get_scale(&x);

  ck_assert_int_eq(scale, 28);
}
END_TEST

START_TEST(ten_scale_return_twenty_ten) {
  s21_decimal x = {{0, 0, 0, 0b00000000000010100000000000000000}};  // scale 10
  uint8_t scale = 99;  // Any not possible value

  scale = _s21_get_scale(&x);

  ck_assert_int_eq(scale, 10);
}
END_TEST

START_TEST(negative_sign_doesnt_matter) {
  s21_decimal x = {{0, 0, 0, 0b00000000000010100000000000000000}};  // scale 10
  s21_change_sign(&x);  // set sign to negative value
  uint8_t scale = 99;   // Any not possible value

  scale = _s21_get_scale(&x);

  ck_assert_int_eq(scale, 10);
}
END_TEST

START_TEST(any_garbage_after_scale_doesnt_matter) {
  // x with scale 10 and some garbage (one) in bits that should 0
  s21_decimal x = {{0, 0, 0, 0b00000000000010101111111111111111}};
  uint32_t scale = 99;  // Any not possible value

  scale = _s21_get_scale(&x);

  ck_assert_int_eq(scale, 10);
}
END_TEST

TCase *tcase__s21_get_scale(void) {
  TCase *tc;

  tc = tcase_create("Tests for internal _s21_get_scale");

  tcase_add_test(tc, zero_scale_return_zero);
  tcase_add_test(tc, one_scale_return_one);
  tcase_add_test(tc, twenty_eight_scale_return_twenty_eight);
  tcase_add_test(tc, ten_scale_return_twenty_ten);
  tcase_add_test(tc, negative_sign_doesnt_matter);
  tcase_add_test(tc, any_garbage_after_scale_doesnt_matter);

  return tc;
}
