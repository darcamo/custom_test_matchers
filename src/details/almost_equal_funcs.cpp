#include "almost_equal_funcs.h"
#include <catch2/catch.hpp>
#include "util.h"

namespace details {

bool almostEqualAngles(double angleRad1, double angleRad2, double margin) {
    return fixAngle(angleRad1) == Approx(fixAngle(angleRad2)).margin(margin);
}

bool almostEqualAnglesDeg(double angleDeg1, double angleDeg2, double margin) {
    return fixAngleDeg(angleDeg1) == Approx(fixAngleDeg(angleDeg2)).margin(margin);
}

}  // namespace details
