#include "munit.h"

#include "exercise.h"

munit_case(RUN, test_premium_user, {
  int result = can_access_registry(1, 0, 0);
  munit_assert_int(result, ==, 1, "Premium users should have access");
});

munit_case(RUN, test_high_rep_with_2fa, {
  int result = can_access_registry(0, 100, 1);
  munit_assert_int(result, ==, 1, "Users with 100+ reputation and 2FA should have access");
});

munit_case(SUBMIT, test_high_rep_no_2fa, {
  int result = can_access_registry(0, 150, 0);
  munit_assert_int(result, ==, 0, "High reputation without 2FA should not have access");
});

munit_case(SUBMIT, test_low_rep_with_2fa, {
  int result = can_access_registry(0, 50, 1);
  munit_assert_int(result, ==, 0, "Low reputation with 2FA should not have access");
});

munit_case(SUBMIT, test_premium_overrides, {
  int result = can_access_registry(1, 10, 0);
  munit_assert_int(result, ==, 1, "Premium status should grant access regardless of other factors");
});

munit_case(SUBMIT, test_no_access, {
  int result = can_access_registry(0, 50, 0);
  munit_assert_int(result, ==, 0, "Should not have access without meeting any criteria");
});

int main() {
  MunitTest tests[] = {
      munit_test("/test_premium_user", test_premium_user),
      munit_test("/test_high_rep_with_2fa", test_high_rep_with_2fa),
      munit_test("/test_high_rep_no_2fa", test_high_rep_no_2fa),
      munit_test("/test_low_rep_with_2fa", test_low_rep_with_2fa),
      munit_test("/test_premium_overrides", test_premium_overrides),
      munit_test("/test_no_access", test_no_access),
      munit_null_test,
  };

  MunitSuite suite = munit_suite("can_access_registry", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}
