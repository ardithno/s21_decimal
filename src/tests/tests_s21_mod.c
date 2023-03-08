#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_return_the_value_itself_if_divider_bigger) {
  // 0.0000000000007 % 0.0000000000001 = 0.0000000000001
  s21_decimal x = {.bits = {1, 0, 0, 0xd0000}};
  s21_decimal y = {.bits = {7, 0, 0, 0xd0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {1, 0, 0, 0xd0000}};  // same as x
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_return_the_zero_with_desired_scale_if_reminder_empty) {
  // 0.0000000000001 % 0.0000000000007 = 0.0000000000000
  s21_decimal x = {.bits = {7, 0, 0, 0xd0000}};
  s21_decimal y = {.bits = {1, 0, 0, 0xd0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0xd0000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(negative_modulo_return_negative) {
  // -218218.87 % -2172182112.29 = -218218.87
  s21_decimal x = {.bits = {0x014CF9BF, 0, 0, 0x80020000}};
  s21_decimal y = {.bits = {0x9336DD9D, 0x00000032, 0, 0x80020000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0x014CF9BF, 0, 0, 0x80020000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(regular_case_when_there_is_int_part_in_division) {
  // 0.00000000000122121 % 0.000000000000000000000922121
  // = 0.000000000000000000000668267
  s21_decimal x = {.bits = {0x0001DD09, 0, 0, 0x00110000}};
  s21_decimal y = {.bits = {0x000E1209, 0, 0, 0x001B0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0x000A326B, 0, 0, 0x001B0000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(regular_case_overflow_not_happen_with_big_values) {
  // 79228162514264337593543.950335 % 80000000000000000000.11111111
  // = 28162514264337593433.95033610
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x60000}};
  s21_decimal y = {.bits = {0x40a98ac7, 0xfe8401e7, 0x19d971e4, 0x80000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {{0xf059520a, 0xbd80a3b3, 0x9198c6f, 0x80000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(negative_on_positive_return_negative) {
  // -939443843942303.1221404929 % 128.00001281
  // = 28162514264337593433.9503361
  s21_decimal x = {.bits = {0xe26bc501, 0x873c632e, 0x7c559, 0x800a0000}};
  s21_decimal y = {.bits = {0xfaf08501, 0x2, 0, 0x80000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {{0xee33fcad, 0x7d, 0, 0x800a0000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(positive_on_negative_return_positive) {
  // 19.3 % -6.45 = 6.40
  s21_decimal x = {.bits = {0xc1, 0, 0, 0x10000}};
  s21_decimal y = {.bits = {0x285, 0, 0, 0x80020000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0x280, 0, 0, 0x20000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

TCase *tcase_s21_mod(void) {
  TCase *tc;

  tc = tcase_create("Tests for s21_mod");

  tcase_add_test(tc, test_return_the_value_itself_if_divider_bigger);
  tcase_add_test(tc, test_return_the_zero_with_desired_scale_if_reminder_empty);
  tcase_add_test(tc, negative_modulo_return_negative);
  tcase_add_test(tc, regular_case_when_there_is_int_part_in_division);
  tcase_add_test(tc, regular_case_overflow_not_happen_with_big_values);
  tcase_add_test(tc, negative_on_positive_return_negative);
  tcase_add_test(tc, positive_on_negative_return_positive);

  return tc;
}