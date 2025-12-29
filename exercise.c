#include "exercise.h"

char *get_temperature_status(int temp)
{
  char *result;
  if (temp < 70) {
    result = "too cold";
  } else if (temp > 90) {
    result = "too hot";
  } else {
    result = "just right";
  }
  return result;
}