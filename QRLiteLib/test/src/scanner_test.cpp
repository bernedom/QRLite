#include <QRLite/scanner.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Empty image returns empty string", "[Scanner]") {
  QRLite::Scanner scanner;
  const auto result = scanner.scan(QImage());
  REQUIRE(result == QString());
}

TEST_CASE("Scanning a valid QR Code returns the message", "[Scanner]") {
  QRLite::Scanner scanner;
  const QImage sample_image(":/images/test.png");
  REQUIRE_FALSE(sample_image.isNull());
  const auto result = scanner.scan(sample_image);
  REQUIRE(result.toStdString() == "I have the best words.");
}
