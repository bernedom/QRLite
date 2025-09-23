#include <CodeParser.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Empty code returns an error", "[CodeParser]") {
  const auto result = QRLite::CodeParser::parse("");
  REQUIRE_FALSE(result.has_value());
  REQUIRE(result.error() == "Code is empty");
}

TEST_CASE("Valid URL returns a link", "[CodeParser]") {
  const auto result = QRLite::CodeParser::parse("https://example.com");
  REQUIRE(result.has_value());
  REQUIRE(result.value() ==
          "<a href=\"https://example.com\">https://example.com</a>");
}

TEST_CASE("Non-URL code returns the original code", "[CodeParser]") {
  const auto result = QRLite::CodeParser::parse("SomeRandom123");
  REQUIRE(result.has_value());
  REQUIRE(result.value() == "SomeRandom123");
}