#ifndef MULTIVERSE_CREATURE_HPP
#define MULTIVERSE_CREATURE_HPP

#include <cstdint>

#include <concepts>

#include "stars/concepts.hpp"

namespace mltvrs::creature {

    // concepts syntax not yet supported
    // clang-format off

    template<typename T>
    concept statistic = requires(T stat, typename T::numeric_type n) {
        requires std::integral<typename T::numeric_type>;
        requires stars::
            explicitly_totally_ordered_with<T, typename T::numeric_type>;

        requires stars::explicitly_convertible_to<T, typename T::numeric_type>;
        requires stars::explicitly_convertible_to<typename T::numeric_type, T>;

        { stat +    n } -> std::same_as<T>;
        {    n + stat } -> std::same_as<T>;
        { stat -    n } -> std::same_as<T>;
        { stat - stat } -> std::signed_integral;
        { stat +=   n } -> std::same_as<T&>;
        { stat -=   n } -> std::same_as<T&>;
    };

    // clang-format on

    template<statistic T>
    constexpr bool is_statistic() noexcept {
        return true;
    };

    template<typename T>
    inline constexpr bool is_statistic_v = is_statistic<T>();

    class dnd_stat {
    public:
        using numeric_type = std::uint_fast16_t;

        explicit constexpr dnd_stat(numeric_type) noexcept;

        explicit constexpr operator numeric_type() const noexcept;

        constexpr bool operator==(const dnd_stat& rhs) const noexcept = default;
        constexpr auto
        operator<=>(const dnd_stat& rhs) const noexcept = default;

    private:
        numeric_type m_value;
    };

    class strength final : public dnd_stat {
        using dnd_stat::dnd_stat;
    };

    class dexterity final : public dnd_stat {
        using dnd_stat::dnd_stat;
    };

    class constitution final : public dnd_stat {
        using dnd_stat::dnd_stat;
    };

    class intelligence final : public dnd_stat {
        using dnd_stat::dnd_stat;
    };

    class wisdom final : public dnd_stat {
        using dnd_stat::dnd_stat;
    };

    class charisma final : public dnd_stat {
        using dnd_stat::dnd_stat;
    };

    constexpr bool
    operator==(const dnd_stat& lhs, const dnd_stat::numeric_type& rhs) noexcept;
    constexpr auto
    operator<=>(const dnd_stat& lhs, const dnd_stat::numeric_type& rhs) noexcept
        -> std::strong_ordering;

    template<std::derived_from<dnd_stat> S>
    constexpr auto operator+=(S& lhs, std::integral auto rhs) noexcept -> S&;
    template<std::derived_from<dnd_stat> S>
    constexpr auto operator-=(S& lhs, std::integral auto rhs) noexcept -> S&;
    template<std::derived_from<dnd_stat> S>
    constexpr auto operator++(S& s) noexcept -> S&;
    template<std::derived_from<dnd_stat> S>
    constexpr auto operator++(S& s, int /*unused*/) noexcept -> S;
    template<std::derived_from<dnd_stat> S>
    constexpr auto operator--(S& s) noexcept -> S&;
    template<std::derived_from<dnd_stat> S>
    constexpr auto operator--(S& s, int /*unused*/) noexcept -> S;
    template<std::derived_from<dnd_stat> S>
    constexpr auto operator+(S lhs, std::integral auto rhs) noexcept -> S;
    template<std::derived_from<dnd_stat> S>
    constexpr auto operator+(std::integral auto rhs, S lhs) noexcept -> S;
    template<std::derived_from<dnd_stat> S>
    constexpr auto operator-(S lhs, std::integral auto rhs) noexcept -> S;
    template<std::derived_from<dnd_stat> S>
    constexpr auto operator-(S lhs, S rhs) noexcept
        -> std::make_signed_t<typename S::numeric_type>;

} // namespace mltvrs::creature

template<std::derived_from<mltvrs::creature::dnd_stat> S>
class std::numeric_limits<S> {
public:
    static constexpr bool is_specialized = true;

    static constexpr S min() noexcept { return 0; }
    static constexpr S max() noexcept { return 35; }
    static constexpr S lowest() noexcept { return 0; }

    static constexpr int digits =
        std::numeric_limits<typename S::numeric_type>::digits;
    static constexpr int digits10     = 2;
    static constexpr int max_digits10 = 2;

    static constexpr bool is_signed  = false;
    static constexpr bool is_integer = true;
    static constexpr bool is_exact   = true;

    static constexpr int radix = 2;
    static constexpr S   epsilon() noexcept { return 0; }
    static constexpr S   round_error() noexcept { return 0; }

    static constexpr int min_exponent   = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent   = 0;
    static constexpr int max_exponent10 = 0;

    static constexpr bool                    has_infinity      = false;
    static constexpr bool                    has_quiet_NaN     = false;
    static constexpr bool                    has_signaling_NaN = false;
    static constexpr std::float_denorm_style has_denorm = std::denorm_absent;
    static constexpr bool                    has_denorm_loss = false;

    static constexpr S infinity() noexcept { return 0; }
    static constexpr S quiet_NaN() noexcept { return 0; }
    static constexpr S signaling_NaN() noexcept { return 0; }
    static constexpr S denorm_min() noexcept { return 0; }

    static constexpr bool is_iec559       = false;
    static constexpr bool is_bounded      = true;
    static constexpr bool is_modulo       = false;
    static constexpr bool traps           = false;
    static constexpr bool tinyness_before = false;

    static constexpr std::float_round_style round_style =
        std::round_toward_zero;
};

template<>
struct std::common_type<
    mltvrs::creature::dnd_stat,
    mltvrs::creature::dnd_stat::numeric_type> {
    using type = mltvrs::creature::dnd_stat;
};

template<>
struct std::common_type<
    mltvrs::creature::dnd_stat::numeric_type,
    mltvrs::creature::dnd_stat> {
    using type = mltvrs::creature::dnd_stat;
};

template<
    std::derived_from<mltvrs::creature::dnd_stat> T,
    template<typename>
    typename TQual,
    template<typename>
    typename UQual>
struct std::basic_common_reference<T, typename T::numeric_type, TQual, UQual> {
    using type = TQual<T>&;
};

template<
    std::derived_from<mltvrs::creature::dnd_stat> U,
    template<typename>
    typename TQual,
    template<typename>
    typename UQual>
struct std::basic_common_reference<typename U::numeric_type, U, TQual, UQual> {
    using type = UQual<U>&;
};

#endif // #ifndef MULTIVERSE_CREATURE_HPP