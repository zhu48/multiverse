#ifndef MULTIVERSE_STARS_CONCEPTS_HPP
#define MULTIVERSE_STARS_CONCEPTS_HPP

#include <concepts>

namespace mltvrs::stars {

    // concepts syntax not yet supported
    // clang-format off

    template<typename B>
    concept boolean =
        std::movable<std::remove_cvref_t<B>> &&
        requires(
            const std::remove_reference_t<B>& b1,
            const std::remove_reference_t<B>& b2,
            const bool                        a
        ) {
            { b1  } -> std::convertible_to<bool>;
            { !b1 } -> std::convertible_to<bool>;
            { b1 && b2 } -> std::same_as<bool>;
            { b1 &&  a } -> std::same_as<bool>;
            {  a && b2 } -> std::same_as<bool>;
            { b1 || b2 } -> std::same_as<bool>;
            { b1 ||  a } -> std::same_as<bool>;
            {  a || b2 } -> std::same_as<bool>;
            { b1 == b2 } -> std::convertible_to<bool>;
            { b1 ==  a } -> std::convertible_to<bool>;
            {  a == b2 } -> std::convertible_to<bool>;
            { b1 != b2 } -> std::convertible_to<bool>;
            { b1 !=  a } -> std::convertible_to<bool>;
            {  a != b2 } -> std::convertible_to<bool>;
        };

    template<typename To, typename From>
    concept explicitly_convertible_to =
        std::constructible_from<To, From> && !std::convertible_to<To, From>;

    template<typename T, typename U>
    concept explicitly_common_reference_with =
        std::same_as<
            std::common_reference_t<T, U>,
            std::common_reference_t<U, T>
        > &&
        std::constructible_from<T, std::common_reference_t<T, U>> &&
        std::constructible_from<U, std::common_reference_t<T, U>>;

    template<typename T, typename U>
    concept weakly_equality_comparable_with =
        requires(
            const std::remove_reference_t<T>& t,
            const std::remove_reference_t<U>& u
        ) {
            { t == u } -> boolean;
            { t != u } -> boolean;
            { u == t } -> boolean;
            { u != t } -> boolean;
        };

    template<typename T, typename U>
    concept explicitly_equality_comparable_with =
        std::equality_comparable<T> &&
        std::equality_comparable<U> &&
        explicitly_common_reference_with<
            const std::remove_reference_t<T>&,
            const std::remove_reference_t<U>&
        > &&
        explicitly_common_reference_with<
            const std::remove_reference_t<T>&,
            const std::remove_reference_t<U>&
        > &&
        weakly_equality_comparable_with<T, U>;

    template<typename T, typename U>
    concept explicitly_totally_ordered_with =
        std::totally_ordered<T> &&
        std::totally_ordered<U> &&
        explicitly_equality_comparable_with<T, U> &&
        std::totally_ordered<
            std::common_reference_t<
                const std::remove_reference_t<T>&,
                const std::remove_reference_t<U>&
            >
        > &&
        requires(
            const std::remove_reference_t<T>& t,
            const std::remove_reference_t<U>& u
        ) {
            { t <  u } -> boolean;
            { t >  u } -> boolean;
            { t <= u } -> boolean;
            { t >= u } -> boolean;
            { u <  t } -> boolean;
            { u >  t } -> boolean;
            { u <= t } -> boolean;
            { u >= t } -> boolean;
        };

    // clang-format on

} // namespace mltvrs::stars

#endif // #ifndef MULTIVERSE_STARS_CONCEPTS_HPP
