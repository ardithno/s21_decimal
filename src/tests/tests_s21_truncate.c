#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_truncate_no_scale) {
  // 79228162514264337593543950335 truncate = 79228162514264337593543950335
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_no_scale_minus) {
  // -79228162514264337593543950335 truncate = -79228162514264337593543950335
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {
      .bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_whith_one_scale) {
  // 5.3 truncate = 5
  s21_decimal x = {.bits = {53, 0, 0, 0x10000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_whith_one_scale_minus) {
  // -5.3 truncate = -5
  s21_decimal x = {.bits = {53, 0, 0, 0x80010000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_whith_two_scale) {
  // 5.35 truncate = 5
  s21_decimal x = {.bits = {535, 0, 0, 0x20000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_whith_two_scale_minus) {
  // -5.35 truncate = -5
  s21_decimal x = {.bits = {535, 0, 0, 0x80020000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_whith_max_scale) {
  // 7.9228162514264337593543950335 truncate = 7
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {7, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_whith_max_scale_minus) {
  // -7.9228162514264337593543950335 truncate = -7
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x801c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {7, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_whith_min_number) {
  // 0.0000000000000000000000000001 truncate = 0
  s21_decimal x = {.bits = {1, 0, 0, 0x1c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_whith_min_number_minus) {
  // -0.0000000000000000000000000001 truncate = -0
  s21_decimal x = {.bits = {1, 0, 0, 0x801c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_zero_whith_scale) {
  // 0.0000 truncate = 0
  s21_decimal x = {.bits = {0, 0, 0, 0x40000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_truncate_zero_whith_scale_minus) {
  // -0.0000 truncate = -0
  s21_decimal x = {.bits = {0, 0, 0, 0x80040000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

TCase *tcase_s21_truncate(void) {
  TCase *tc;

  tc = tcase_create("Tests for s21_truncate");

  tcase_add_test(tc, test_truncate_no_scale);
  tcase_add_test(tc, test_truncate_no_scale_minus);

  tcase_add_test(tc, test_truncate_whith_one_scale);
  tcase_add_test(tc, test_truncate_whith_one_scale_minus);

  tcase_add_test(tc, test_truncate_whith_two_scale);
  tcase_add_test(tc, test_truncate_whith_two_scale_minus);

  tcase_add_test(tc, test_truncate_whith_max_scale);
  tcase_add_test(tc, test_truncate_whith_max_scale_minus);

  tcase_add_test(tc, test_truncate_whith_min_number);
  tcase_add_test(tc, test_truncate_whith_min_number_minus);

  tcase_add_test(tc, test_truncate_zero_whith_scale);
  tcase_add_test(tc, test_truncate_zero_whith_scale_minus);

  return tc;
}
