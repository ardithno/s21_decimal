#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_truncate_whith_one_scale) {
  // 5.3 truncate = 5
  s21_decimal x = {.bits = {53, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {5, 0, 0, 0xd0000}};
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
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0b00000000000111000000000000000000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {7, 0, 0, 0xd0000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_truncate(x, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST
/*
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

START_TEST(positive_on_positive_that_should_do_overflow) {
  // 70000000000000000000000000000 % 0.001 = 0.000
  s21_decimal x = {.bits = {0x70000000, 0xb30310a7, 0xe22ea493, 0}};
  s21_decimal y = {.bits = {1, 0, 0, 0x30000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0x30000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 1);  // Means positive overflow
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(positive_on_negative_that_should_do_overflow) {
  // 79228162514264337593543950335 % -0.4 = 0.000
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal y = {.bits = {0x4, 0, 0, 0x80010000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {2, 0, 0, 0x10000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 2);  // Means negative overflow
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(negative_on_positive_that_should_do_overflow) {
  // -79228162514264337593543950335 % 0.9 = 0.000
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal y = {.bits = {0x9, 0, 0, 0x10000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0x10000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 2);  // Means negative overflow
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(negative_on_negative_that_should_do_overflow) {
  // -79228162514264337593543950335 % -0.78 = 0.00
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal y = {.bits = {0x4e, 0, 0, 0x80020000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0x20000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 1);  // Means positive overflow
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(division_on_plain_zero) {
  // 32823.03 % 0 = ! division by zero exception
  s21_decimal x = {.bits = {0x32157f, 0, 0, 0x20000}};
  s21_decimal y = S21_DECIMAL_NULL;
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = S21_DECIMAL_NULL;
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 3);  // Means null division
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(division_on_negative_zero) {
  // 0.03 % -0.0000 = ! division by zero exception
  s21_decimal x = {.bits = {0x3, 0, 0, 0x20000}};
  s21_decimal y = {.bits = {0, 0, 0, 0x80040000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = S21_DECIMAL_NULL;
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 3);  // Means null division
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(possible_verter_test_1) {
  // 1844674407800451891.3 % -1844674407800451891.3 = 0
  s21_decimal x = {.bits = {1, 1, 1, 0x10000}};
  s21_decimal y = {.bits = {1, 1, 1, 0x80010000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0x10000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(possible_verter_test_2) {
  // 1844674407800451891.3 % -1844674407.8004518913 = 0.0000000000
  s21_decimal x = {.bits = {1, 1, 1, 0x80010000}};
  s21_decimal y = {.bits = {1, 1, 1, 0x800a0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0, 0, 0, 0x800a0000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(possible_verter_test_3) {
  // 5534023222971858944.1 % -1844674408.2299486211 = 126687489.0299486211
  s21_decimal x = {.bits = {1, 2, 3, 0x80010000}};
  s21_decimal y = {.bits = {3, 2, 1, 0x800a0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0x2329b003, 0x1194d800, 0, 0xa0000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST

START_TEST(possible_verter_test_4) {
  // 5534023222.9718589441 % -1844674408.2299486211 = 1844674406.5119617019
  s21_decimal x = {.bits = {1, 2, 3, 0xa0000}};
  s21_decimal y = {.bits = {3, 2, 1, 0x800a0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  s21_decimal expected = {.bits = {0xfffffffb, 0xfffffffd, 0, 0xa0000}};
  int is_error = -999;
  int is_equal = -999;

  is_error = s21_mod(x, y, &result);

  is_equal = _s21_decimal_compare_bits(&result, &expected);
  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(is_equal, 0);  // bits the same
}
END_TEST
*/

TCase *tcase_s21_truncate(void) {
  TCase *tc;

  tc = tcase_create("Tests for s21_truncate");

  tcase_add_test(tc, test_truncate_whith_one_scale);
  tcase_add_test(tc, test_truncate_whith_max_scale);
  /*
  tcase_add_test(tc, negative_modulo_return_negative);
  tcase_add_test(tc, regular_case_when_there_is_int_part_in_division);
  tcase_add_test(tc, regular_case_overflow_not_happen_with_big_values);
  tcase_add_test(tc, negative_on_positive_return_negative);
  tcase_add_test(tc, positive_on_negative_return_positive);
  tcase_add_test(tc, positive_on_positive_that_should_do_overflow);
  tcase_add_test(tc, positive_on_negative_that_should_do_overflow);
  tcase_add_test(tc, negative_on_positive_that_should_do_overflow);
  tcase_add_test(tc, negative_on_negative_that_should_do_overflow);
  tcase_add_test(tc, division_on_plain_zero);
  tcase_add_test(tc, division_on_negative_zero);

  tcase_add_test(tc, possible_verter_test_1);
  tcase_add_test(tc, possible_verter_test_2);
  tcase_add_test(tc, possible_verter_test_3);
  tcase_add_test(tc, possible_verter_test_4);*/

  return tc;
}
