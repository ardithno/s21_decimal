#include <check.h>
#include <stdlib.h>

#include "test_cases.h"

Suite *suite_s21_decimal(void) {
  Suite *suite;

  suite = suite_create("Tests s21_decimal");

  // Internal functions
  suite_add_tcase(suite, tcase__s21_big_decimal_add());
  suite_add_tcase(suite, tcase__s21_big_decimal_compare());
  suite_add_tcase(suite, tcase__s21_big_decimal_shift_left());
  suite_add_tcase(suite, tcase__s21_big_decimal_sub());
  suite_add_tcase(suite, tcase__s21_big_decimal_to_decimal());
  suite_add_tcase(suite, tcase__s21_decimal_to_big_decimal());
  suite_add_tcase(suite, tcase__s21_get_scale());

  // User-faced functions
  suite_add_tcase(suite, tcase_s21_add());
  suite_add_tcase(suite, tcase_s21_change_sign());
  suite_add_tcase(suite, tcase_s21_div());
  suite_add_tcase(suite, tcase_s21_from_int_to_decimal());
  suite_add_tcase(suite, tcase_s21_get_sign());
  suite_add_tcase(suite, tcase_s21_is_equal());
  suite_add_tcase(suite, tcase_s21_is_zero());
  suite_add_tcase(suite, tcase_s21_mod());
  suite_add_tcase(suite, tcase_s21_mul());
  suite_add_tcase(suite, tcase_s21_negate());
  suite_add_tcase(suite, tcase_s21_sub());
  suite_add_tcase(suite, tcase_s21_is_not_equal());
  suite_add_tcase(suite, tcase_s21_is_less());
  suite_add_tcase(suite, tcase_s21_is_less_or_equal());
  suite_add_tcase(suite, tcase_s21_is_greater());
  suite_add_tcase(suite, tcase_s21_is_greater_or_equal());
  suite_add_tcase(suite, tcase_s21_from_decimal_to_float());
  suite_add_tcase(suite, tcase_s21_set_power());
  suite_add_tcase(suite, tcase_s21_truncate());

  return suite;
}

int main(void) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(suite_s21_decimal());

  // We set NOFORK mode for debug ability and testing with valgrind
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
