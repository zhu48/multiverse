#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "creature/creature.hpp"

TEST_CASE("verify the base D&D stats match the statistic concept") {
    CHECK(mltvrs::creature::statistic<mltvrs::creature::dnd_stat>);
    CHECK(mltvrs::creature::statistic<mltvrs::creature::strength>);
    CHECK(mltvrs::creature::statistic<mltvrs::creature::dexterity>);
    CHECK(mltvrs::creature::statistic<mltvrs::creature::constitution>);
    CHECK(mltvrs::creature::statistic<mltvrs::creature::intelligence>);
    CHECK(mltvrs::creature::statistic<mltvrs::creature::wisdom>);
    CHECK(mltvrs::creature::statistic<mltvrs::creature::charisma>);
}
