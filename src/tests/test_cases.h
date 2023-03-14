#ifndef SRC_TESTS_TEST_CASES_H_
#define SRC_TESTS_TEST_CASES_H_

#include <check.h>

TCase *tcase__s21_big_decimal_add();
TCase *tcase__s21_big_decimal_compare();
TCase *tcase__s21_big_decimal_shift_left();
TCase *tcase__s21_big_decimal_sub();
TCase *tcase__s21_big_decimal_to_decimal();
TCase *tcase__s21_decimal_to_big_decimal();
TCase *tcase__s21_get_scale();
TCase *tcase_s21_add();
TCase *tcase_s21_change_sign();
TCase *tcase_s21_div();
TCase *tcase_s21_from_int_to_decimal();
TCase *tcase_s21_get_sign();
TCase *tcase_s21_is_equal();
TCase *tcase_s21_is_zero();
TCase *tcase_s21_mod();
TCase *tcase_s21_mul();
TCase *tcase_s21_negate();
TCase *tcase_s21_sub();
TCase *tcase_s21_is_not_equal();
TCase *tcase_s21_is_less();
TCase *tcase_s21_is_less_or_equal();
TCase *tcase_s21_is_greater();
TCase *tcase_s21_is_greater_or_equal();
TCase *tcase_s21_from_decimal_to_float();
TCase *tcase_s21_set_power();
TCase *tcase_s21_from_decimal_to_int();

#endif /* SRC_TESTS_TEST_CASES_H_ */
