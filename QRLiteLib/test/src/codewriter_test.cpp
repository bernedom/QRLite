#include "QRLite/Scanner.h"
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

TEST_CASE(
    "Writing a string to an image and reading it back returns the same string",
    "[CodeWriter][Scanner]") {
  QRLite::CodeWriter codeWriter;
  QRLite::Scanner scanner;

  const QString originalString = "Test String";
  const auto writtenImage = codeWriter.writeCode(originalString);

  writtenImage.save("test_qr_code.png"); // Save for debugging if needed

  // Simulate reading the image back
  const auto scanResult = scanner.scan(writtenImage);

  REQUIRE(scanResult.has_value() == true);
  REQUIRE(scanResult.value() == originalString);
}