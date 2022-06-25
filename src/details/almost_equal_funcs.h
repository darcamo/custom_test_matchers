#ifndef CUSTOM_CATCH_MATCHERS_ALMOST_EQUAL_FUNCS_H
#define CUSTOM_CATCH_MATCHERS_ALMOST_EQUAL_FUNCS_H

#include <catch2/catch_all.hpp>

namespace details {

/**
 * Test that two angles (in radians) are equal up to some margin
 *
 * @note This function correctly changes the angles to the [0,2PI) interval
 * before comparison.
 *
 * @param angleRad1 The first angle (in radians)
 * @param angleRad2 The second angle (in radians)
 * @param margin Tolerance for equality comparison
 * @return True if both angles are equal up to the margin.
 */
bool almostEqualAngles(double angleRad1, double angleRad2, double margin = 1e-5);

/**
 * Test that two angles (in degrees) are equal up to some margin
 *
 * @note This function correctly changes the angles to the [0,360) interval
 * before comparison.
 *
 * @param angleDeg1 The first angle (in radians)
 * @param angleDeg2 The second angle (in radians)
 * @param margin Tolerance for equality comparison
 * @return True if both angles are equal up to the margin.
 */
bool almostEqualAnglesDeg(double angleDeg1, double angleDeg2, double margin = 1e-5);

}  // namespace details
#endif  // CUSTOM_CATCH_MATCHERS_ALMOST_EQUAL_FUNCS_H
