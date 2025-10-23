#include <QRLite/CodeWriter.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Writing an empty string returns an empty image", "[CodeWriter]") {
  QRLite::CodeWriter codeWriter;
  const auto result = codeWriter.writeCode("");
  REQUIRE(result.isNull() == true);
}

TEST_CASE("Writing a non-empty string returns a non-empty image",
          "[CodeWriter]") {
  QRLite::CodeWriter codeWriter;
  const auto result = codeWriter.writeCode("Hello, World!");
  REQUIRE(result.isNull() == false);
}