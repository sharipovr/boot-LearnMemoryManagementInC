#include "munit/munit.h"

#include "coord.h"

munit_case(RUN, test_new_coordinate1, {
  struct Coordinate c = new_coord(1, 2, 3);

  assert_int(c.x, ==, 1, "should set x");
  assert_int(c.y, ==, 2, "should set y");
  assert_int(c.z, ==, 3, "should set z");
});

munit_case(SUBMIT, test_new_coordinate2, {
  struct Coordinate c = new_coord(4, 2, 0);

  assert_int(c.x, ==, 4, "should set x");
  assert_int(c.y, ==, 2, "should set y");
  assert_int(c.z, ==, 0, "should set z");
});

int main() {
  MunitTest tests[] = {
    munit_test("/create_coordinate1", test_new_coordinate1),
    munit_test("/create_coordinate2", test_new_coordinate2),
    munit_null_test,
  };

  MunitSuite suite = munit_suite("coordinates", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}
