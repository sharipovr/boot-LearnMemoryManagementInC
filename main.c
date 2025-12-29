#include "munit.h"

#include "exercise.h"

munit_case(RUN, test_cold, {
  char *result = get_temperature_status(50);
  munit_assert_string_equal(result, "too cold", "50 should be too cold");
});

munit_case(RUN, test_hot, {
  char *result = get_temperature_status(100);
  munit_assert_string_equal(result, "too hot", "100 should be too hot");
});

munit_case(SUBMIT, test_just_right, {
  char *result = get_temperature_status(70);
  munit_assert_string_equal(result, "just right", "70 should be just right");
});

munit_case(SUBMIT, test_just_right2, {
  char *result = get_temperature_status(75);
  munit_assert_string_equal(result, "just right", "75 should be just right");
});

int main() {
  MunitTest tests[] = {
      munit_test("/test_cold", test_cold),
      munit_test("/test_hot", test_hot),
      munit_test("/test_just_right", test_just_right),
      munit_test("/test_just_right2", test_just_right2),
      munit_null_test,
  };

  MunitSuite suite = munit_suite("get_temperature_status", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}
