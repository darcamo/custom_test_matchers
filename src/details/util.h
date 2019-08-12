#ifndef CUSTOM_CATCH_MATCHERS_DETAILS_UTIL_H
#define CUSTOM_CATCH_MATCHERS_DETAILS_UTIL_H

namespace details {

/**
 * Change an angle to the interval [0,2pi)
 * @param angleRad The angle (in radians)
 * @return The angle in the interval [0,2pi)
 */
double fixAngle(double angleRad);

} // namespace details

#endif // CUSTOM_CATCH_MATCHERS_UTIL_H
