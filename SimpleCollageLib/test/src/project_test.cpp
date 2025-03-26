#include <SimpleCollage/project.h>
#include <catch2/catch_test_macros.hpp>

#include <QFile>

TEST_CASE("A new project has an empty image", "[Project]") {
  SimpleCollage::Project project;
  REQUIRE(project.getImage().isNull());
}

TEST_CASE("Adding an image to a project returns a non null image",
          "[Project]") {
  SimpleCollage::Project project;
  QFile file(":/images/checkerboard_64x64.jpg");
  project.addImage(file);
  REQUIRE_FALSE(project.getImage().isNull());
}
TEST_CASE("Passing a nonexisting image to addImage throws an exception",
          "[Project]") {
  SimpleCollage::Project project;
  QFile file(":/images/nonexisting.jpg");
  REQUIRE_THROWS(project.addImage(file));
}

TEST_CASE("Passing a file that is not an image to addImage throws an exception",
          "[Project]") {
  SimpleCollage::Project project;
  QFile file(":/images/corruped_image.xx");
  assert(file.exists());
  REQUIRE_THROWS(project.addImage(file));
}

TEST_CASE("Passing two images to add image arranges them horizontally") {
  SimpleCollage::Project project;
  QFile file1(":/images/checkerboard_64x64.jpg");
  project.addImage(file1);
  QFile file2(":/images/checkerboard_64x64.jpg");
  project.addImage(file2);
  const auto image = project.getImage();
  REQUIRE(image.width() == 128);
  REQUIRE(image.height() == 64);
}