#include <catch2/catch_test_macros.hpp>
#include <SimpleCollage/project.h>

TEST_CASE("A new project has an empty image", "[Project]")
{
    SimpleCollage::Project project;
    REQUIRE(project.getImage().isNull());
}