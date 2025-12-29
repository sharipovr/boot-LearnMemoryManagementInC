/*
 * Compatibility shim for boot.dev-style helper macros used by main.c.
 *
 * This repo vendors upstream µnit under ./munit/, but main.c uses helper
 * macros (munit_case/munit_test/munit_suite/munit_null_test) which are not
 * part of upstream µnit. Rather than editing main.c, compile with:
 *
 *   clang -I. -Imunit -include munit_bootdev_compat.h \
 *     main.c exercise.c munit/munit.c -o main.out
 *
 * (The -include ensures this file is processed before main.c.)
 */
#ifndef MUNIT_BOOTDEV_COMPAT_H
#define MUNIT_BOOTDEV_COMPAT_H

#include <string.h>

/* Include upstream µnit once, then prevent main.c from re-including it. */
#include "munit/munit.h"

/* ---- boot.dev helper macros ---- */

/* main.c uses munit_case(RUN|SUBMIT, test_name, { ... }); */
#ifndef munit_case
#define munit_case(_category, _name, _body)                                       \
  static MunitResult _name(const MunitParameter params[], void* user_data) {      \
    (void) params;                                                                \
    (void) user_data;                                                             \
    _body                                                                         \
    return MUNIT_OK;                                                              \
  }
#endif

/* main.c uses munit_test("/path", test_func) inside a MunitTest[] array. */
#ifndef munit_test
#define munit_test(_path, _func)                                                  \
  { (char*) (_path), (_func), NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
#endif

/* main.c uses munit_null_test as a terminator. */
#ifndef munit_null_test
#define munit_null_test { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
#endif

/* main.c expects a helper to build a suite from a name + test array. */
#ifndef munit_suite
#define munit_suite(_name_ignored, _tests)                                        \
  ((MunitSuite) { (char*) "", (_tests), NULL, 1, MUNIT_SUITE_OPTION_NONE })
#endif

/*
 * main.c calls munit_assert_string_equal(result, expected, "message").
 * Upstream µnit only takes 2 arguments. We override it to accept a message.
 */
#ifdef munit_assert_string_equal
#undef munit_assert_string_equal
#endif
#define munit_assert_string_equal(_a, _b, _msg)                                   \
  do {                                                                            \
    const char* munit_tmp_a_ = (const char*) (_a);                                \
    const char* munit_tmp_b_ = (const char*) (_b);                                \
    if (MUNIT_UNLIKELY(strcmp(munit_tmp_a_, munit_tmp_b_) != 0)) {                \
      munit_errorf("%s (%s != %s)", (_msg), munit_tmp_a_, munit_tmp_b_);          \
    }                                                                             \
  } while (0)

/*
 * main.c calls munit_assert_double_equal(result, expected, "message").
 * Upstream µnit expects the 3rd argument to be an INTEGER precision.
 * We override it with a message-based variant using a fixed tolerance.
 */
#ifdef munit_assert_double_equal
#undef munit_assert_double_equal
#endif
#define munit_assert_double_equal(_a, _b, _msg)                                   \
  do {                                                                            \
    const double munit_tmp_a_ = (double) (_a);                                    \
    const double munit_tmp_b_ = (double) (_b);                                    \
    const double munit_tmp_diff_ =                                                 \
      (munit_tmp_a_ < munit_tmp_b_) ? (munit_tmp_b_ - munit_tmp_a_)               \
                                   : (munit_tmp_a_ - munit_tmp_b_);              \
    /* Default tolerance: 1e-6 */                                                 \
    if (MUNIT_UNLIKELY(munit_tmp_diff_ > 1e-6)) {                                 \
      munit_errorf("%s (%.17g != %.17g)", (_msg), munit_tmp_a_, munit_tmp_b_);    \
    }                                                                             \
    MUNIT_PUSH_DISABLE_MSVC_C4127_                                                \
  } while (0)                                                                     \
  MUNIT_POP_DISABLE_MSVC_C4127_

#endif /* MUNIT_BOOTDEV_COMPAT_H */


