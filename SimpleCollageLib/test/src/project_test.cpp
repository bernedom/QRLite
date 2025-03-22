#include <catch2/catch_test_macros.hpp>
#include <SimpleCollage/project.h>

TEST_CASE("A new project has an empty image", "[Project]")
{
    SimpleCollage::Project project;
    REQUIRE(project.getImage().isNull());
}

TEST_CASE("Adding an image to a project returns the same image", "[Project]") {
  SimpleCollage::Project project;
  project.addImage(":/images/checkerboard_64x64.jpg");
  REQUIRE_FALSE(project.getImage().isNull());
}