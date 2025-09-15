#include <QRLite/Scanner.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Empty image returns empty string", "[Scanner]") {
  QRLite::Scanner scanner;
  const auto result = scanner.scan(QImage());
  REQUIRE_FALSE(result.has_value());
}

TEST_CASE("Scanning a valid QR Code returns the message", "[Scanner]") {
  QRLite::Scanner scanner;
  const QImage sample_image(":/images/test.png");
  REQUIRE_FALSE(sample_image.isNull());
  const auto result = scanner.scan(sample_image);
  REQUIRE(result.has_value());
  REQUIRE(result.value().toStdString() == "I have the best words.");
}

TEST_CASE("Scan an image using path", "[Scanner]") {
  QRLite::Scanner scanner;
  const auto result = scanner.scan(":/images/test.png");
  REQUIRE(result.has_value());
  REQUIRE(result.value().toStdString() == "I have the best words.");
}

TEST_CASE("Scanning an image from an invalid path returns an error message",
          "[Scanner]") {
  QRLite::Scanner scanner;
  const auto result = scanner.scan(":/images/non_existent.png");
  REQUIRE_FALSE(result.has_value());
}
