#include <check.h>

#include "../s21_decimal.h"

int git_uint_bits_as_int(uint32_t x) {
  union convert {
    int int_value;
    uint32_t uint_value;
  } convert = {.uint_value = x};

  return convert.int_value;
}

START_TEST(regular_positive_same_scale) {
  // 1 / 3 = 0.3333333333333333333333333333
  s21_decimal x = {.bits = {1, 0, 0, 0}};
  s21_decimal y = {.bits = {3, 0, 0, 0}};
  s21_decimal expect = {.bits = {0x5555555, 0x14b700cb, 0xac544ca, 0x1c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_div(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(regular_positive_implicitly_different_scale) {
  // 10 / 3 = 3.333333333333333333333333333
  s21_decimal x = {.bits = {10, 0, 0, 0}};
  s21_decimal y = {.bits = {3, 0, 0, 0}};
  s21_decimal expect = {.bits = {0x35555555, 0xcf2607ee, 0x6bb4afe4, 0x1c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_div(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(regular_positive_division_itself) {
  // 239329.238239329992 / 239329.238239329992 = 1
  s21_decimal x = {.bits = {0x959ebec8, 0x35244ac, 0, 0xc0000}};
  s21_decimal y = {.bits = {0x959ebec8, 0x35244ac, 0, 0xc0000}};
  s21_decimal expect = {.bits = {1, 0, 0, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_div(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(regular_positive_division_itself_different_scale) {
  // 239329.238239329992000 / 239329.238239329992 = 1
  s21_decimal x = {.bits = {0x74193d40, 0xf95c4228, 0xc, 0xf0000}};
  s21_decimal y = {.bits = {0x959ebec8, 0x35244ac, 0, 0xc0000}};
  s21_decimal expect = {.bits = {1, 0, 0, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_div(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(regular_positive_division_on_smaller_decrease_scale) {
  // 0.1 / 0.0003 = 333.33333333333333333333333333 (26 fraction digits)
  s21_decimal x = {.bits = {1, 0, 0, 0x10000}};
  s21_decimal y = {.bits = {0x3, 0, 0, 0x40000}};
  s21_decimal expect = {.bits = {0x35555555, 0xcf2607ee, 0x6bb4afe4, 0x1a0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_div(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_1) {
  // 1844674407.8004518913 / 1844674407.8004518913 = 1
  s21_decimal x = {.bits = {1, 1, 1, 655360}};
  s21_decimal y = {.bits = {1, 1, 1, 655360}};
  s21_decimal expect = {.bits = {1, 0, 0, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_div(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_2) {
  // 1844674407.8004518913 / 18446.744078004518913 = 100000
  s21_decimal x = {.bits = {1, 1, 1, 655360}};
  s21_decimal y = {.bits = {1, 1, 1, 983040}};
  s21_decimal expect = {.bits = {0x186a0, 0, 0, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_div(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_3) {
  // 1844674407.8004518913 / -18446.744116659224577
  // = -99999.99979045242119940831048
  s21_decimal x = {.bits = {1, 1, 1, 655360}};
  s21_decimal y = {.bits = {1, 10, 1, -2146500608}};
  s21_decimal expect = {{0x3cc17748, 0x1b56c11c, 0x204fce5d, 0x80170000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_div(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_4) {
  // 18446.744078004518913 / -18446.744078004518913 = -1
  s21_decimal x = {.bits = {1, 1, 1, 983040}};
  s21_decimal y = {.bits = {1, 1, 1, -2146500608}};
  s21_decimal expect = {{1, 0, 0, 0x80000000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_div(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expect);
  ck_assert_int_eq(is_equal, 0);  // Zero means equal
  ck_assert_int_eq(is_error, 0);
}
END_TEST

TCase *tcase_s21_div(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_div`");

  tcase_add_test(tc, regular_positive_same_scale);
  tcase_add_test(tc, regular_positive_implicitly_different_scale);
  tcase_add_test(tc, regular_positive_division_itself);
  tcase_add_test(tc, regular_positive_division_itself_different_scale);
  tcase_add_test(tc, regular_positive_division_on_smaller_decrease_scale);

  tcase_add_test(tc, possible_verter_test_1);
  tcase_add_test(tc, possible_verter_test_2);
  tcase_add_test(tc, possible_verter_test_3);
  tcase_add_test(tc, possible_verter_test_4);

  return tc;
}
