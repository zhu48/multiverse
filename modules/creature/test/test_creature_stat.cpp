#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "creature/creature.hpp"

TEST_CASE("verify the base D&D stats match the statistic concept") {
    CHECK(mltvrs::creature::is_statistic_v<mltvrs::creature::dnd_stat>);
    CHECK(mltvrs::creature::is_statistic_v<mltvrs::creature::strength>);
    CHECK(mltvrs::creature::is_statistic_v<mltvrs::creature::dexterity>);
    CHECK(mltvrs::creature::is_statistic_v<mltvrs::creature::constitution>);
    CHECK(mltvrs::creature::is_statistic_v<mltvrs::creature::intelligence>);
    CHECK(mltvrs::creature::is_statistic_v<mltvrs::creature::wisdom>);
    CHECK(mltvrs::creature::is_statistic_v<mltvrs::creature::charisma>);
}
