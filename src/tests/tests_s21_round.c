#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_round_no_scale) {
  // 79228162514264337593543950335 round = 79228162514264337593543950335
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_no_scale_minus) {
  // -79228162514264337593543950335 round = -79228162514264337593543950335
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_one_scale) {
  // 5.3 round = 5
  s21_decimal x = {.bits = {53, 0, 0, 0x10000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_one_scale_minus) {
  // -5.3 round = -5
  s21_decimal x = {.bits = {53, 0, 0, 0x80010000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_two_scale) {
  // 5.35 round = 5
  s21_decimal x = {.bits = {535, 0, 0, 0x20000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_two_scale_minus) {
  // -5.35 round = -5
  s21_decimal x = {.bits = {535, 0, 0, 0x80020000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_three_scale) {
  // 5.555 round = 6
  s21_decimal x = {.bits = {5555, 0, 0, 0x30000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {6, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_three_scale_minus) {
  // -5.555 round = -6
  s21_decimal x = {.bits = {5555, 0, 0, 0x80030000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {6, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_545_scale) {
  // 5.45 round = 5
  s21_decimal x = {.bits = {545, 0, 0, 0x20000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_545_scale_minus) {
  // -5.45 round = -5
  s21_decimal x = {.bits = {545, 0, 0, 0x80020000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_max_scale) {
  // 7.9228162514264337593543950335 round = 7
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {8, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_max_scale_minus) {
  // -7.9228162514264337593543950335 round = -7
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x801c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {8, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_min_number) {
  // 0.0000000000000000000000000001 round = 0
  s21_decimal x = {.bits = {1, 0, 0, 0x1c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_whith_min_number_minus) {
  // -0.0000000000000000000000000001 round = -0
  s21_decimal x = {.bits = {1, 0, 0, 0x801c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_zero_whith_scale) {
  // 0.0000 round = 0
  s21_decimal x = {.bits = {0, 0, 0, 0x40000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_zero_whith_scale_minus) {
  // -0.0000 round = -0
  s21_decimal x = {.bits = {0, 0, 0, 0x80040000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0x80000000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_545001) {
  // 54.5000000000000000001 round = 55
  s21_decimal x = {.bits = {0x5be40001, 0x8b64f477, 0x1d, 0x130000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {55, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(test_round_545000) {
  // 54.5000000000000000000 round = 54
  s21_decimal x = {.bits = {0x5be40000, 0x8b64f477, 0x1d, 0x130000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {54, 0, 0, 0}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_round(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

TCase *tcase_s21_round(void) {
  TCase *tc;

  tc = tcase_create("Tests for s21_round");

  tcase_add_test(tc, test_round_no_scale);
  tcase_add_test(tc, test_round_no_scale_minus);

  tcase_add_test(tc, test_round_whith_one_scale);
  tcase_add_test(tc, test_round_whith_one_scale_minus);

  tcase_add_test(tc, test_round_whith_two_scale);
  tcase_add_test(tc, test_round_whith_two_scale_minus);

  tcase_add_test(tc, test_round_whith_three_scale);
  tcase_add_test(tc, test_round_whith_three_scale_minus);

  tcase_add_test(tc, test_round_whith_545_scale);
  tcase_add_test(tc, test_round_whith_545_scale_minus);

  tcase_add_test(tc, test_round_whith_max_scale);
  tcase_add_test(tc, test_round_whith_max_scale_minus);

  tcase_add_test(tc, test_round_whith_min_number);
  tcase_add_test(tc, test_round_whith_min_number_minus);

  tcase_add_test(tc, test_round_zero_whith_scale);
  tcase_add_test(tc, test_round_zero_whith_scale_minus);

  tcase_add_test(tc, test_round_545001);
  tcase_add_test(tc, test_round_545000);

  return tc;
}
