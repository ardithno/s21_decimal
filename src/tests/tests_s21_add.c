#include <check.h>

#include "../s21_decimal.h"

int _tests_add_check_bits(s21_decimal first, s21_decimal second) {
  int is_equal = S21_TRUE;

  for (int i = LOW; i <= SCALE; i++) {
    if (first.bits[i] != second.bits[i]) is_equal = S21_FALSE;
  }

  return is_equal;
}

START_TEST(regular_positive_add_rounding_up) {
  // 0.4444444444444444444444443354 + 100 = 100.44444444444444444444444434
  s21_decimal x = {.bits = {0x5c71c2da, 0x1b9eabb9, 0xe5c5bb8, 0x1c0000}};
  s21_decimal y = {.bits = {0x64, 0, 0, 0}};
  s21_decimal expect = {.bits = {0x3c71c712, 0x676179db, 0x207491d8, 0x1a0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(regular_positive_not_rounding) {
  // 0.4444444444444444444444443354 + 10 = 10.444444444444444444444444335
  s21_decimal x = {.bits = {0x5c71c2da, 0x1b9eabb9, 0xe5c5bb8, 0x1c0000}};
  s21_decimal y = {.bits = {0xa, 0, 0, 0}};
  s21_decimal expect = {.bits = {0xcc71c6af, 0xda81ad26, 0x21bf7123, 0x1b0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(bank_rounding_if_not_enough_bits_for_whole_result) {
  // 792.28162514264337593543950335 + 10 = 802.2816251426433759354395034
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x1a0000}};
  s21_decimal y = {.bits = {0xa, 0, 0, 0}};
  s21_decimal expect = {.bits = {0x7d99999a, 0x7661a66c, 0x19ec516c, 0x190000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(remove_unnecessary_trialing_zeros_from_result) {
  // 0.00000000000000004294967294 + 10 = 10.00000000000000004294967294
  s21_decimal x = {.bits = {0xfffffffe, 0, 0, 0x1a0000}};
  s21_decimal y = {.bits = {0xa, 0, 0, 0}};
  s21_decimal expect = {.bits = {0xe7fffffe, 0x9fd0803d, 0x33b2e3c, 0x1a0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(overflow_happen) {
  // 79228162514264337593543950335 + 0.50 = overflow !!!
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal y = {.bits = {0x32, 0, 0, 0x20000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  ck_assert_int_eq(is_error, 1);
}
END_TEST

START_TEST(overflow_not_happen) {
  // 79228162514264337593543950335 + 0.49 = 79228162514264337593543950335
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal y = {.bits = {0x31, 0, 0, 0x20000}};
  s21_decimal expect = x;
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(regular_negative_add_rounding_up) {
  // -0.4444444444444444444444443354 + -100 = -100.44444444444444444444444434
  s21_decimal x = {.bits = {0x5c71c2da, 0x1b9eabb9, 0xe5c5bb8, 0x801c0000}};
  s21_decimal y = {.bits = {0x64, 0, 0, 0x80000000}};
  s21_decimal expect = {{0x3c71c712, 0x676179db, 0x207491d8, 0x801a0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(regular_negative_not_rounding) {
  // -0.4444444444444444444444443354 + -10 = -10.444444444444444444444444335
  s21_decimal x = {.bits = {0x5c71c2da, 0x1b9eabb9, 0xe5c5bb8, 0x801c0000}};
  s21_decimal y = {.bits = {0xa, 0, 0, 0x80000000}};
  s21_decimal expect = {{0xcc71c6af, 0xda81ad26, 0x21bf7123, 0x801b0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(save_trailing_zeros_if_possible) {
  // 0.49999 + 0.00001 = 0.50000
  s21_decimal x = {.bits = {0x7a11f, 0, 0, 0x60000}};
  s21_decimal y = {.bits = {0x1, 0, 0, 0x60000}};
  s21_decimal expect = {{0x7a120, 0, 0, 0x60000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(negative_overflow_happen) {
  // -79228162514264337593543950335 + -0.50 = overflow !!!
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal y = {.bits = {0x32, 0, 0, 0x80020000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  ck_assert_int_eq(is_error, 2);
}
END_TEST

START_TEST(negative_overflow_not_happen) {
  // -79228162514264337593543950335 + -0.49 = 79228162514264337593543950335
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal y = {.bits = {0x31, 0, 0, 0x80020000}};
  s21_decimal expect = x;
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(adding_negative_and_positive_result_positive_null) {
  // -0.000001 + 0.000001 = 0.000000
  s21_decimal x = {.bits = {0x1, 0, 0, 0x80060000}};
  s21_decimal y = {.bits = {0x1, 0, 0, 0x60000}};
  s21_decimal expect = {.bits = {0, 0, 0, 0x60000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(adding_positive_and_negative_result_positive_null) {
  // 0.000001 + -0.000001 = 0.000000
  s21_decimal x = {.bits = {0x1, 0, 0, 0x60000}};
  s21_decimal y = {.bits = {0x1, 0, 0, 0x80060000}};
  s21_decimal expect = {.bits = {0, 0, 0, 0x60000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_1) {
  s21_decimal x = {.bits = {1, 1, 1, 65536}};
  s21_decimal y = {.bits = {1, 1, 1, 65536}};
  s21_decimal expect = {.bits = {2, 2, 2, 65536}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}

START_TEST(possible_verter_test_2) {
  s21_decimal x = {.bits = {1, 1, 1, 65536}};
  s21_decimal y = {.bits = {1, 1, 1, 655360}};
  s21_decimal expect = {.bits = {0x3b9aca01, 0x3b9aca01, 0x3b9aca01, 0xa0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}

START_TEST(possible_verter_test_3) {
  s21_decimal x = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal y = {.bits = {1, 15, 1, 655360}};
  s21_decimal expect = {{0x9682efff, 0x3b9ac9f6, 0x3b9ac9ff, 0x800a0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}

START_TEST(possible_verter_test_4) {
  s21_decimal x = {.bits = {1, 1, 1, 655360}};
  s21_decimal y = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal expect = {{0x3b9ac9ff, 0x3b9ac9ff, 0x3b9ac9ff, 0x800a0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_add(x, y, &result);

  is_equal = _tests_add_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}

TCase *tcase_s21_add(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_add`");

  tcase_add_test(tc, regular_positive_add_rounding_up);
  tcase_add_test(tc, regular_positive_not_rounding);
  tcase_add_test(tc, bank_rounding_if_not_enough_bits_for_whole_result);
  tcase_add_test(tc, remove_unnecessary_trialing_zeros_from_result);
  tcase_add_test(tc, save_trailing_zeros_if_possible);
  tcase_add_test(tc, overflow_happen);
  tcase_add_test(tc, overflow_not_happen);
  tcase_add_test(tc, regular_negative_add_rounding_up);
  tcase_add_test(tc, regular_negative_not_rounding);
  tcase_add_test(tc, negative_overflow_happen);
  tcase_add_test(tc, negative_overflow_not_happen);
  tcase_add_test(tc, adding_negative_and_positive_result_positive_null);
  tcase_add_test(tc, adding_positive_and_negative_result_positive_null);

  tcase_add_test(tc, possible_verter_test_1);
  tcase_add_test(tc, possible_verter_test_2);
  tcase_add_test(tc, possible_verter_test_3);
  tcase_add_test(tc, possible_verter_test_4);

  return tc;
}
