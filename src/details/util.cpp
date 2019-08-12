#include "util.h"

namespace details {

double fixAngle(double angleRad) {
  constexpr const double PI =
      3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

  auto quotient = static_cast<int>(angleRad / (2 * PI));

  if (quotient >= 1 || quotient <= -1) {
    angleRad -= quotient * 2 * PI;
  }

  if (angleRad < 0) {
    angleRad += 2 * PI;
  }

  return angleRad;
}

} // namespace details
