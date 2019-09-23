#ifndef CUSTOM_CATCH_MATCHERS_CUSTOM_STRING_MAKERS_H
#define CUSTOM_CATCH_MATCHERS_CUSTOM_STRING_MAKERS_H

#include <armadillo>
#include <catch2/catch.hpp>
#include <tuple>

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// xxxxxxxxxxxxxxx Catch::StringMaker specialisations
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// A specialization of Catch::StringMaker for some type will tell catch how to
// convert this type to a string. With this, the catch error messages will show
// our stringfied type, instead of the default "{?}" shown for types that Catch
// does not know hot to convert to string.
//
// Note that all StringMaker specializations must be in the Catch namespace
namespace Catch {

// Specialization for tuples
template <typename T, typename U>
struct StringMaker<std::tuple<T, U>> {
    static std::string convert(std::tuple<T, U> const &value) {
        std::ostringstream ss;
        ss << "(" << std::get<0>(value) << ", " << std::get<1>(value) << ")";
        return ss.str();
    }
};

// Specialization for arma::vec
template <typename T>
struct StringMaker<arma::Col<T>> {
    static std::string convert(arma::Col<T> const &value) {
        std::ostringstream ss;

        ss << "Vector (x" << value.size() << ")";

        if(value.size() - 1 > 6) {
            auto max_index = std::min(value.size() - 1, static_cast<arma::uword>(6));
            ss << " -> Only showing from index 0 to " << max_index << "\n";
            value.subvec(0, max_index).st().print(ss);
        } else {
            ss << "\n";
            value.st().print(ss);
        }

        return ss.str();
    }
};

// Specialization for arma::rowvec
template <typename T>
struct StringMaker<arma::Row<T>> {
    static std::string convert(arma::Row<T> const &value) {
        std::ostringstream ss;

        ss << "Row Vector (x" << value.size() << ")";

        if(value.size() - 1 > 6) {
            auto max_index = std::min(value.size() - 1, static_cast<arma::uword>(6));
            ss << " -> Only showing from index 0 to " << max_index << "\n";
            value.subvec(0, max_index).print(ss);
        } else {
            ss << "\n";
            value.print(ss);
        }

        return ss.str();
    }
};

// Specialization for arma::mat
template <typename T>
struct StringMaker<arma::Mat<T>> {
    static std::string convert(arma::Mat<T> const &value) {
        std::ostringstream ss;

        ss << "(" << value.n_rows << "x" << value.n_cols << ")";

        auto max_cols = std::min(value.n_cols - 1, static_cast<arma::uword>(4));
        auto max_rows = std::min(value.n_rows - 1, static_cast<arma::uword>(5));

        if(max_rows != value.n_rows - 1 || max_cols != value.n_cols - 1) {
            ss << " -> Only showing from ";
            if(max_rows != value.n_rows - 1) {
                if(max_cols != value.n_cols - 1) {
                    ss << "row 0 to " << max_rows << " and column 0 to " << max_cols << "\n";
                } else {
                    ss << "row 0 to " << max_rows << "\n";
                }
            } else if(max_cols != value.n_cols - 1) {
                ss << "column 0 to " << max_cols << "\n";
            }

        } else {
            ss << "\n";
        }

        value.submat(0, 0, max_rows, max_cols).print(ss);

        return ss.str();
    }
};

}  // namespace Catch

#endif  // CUSTOM_CATCH_MATCHERS_CUSTOM_STRING_MAKERS_H
