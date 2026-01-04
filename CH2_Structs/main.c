#include "munit_bootdev_compat.h"

#include "coord.h"

munit_case(RUN, test_new_coordinate, {
  struct Coordinate c;
  c.x = 1;
  c.y = 2;
  c.z = 3;

  assert_int(c.x, ==, 1, "should set x");
  assert_int(c.y, ==, 2, "should set y");
  assert_int(c.z, ==, 3, "should set z");
});

munit_case(RUN, test_scale_coordinate1, {
  struct Coordinate c = new_coord(1, 2, 3);
  struct Coordinate scaled = scale_coordinate(c, 2);

  assert_int(scaled.x, ==, 2, "should scale x");
  assert_int(scaled.y, ==, 4, "should scale y");
  assert_int(scaled.z, ==, 6, "should scale z");
});

munit_case(SUBMIT, test_scale_coordinate2, {
  struct Coordinate c = new_coord(4, 2, 0);
  struct Coordinate scaled = scale_coordinate(c, 2);

  assert_int(scaled.x, ==, 8, "should scale x");
  assert_int(scaled.y, ==, 4, "should scale y");
  assert_int(scaled.z, ==, 0, "should scale z");
});

munit_case(SUBMIT, test_original_unchanged, {
  struct Coordinate c = new_coord(1, 2, 3);
  struct Coordinate scaled = scale_coordinate(c, 2);

  assert_int(c.x, ==, 1, "original x should remain unchanged");
  assert_int(c.y, ==, 2, "original y should remain unchanged");
  assert_int(c.z, ==, 3, "original z should remain unchanged");
});

int main() {
  MunitTest tests[] = {
    munit_test("/create_coordinate", test_new_coordinate),
    munit_test("/test_scale_coordinate1", test_scale_coordinate1),
    munit_test("/test_scale_coordinate2", test_scale_coordinate2),
    munit_test("/test_original_unchanged", test_original_unchanged),
    munit_null_test,
  };

  MunitSuite suite = munit_suite("coordinates", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}
