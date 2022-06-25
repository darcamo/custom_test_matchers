#ifndef CUSTOM_CATCH_MATCHERS_ALL_H
#define CUSTOM_CATCH_MATCHERS_ALL_H

#include <catch2/catch_all.hpp>
#include <tuple>
#include "details/almost_equal_funcs.h"
#include "details/custom_string_makers.h"
#include "details/matchers_imp.h"

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// xxxxxxxxxxxxxxx The builder functions xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Once a specialization of Catch::MatcherBase is defined, we also need a
// "builder function" that we will call in the test code to create an object of
// the Catch::MatcherBase. This design of using a function to create the object
// of the correct specialization of Catch::MatcherBase is interesting because
// the function can have some clear name, such as "Equals", and be overloaded
// for each type to return an object of the correct specialization of
// Catch::MatcherBase.
//
// Note: Catch already define several overloads for an "Equals" function and we
// are adding more overloads here. Note2: The returned matcher supports bolean
// operator. Therefore, it is possible to use something such as
// "!Equal(arg1)" in a REQUIRE_THAT.

// Template version for armadillo types
template <typename T,
          typename = typename std::enable_if<arma::is_arma_type<T>::value || arma::is_arma_cube_type<T>::value>::type>
inline auto Equals(T c, double tol = 1e-10) {
    return details::ArmadilloEqualsMatcher(c.eval(), tol);
}

template <class T>
inline auto EqualsWithinTolerance(T c, double tol) {
    return details::ArmadilloEqualsMatcher(c.eval(), tol);
}

inline details::AngleEqualsMatcher EqualsAngle(double angle) { return details::AngleEqualsMatcher(angle); }

inline details::AngleDegEqualsMatcher EqualsAngleDeg(double angle) { return details::AngleDegEqualsMatcher(angle); }

template <typename T, typename U>
inline details::Tuple2EqualsMatcher<T, U> Equals(std::tuple<T, U> t) {
    return details::Tuple2EqualsMatcher<T, U>(t);
}

template <typename T>
inline details::IsInRangeMatcher<T> InRange(T minimum, T maximum) {
    return details::IsInRangeMatcher(std::forward<T>(minimum), std::forward<T>(maximum));
}

#endif  // CUSTOM_CATCH_MATCHERS_ALL_H
