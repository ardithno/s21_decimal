#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_floor_no_scale) {
  // 79228162514264337593543950335 floor = 79228162514264337593543950335
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_no_scale_minus) {
  // -79228162514264337593543950335 floor = -79228162514264337593543950335
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {
      .bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_whith_one_scale) {
  // 5.3 floor = 5
  s21_decimal x = {.bits = {53, 0, 0, 0x10000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_whith_one_scale_minus) {
  // -5.3 floor = -6
  s21_decimal x = {.bits = {53, 0, 0, 0x80010000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {6, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_whith_two_scale) {
  // 5.35 floor = 5
  s21_decimal x = {.bits = {535, 0, 0, 0x20000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_whith_two_scale_minus) {
  // -5.35 floor = -6
  s21_decimal x = {.bits = {535, 0, 0, 0x80020000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {6, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_whith_max_scale) {
  // 7.9228162514264337593543950335 floor = 7
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {7, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_whith_max_scale_minus) {
  // -7.9228162514264337593543950335 floor = -8
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x801c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {8, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_whith_min_number) {
  // 0.0000000000000000000000000001 floor = 0
  s21_decimal x = {.bits = {1, 0, 0, 0x1c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_whith_min_number_minus) {
  // -0.0000000000000000000000000001 floor = -1
  s21_decimal x = {.bits = {1, 0, 0, 0x801c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {1, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_whith_mid_number_minus) {
  // -0.01 floor = -1
  s21_decimal x = {.bits = {1, 0, 0, 0x80020000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {1, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_zero_whith_scale) {
  // 0.0000 floor = 0
  s21_decimal x = {.bits = {0, 0, 0, 0x40000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_zero_whith_scale_minus) {
  // -0.0000 floor = -0
  s21_decimal x = {.bits = {0, 0, 0, 0x80040000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_floor_30000) {
  // -3.0000 floor = -3
  s21_decimal x = {.bits = {0x7530, 0, 0, 0x80040000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {3, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_floor(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

TCase *tcase_s21_floor(void) {
  TCase *tc;

  tc = tcase_create("Tests for s21_floor");

  tcase_add_test(tc, test_floor_no_scale);
  tcase_add_test(tc, test_floor_no_scale_minus);

  tcase_add_test(tc, test_floor_whith_one_scale);
  tcase_add_test(tc, test_floor_whith_one_scale_minus);

  tcase_add_test(tc, test_floor_whith_two_scale);
  tcase_add_test(tc, test_floor_whith_two_scale_minus);

  tcase_add_test(tc, test_floor_whith_max_scale);
  tcase_add_test(tc, test_floor_whith_max_scale_minus);

  tcase_add_test(tc, test_floor_whith_min_number);
  tcase_add_test(tc, test_floor_whith_min_number_minus);

  tcase_add_test(tc, test_floor_whith_mid_number_minus);

  tcase_add_test(tc, test_floor_zero_whith_scale);
  tcase_add_test(tc, test_floor_zero_whith_scale_minus);

  tcase_add_test(tc, test_floor_30000);

  return tc;
}
