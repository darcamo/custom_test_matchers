#include "almost_equal_funcs.h"
#include "util.h"
#include <catch2/catch.hpp>

namespace details {

bool almostEqualAngles(double angleRad1, double angleRad2, double margin) {
  return fixAngle(angleRad1) == Approx(fixAngle(angleRad2)).margin(margin);
}

} // namespace details
