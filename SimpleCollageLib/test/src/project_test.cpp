#include <SimpleCollage/project.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("A new project has an empty image", "[Project]") {
  SimpleCollage::Project project;
  REQUIRE(project.getImage().isNull());
}

TEST_CASE("Adding an image to a project returns the same image", "[Project]") {
  SimpleCollage::Project project;
  project.addImage(":/images/checkerboard_64x64.jpg");
  REQUIRE_FALSE(project.getImage().isNull());
}

TEST_CASE("Passing a nonexisting image to addImage throws an exception",
          "[Project]") {
  SimpleCollage::Project project;
  REQUIRE_THROWS(project.addImage(":/images/nonexisting.jpg"));
}