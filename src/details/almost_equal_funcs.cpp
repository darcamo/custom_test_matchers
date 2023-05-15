#include "custom_test_matchers/details/almost_equal_funcs.h"
#include <catch2/catch_approx.hpp>
#include "custom_test_matchers/details/util.h"

namespace details {

bool almostEqualAngles(double angleRad1, double angleRad2, double margin) {
    return fixAngle(angleRad1) == Catch::Approx(fixAngle(angleRad2)).margin(margin);
}

bool almostEqualAnglesDeg(double angleDeg1, double angleDeg2, double margin) {
    return fixAngleDeg(angleDeg1) == Catch::Approx(fixAngleDeg(angleDeg2)).margin(margin);
}

}  // namespace details
