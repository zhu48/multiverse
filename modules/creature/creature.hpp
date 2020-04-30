#ifndef MULTIVERSE_CREATURE_HPP
#define MULTIVERSE_CREATURE_HPP

#include "creature/statistic.hpp"

namespace mltvrs::creature {

    enum class proficient { none, half, full, expert };

    template<statistic S>
    struct saving_throw {
        proficient proficiency;

        [[nodiscard]] constexpr auto modifier() const noexcept -> modifier_type;
    };

    class creature {
    public:
        constexpr creature(
            std::pmr::string char_name,
            strength         str,
            dexterity        dex,
            constitution     con,
            wisdom           wis,
            intelligence     intel,
            charisma         cha) noexcept;

        [[nodiscard]] constexpr auto name() const noexcept
            -> const std::pmr::string&;
        [[nodiscard]] constexpr auto name() noexcept -> std::pmr::string&;

        template<statistic S>
        [[nodiscard]] constexpr auto attr() const noexcept(false) -> const S&;
        template<statistic S>
        [[nodiscard]] constexpr auto attr() noexcept(false) -> S&;

        template<statistic S>
        [[nodiscard]] constexpr auto save() const noexcept(false) ->
            typename saving_throw<S>::modifier_type;

    private:
        std::pmr::string m_name;

        strength     m_str;
        dexterity    m_dex;
        constitution m_con;
        wisdom       m_wis;
        intelligence m_int;
        charisma     m_cha;

        saving_throw<strength>     m_str_save;
        saving_throw<dexterity>    m_dex_save;
        saving_throw<constitution> m_con_save;
        saving_throw<wisdom>       m_wis_save;
        saving_throw<intelligence> m_int_save;
        saving_throw<charisma>     m_cha_save;
    };

} // namespace mltvrs::creature

#endif // #ifndef MULTIVERSE_CREATURE_HPP
