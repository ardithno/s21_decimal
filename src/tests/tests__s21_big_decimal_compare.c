#include <check.h>

#include "../s21_decimal.h"

int _big_decimal_compare;

void setup_invalid_comparing_result(void) { _big_decimal_compare = 999; }

START_TEST(compare_two_zeros_return_zero) {
  _s21_big_decimal first = S21_DECIMAL_NULL;
  _s21_big_decimal second = S21_DECIMAL_NULL;

  _big_decimal_compare = _s21_big_decimal_compare(&first, &second);

  ck_assert_int_eq(_big_decimal_compare, 0);
}
END_TEST

START_TEST(zeros_with_different_signs_is_equal) {
  _s21_big_decimal positive = S21_DECIMAL_NULL;
  _s21_big_decimal negative = {.bits = {0, 0, 0, 0, 0, 0, 0, 0x80000000}};

  _big_decimal_compare = _s21_big_decimal_compare(&positive, &negative);

  ck_assert_int_eq(_big_decimal_compare, 0);
}
END_TEST

START_TEST(return_minus_one_if_first_bigger) {
  _s21_big_decimal first = {.bits = {0, 1, 0, 0, 0, 0, 0, 0}};
  _s21_big_decimal second = {.bits = {1, 0, 0, 0, 0, 0, 0, 0}};

  _big_decimal_compare = _s21_big_decimal_compare(&first, &second);

  ck_assert_int_eq(_big_decimal_compare, -1);
}
END_TEST

START_TEST(return_minus_one_if_first_bigger_for_negative) {
  _s21_big_decimal first = {.bits = {1, 0, 0, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal second = {.bits = {0, 1, 0, 0, 0, 0, 0, 0x80000000}};

  _big_decimal_compare = _s21_big_decimal_compare(&first, &second);

  ck_assert_int_eq(_big_decimal_compare, -1);
}
END_TEST

START_TEST(return_one_if_second_bigger) {
  _s21_big_decimal first = {.bits = {1, 0, 0, 0, 0, 0, 0, 0}};
  _s21_big_decimal second = {.bits = {0, 1, 0, 0, 0, 0, 0, 0}};

  _big_decimal_compare = _s21_big_decimal_compare(&first, &second);

  ck_assert_int_eq(_big_decimal_compare, 1);
}
END_TEST

START_TEST(return_one_if_second_bigger_for_negative) {
  _s21_big_decimal first = {.bits = {0, 1, 0, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal second = {.bits = {1, 0, 0, 0, 0, 0, 0, 0x80000000}};

  _big_decimal_compare = _s21_big_decimal_compare(&first, &second);

  ck_assert_int_eq(_big_decimal_compare, 1);
}
END_TEST

START_TEST(two_same_bits_different_signs_first_bigger) {
  _s21_big_decimal positive = {.bits = {99, 99, 0, 0, 0, 1, 0, 0}};
  _s21_big_decimal negative = {.bits = {99, 99, 0, 0, 0, 1, 0, 0x80000000}};

  _big_decimal_compare = _s21_big_decimal_compare(&positive, &negative);

  ck_assert_int_eq(_big_decimal_compare, -1);
}
END_TEST

START_TEST(two_same_bits_different_signs_second_bigger) {
  _s21_big_decimal positive = {.bits = {99, 99, 0, 0, 0, 1, 0, 0}};
  _s21_big_decimal negative = {.bits = {99, 99, 0, 0, 0, 1, 0, 0x80000000}};

  _big_decimal_compare = _s21_big_decimal_compare(&negative, &positive);

  ck_assert_int_eq(_big_decimal_compare, 1);
}
END_TEST

START_TEST(two_negative_is_equal) {
  _s21_big_decimal first = {.bits = {99, 99, 0, 0, 0, 1, 0, 0x80000000}};
  _s21_big_decimal second = {.bits = {99, 99, 0, 0, 0, 1, 0, 0x80000000}};

  _big_decimal_compare = _s21_big_decimal_compare(&first, &second);

  ck_assert_int_eq(_big_decimal_compare, 0);
}
END_TEST

START_TEST(two_positive_is_equal) {
  _s21_big_decimal first = {.bits = {99, 99, 0, 0, 43, 1, 0, 0}};
  _s21_big_decimal second = {.bits = {99, 99, 0, 0, 43, 1, 0, 0}};

  _big_decimal_compare = _s21_big_decimal_compare(&first, &second);

  ck_assert_int_eq(_big_decimal_compare, 0);
}
END_TEST

TCase* tcase__s21_big_decimal_compare(void) {
  TCase* tc;

  tc = tcase_create("Tests for comparing big decimals");

  tcase_add_checked_fixture(tc, setup_invalid_comparing_result, NULL);

  tcase_add_test(tc, compare_two_zeros_return_zero);
  tcase_add_test(tc, zeros_with_different_signs_is_equal);
  tcase_add_test(tc, return_minus_one_if_first_bigger);
  tcase_add_test(tc, return_minus_one_if_first_bigger_for_negative);
  tcase_add_test(tc, return_one_if_second_bigger);
  tcase_add_test(tc, return_one_if_second_bigger_for_negative);
  tcase_add_test(tc, two_same_bits_different_signs_first_bigger);
  tcase_add_test(tc, two_same_bits_different_signs_second_bigger);
  tcase_add_test(tc, two_negative_is_equal);
  tcase_add_test(tc, two_positive_is_equal);

  return tc;
}
