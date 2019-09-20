#include "util.h"
#include <cmath>

namespace details {

double fixAngle(double angleRad) {
  constexpr const double PI =
      3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

  // Make sure small negative numbers, such as -1e-15 are not mapped to 2pi,
  // instead of 0
  if (std::abs(angleRad) < 1e-10) {
    angleRad = 0.0;
  }

  auto quotient = static_cast<int>(angleRad / (2 * PI));

  if (quotient >= 1 || quotient <= -1) {
    angleRad -= quotient * 2 * PI;
  }

  if (angleRad < 0) {
    angleRad += 2 * PI;
  }

  return angleRad;
}

double fixAngleDeg(double angleDeg) {
    // Make sure small negative numbers, such as -1e-15 are not mapped to 2pi,
    // instead of 0
    if (std::abs(angleDeg) < 1e-10) {
        angleDeg = 0.0;
    }

    auto quotient = static_cast<int>(angleDeg / 360.0);

    if (quotient >= 1 || quotient <= -1) {
        angleDeg -= quotient * 360.0;
    }

    if (angleDeg < 0) {
        angleDeg += 360.0;
    }

    return angleDeg;
}

} // namespace details
