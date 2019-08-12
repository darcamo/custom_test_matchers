#include "matchers_imp.h"

namespace details {

template <>
bool Tuple2EqualsMatcher<double, double>::match(const Tuple2& t) const {
    return (std::get<0>(this->t) == Approx(std::get<0>(t))) && (std::get<1>(this->t) == Approx(std::get<1>(t)));
}

}  // namespace details
