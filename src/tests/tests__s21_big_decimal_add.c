#include <check.h>

#include "../s21_decimal.h"

START_TEST(zero_add_zero) {
  _s21_big_decimal null = S21_DECIMAL_NULL;
  _s21_big_decimal second_null = S21_DECIMAL_NULL;

  _s21_big_decimal result = _s21_big_decimal_add(&null, &second_null);

  ck_assert_int_eq(_s21_big_decimal_compare(&result, &null), 0);
}
END_TEST

START_TEST(negative_add_same_positive_return_zero) {
  _s21_big_decimal negative = {.bits = {0, 0, 1, 1, 0, 0, 0x80000000}};
  _s21_big_decimal positive = {.bits = {0, 0, 1, 1, 0, 0, 0}};
  _s21_big_decimal expected = S21_DECIMAL_NULL;

  _s21_big_decimal result = _s21_big_decimal_add(&positive, &negative);

  ck_assert_int_eq(_s21_big_decimal_compare_bits(&result, &expected), 0);
  ck_assert_int_eq(_s21_big_decimal_get_sign(&result), 0);
}
END_TEST

START_TEST(positive_add_same_negative_return_zero) {
  _s21_big_decimal negative = {.bits = {0, 0, 1, 1, 0, 0, 0x80000000}};
  _s21_big_decimal positive = {.bits = {0, 0, 1, 1, 0, 0, 0}};
  _s21_big_decimal expected = S21_DECIMAL_NULL;

  _s21_big_decimal result = _s21_big_decimal_add(&negative, &positive);

  ck_assert_int_eq(_s21_big_decimal_compare_bits(&result, &expected), 0);
  ck_assert_int_eq(_s21_big_decimal_get_sign(&result), 0);
}
END_TEST

START_TEST(two_positive_expect_positive) {
  _s21_big_decimal first = {.bits = {0, 0, 0, 1, 0, 0, 0}};
  _s21_big_decimal second = {.bits = {0xffffffff, 0, 0, 0, 0, 0, 0}};
  _s21_big_decimal expected = {.bits = {0xffffffff, 0, 0, 1, 0, 0, 0}};

  _s21_big_decimal result = _s21_big_decimal_add(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(positive_add_negative_still_positive) {
  _s21_big_decimal first = {.bits = {0, 3, 0, 0, 0, 0, 0}};
  _s21_big_decimal second = {.bits = {0, 1, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal expected = {.bits = {0, 2, 0, 0, 0, 0, 0}};

  _s21_big_decimal result = _s21_big_decimal_add(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(positive_add_negative_expect_negative) {
  _s21_big_decimal first = {.bits = {0, 0, 3, 0, 0, 0, 0}};
  _s21_big_decimal second = {.bits = {0, 0, 4, 0, 0, 0, 0x80000000}};
  _s21_big_decimal expected = {.bits = {0, 0, 1, 0, 0, 0, 0x80000000}};

  _s21_big_decimal result = _s21_big_decimal_add(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(two_negative_expect_negative) {
  _s21_big_decimal first = {.bits = {0xffffffff, 0, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal second = {.bits = {0, 0, 1, 0, 0, 0, 0x80000000}};
  _s21_big_decimal expected = {.bits = {0xffffffff, 0, 1, 0, 0, 0, 0x80000000}};

  _s21_big_decimal result = _s21_big_decimal_add(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(negative_add_positive_still_negative) {
  _s21_big_decimal first = {.bits = {0, 1, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal second = {.bits = {0xffffffff, 0, 0, 0, 0, 0, 0}};
  _s21_big_decimal expected = {.bits = {1, 0, 0, 0, 0, 0, 0x80000000}};

  _s21_big_decimal result = _s21_big_decimal_add(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(negative_add_positive_return_positive) {
  _s21_big_decimal first = {.bits = {0, 1, 0, 0, 0, 1, 0x80000000}};
  _s21_big_decimal second = {.bits = {0xffffffff, 1, 0, 0, 0, 1, 0}};
  _s21_big_decimal expected = {.bits = {0xffffffff, 0, 0, 0, 0, 0, 0}};

  _s21_big_decimal result = _s21_big_decimal_add(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(overflow_from_lower_bits_not_break_result) {
  _s21_big_decimal first = {.bits = {0xb1380000, 0xe43e9298, 0xffffffff,
                                     0xa763ffff, 0xde0b6b3, 0, 0xa0000}};
  _s21_big_decimal second = {.bits = {0xa7640000, 0xde0b6b3, 0x0000000,
                                      0x00000000, 0x00000000, 0, 0xa0000}};
  _s21_big_decimal expected = {.bits = {0x589c0000, 0xf21f494c, 0xffffffff,
                                        0xa763ffff, 0xde0b6b3, 0, 0xa0000}};

  _s21_big_decimal result = _s21_big_decimal_add(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

TCase *tcase__s21_big_decimal_add(void) {
  TCase *tc;

  tc = tcase_create("Tests for `_s21_big_decimal_add`");

  tcase_add_test(tc, zero_add_zero);
  tcase_add_test(tc, negative_add_same_positive_return_zero);
  tcase_add_test(tc, positive_add_same_negative_return_zero);
  tcase_add_test(tc, two_positive_expect_positive);
  tcase_add_test(tc, positive_add_negative_still_positive);
  tcase_add_test(tc, positive_add_negative_expect_negative);
  tcase_add_test(tc, two_negative_expect_negative);
  tcase_add_test(tc, negative_add_positive_still_negative);
  tcase_add_test(tc, negative_add_positive_return_positive);
  tcase_add_test(tc, overflow_from_lower_bits_not_break_result);

  return tc;
}
