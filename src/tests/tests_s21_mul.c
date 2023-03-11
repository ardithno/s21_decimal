#include <check.h>

#include "../s21_decimal.h"

START_TEST(small_positive_mull_one_return_itself) {
  // 1 * 3 = 3
  s21_decimal x = {.bits = {1, 0, 0, 0}};
  s21_decimal y = {.bits = {3, 0, 0, 0}};
  s21_decimal expect = {.bits = {3, 0, 0, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(sum_scale_when_multiply_values_with_fraction) {
  // 0.1 * 0.3 = 0.03
  s21_decimal x = {.bits = {1, 0, 0, 1}};
  s21_decimal y = {.bits = {3, 0, 0, 2}};
  s21_decimal expect = {.bits = {3, 0, 0, 3}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(return_zero_if_multiply_too_small) {
  // 0.000000000000001 * 0.000000000000007 = 0.0000000000000000000000000000
  s21_decimal x = {.bits = {1, 0, 0, 0xf0000}};
  s21_decimal y = {.bits = {7, 0, 0, 0xf0000}};
  s21_decimal expect = {.bits = {0, 0, 0, 0x1c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(do_not_cut_result_from_lower_rounded_bits) {
  // 0.000000000000009 * 0.000000000000009 = 0.0000000000000000000000000001
  s21_decimal x = {.bits = {9, 0, 0, 0xf0000}};
  s21_decimal y = {.bits = {9, 0, 0, 0xf0000}};
  s21_decimal expect = {.bits = {1, 0, 0, 0x1c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(do_not_overflow_on_multiplying_max_value) {
  // 79228162514264337593543950335 * -1 = -79228162514264337593543950335
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal y = {.bits = {1, 0, 0, 0x80000000}};
  s21_decimal expect = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(overflow_on_multiplying_max_value) {
  // 7922816251426433759354395033.5 * 11 = positive overflow!
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 1}};
  s21_decimal y = {.bits = {11, 0, 0, 0}};
  s21_decimal expect = {{0, 0, 0, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 1);  // Positive overflow
}
END_TEST

START_TEST(round_fractional_part_on_overflow) {
  // -79228162514264337593543950.335 * 101 = positive overflow!
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80030000}};
  s21_decimal y = {.bits = {101, 0, 0, 0}};
  s21_decimal expect = {{0x374bc6a8, 0xe5604189, 0x19db22d0, 0x80000000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(negative_overflow_may_happen) {
  // -79228162514264337593543950.335 * 1001 = negative overflow!
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80030000}};
  s21_decimal y = {.bits = {1001, 0, 0, 0}};
  s21_decimal expect = {{0, 0, 0, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 2);
}
END_TEST

START_TEST(negative_to_negative_return_positive) {
  // -123456778.43489348 * -9393982.83238238 = 1159750857158624.5838066699289
  s21_decimal x = {.bits = {0x1e5f6244, 0x2bdc54, 0, 0x80080000}};
  s21_decimal y = {.bits = {0xb4f99b5e, 0x35660, 0, 0x80080000}};
  s21_decimal expect = {.bits = {0x5f904c19, 0x6fc8839e, 0x25793bf7, 0xd0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_1) {
  // 1844674407.8004518913 * 1844674407.8004518913
  // =
  // 3402823670793947885.4724351485
  s21_decimal x = {.bits = {1, 1, 1, 0xa0000}};
  s21_decimal y = {.bits = {1, 1, 1, 0xa0000}};
  s21_decimal expect = {.bits = {0x6281f5fd, 0x3adde9af, 0x6df37f68, 0xa0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_2) {
  // 0.0000000001 * 0.0000000001 = 0.00000000000000000001
  s21_decimal x = {.bits = {1, 0, 0, 0xa0000}};
  s21_decimal y = {.bits = {1, 0, 0, 0xa0000}};
  s21_decimal expect = {.bits = {1, 0, 0, 0x140000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_3) {
  // 0.0000000001 * -0.0000000001 = 0.00000000000000000001
  s21_decimal x = {.bits = {1, 0, 0, 0xa0000}};
  s21_decimal y = {.bits = {1, 0, 0, -2146828288}};
  s21_decimal expect = {.bits = {1, 0, 0, 0x80140000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_4) {
  // 184467.44073709551617 * -0.0000000001 = -0.000018446744073709551617
  s21_decimal x = {.bits = {1, 0, 1, 917504}};
  s21_decimal y = {.bits = {1, 0, 0, -2146828288}};
  s21_decimal expect = {.bits = {1, 0, 1, 0x80180000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_mul(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

TCase *tcase_s21_mul(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_mul`");

  tcase_add_test(tc, small_positive_mull_one_return_itself);
  tcase_add_test(tc, sum_scale_when_multiply_values_with_fraction);
  tcase_add_test(tc, return_zero_if_multiply_too_small);
  tcase_add_test(tc, do_not_cut_result_from_lower_rounded_bits);
  tcase_add_test(tc, do_not_overflow_on_multiplying_max_value);
  tcase_add_test(tc, overflow_on_multiplying_max_value);
  tcase_add_test(tc, round_fractional_part_on_overflow);
  tcase_add_test(tc, negative_overflow_may_happen);
  tcase_add_test(tc, negative_to_negative_return_positive);

  tcase_add_test(tc, possible_verter_test_1);
  tcase_add_test(tc, possible_verter_test_2);
  tcase_add_test(tc, possible_verter_test_3);
  tcase_add_test(tc, possible_verter_test_4);

  return tc;
}
