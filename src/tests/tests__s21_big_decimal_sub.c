#include <check.h>

#include "../s21_decimal.h"

START_TEST(zero_sub_zero) {
  _s21_big_decimal null = S21_DECIMAL_NULL;
  _s21_big_decimal second_null = S21_DECIMAL_NULL;
  _s21_big_decimal result = {.bits = {2, 2, 2, 2, 2, 2, 2}};  // any not null

  result = _s21_big_decimal_sub(&null, &second_null);

  ck_assert_int_eq(_s21_big_decimal_compare(&result, &null), 0);
}
END_TEST

START_TEST(negative_zero_sub_zero) {
  _s21_big_decimal negative_null = {.bits = {0, 0, 0, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal null = S21_DECIMAL_NULL;

  _s21_big_decimal result = _s21_big_decimal_sub(&negative_null, &null);

  ck_assert_int_eq(_s21_big_decimal_compare(&result, &negative_null), 0);
  ck_assert_int_eq(_s21_big_decimal_get_sign(&result), 1);  // negative zero
}
END_TEST

START_TEST(zero_sub_negative_zero) {
  _s21_big_decimal null = S21_DECIMAL_NULL;
  _s21_big_decimal negative_null = {.bits = {0, 0, 0, 0, 0, 0, 0, 0x80000000}};

  _s21_big_decimal result = _s21_big_decimal_sub(&null, &negative_null);

  ck_assert_int_eq(_s21_big_decimal_compare(&result, &null), 0);
  ck_assert_int_eq(_s21_big_decimal_get_sign(&result), 0);  // positive zero
}
END_TEST

START_TEST(two_positive_expect_positive) {
  _s21_big_decimal first = {.bits = {0, 0, 0, 1, 0, 0, 0, 0}};
  _s21_big_decimal second = {{0xffffffff, 0xffffffff, 0, 0, 0, 0, 0, 0}};
  _s21_big_decimal expected = {.bits = {1, 0, 0xffffffff, 0, 0, 0, 0, 0}};

  _s21_big_decimal result = _s21_big_decimal_sub(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(two_positive_expect_negative) {
  _s21_big_decimal first = {.bits = {0xffffffff, 0xffffffff, 0, 0, 0, 0, 0, 0}};
  _s21_big_decimal second = {.bits = {0, 0, 0, 1, 0, 0, 0, 0}};
  _s21_big_decimal expected = {{1, 0, 0xffffffff, 0, 0, 0, 0, 0x80000000}};

  _s21_big_decimal result = _s21_big_decimal_sub(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(two_negative_expect_negative) {
  _s21_big_decimal first = {.bits = {0, 0, 1, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal second = {{0xffffffff, 0, 0, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal expected = {{1, 0xffffffff, 0, 0, 0, 0, 0, 0x80000000}};

  _s21_big_decimal result = _s21_big_decimal_sub(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(two_negative_expect_positive) {
  _s21_big_decimal first = {.bits = {0xffffffff, 0, 0, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal second = {.bits = {0, 0, 1, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal expected = {.bits = {1, 0xffffffff, 0, 0, 0, 0, 0, 0}};

  _s21_big_decimal result = _s21_big_decimal_sub(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(from_positive_sub_negative) {
  _s21_big_decimal first = {.bits = {2, 0, 0, 0, 0, 0, 0, 0}};
  _s21_big_decimal second = {.bits = {1, 0, 1, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal expected = {.bits = {3, 0, 1, 0, 0, 0, 0, 0}};

  _s21_big_decimal result = _s21_big_decimal_sub(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

START_TEST(from_negative_sub_positive) {
  _s21_big_decimal first = {.bits = {2, 0, 0, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal second = {.bits = {1, 0, 1, 0, 0, 0, 0, 0}};
  _s21_big_decimal expected = {.bits = {3, 0, 1, 0, 0, 0, 0, 0x80000000}};

  _s21_big_decimal result = _s21_big_decimal_sub(&first, &second);

  ck_assert_int_eq(_s21_big_decimal_compare(&expected, &result), 0);
}
END_TEST

TCase *tcase__s21_big_decimal_sub(void) {
  TCase *tc;

  tc = tcase_create("Tests for `_s21_big_decimal_sub`");

  tcase_add_test(tc, zero_sub_zero);
  tcase_add_test(tc, negative_zero_sub_zero);
  tcase_add_test(tc, zero_sub_negative_zero);
  tcase_add_test(tc, two_positive_expect_positive);
  tcase_add_test(tc, two_positive_expect_negative);
  tcase_add_test(tc, two_negative_expect_negative);
  tcase_add_test(tc, two_negative_expect_positive);
  tcase_add_test(tc, from_positive_sub_negative);
  tcase_add_test(tc, from_negative_sub_positive);

  return tc;
}
