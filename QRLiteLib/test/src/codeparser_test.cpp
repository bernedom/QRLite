#include <CodeParser.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

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
  REQUIRE(result.value().toStdString() == "SomeRandom123");
}

TEST_CASE("URL without scheme returns a link with http://", "[CodeParser]") {
  const QString data =
      GENERATE("example.com", "www.example.com", "sub.domain.org",
               "test-site.net?with=query", "my-site.io/path",
               "test-site.net?with=query&multiple=params");

  const auto result = QRLite::CodeParser::parse(data);
  REQUIRE(result.has_value());
  REQUIRE(result.value().toStdString() ==
          QString("<a href=\"http://" + data + "\">http://" + data + "</a>")
              .toStdString());
}

TEST_CASE("Code with invalid TLD returns the original code", "[CodeParser]") {
  const auto data = GENERATE("example.c", "example.commM", "example.1a",
                             "example.", "ftp://non-http.com");
  const auto result = QRLite::CodeParser::parse(data);

  REQUIRE(result.has_value());
  REQUIRE(result.value().toStdString() == data);
}