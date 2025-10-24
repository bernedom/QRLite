#include "QRLite/Scanner.h"
#include <QRLite/CodeWriter.h>
#include <QtCore/QTemporaryFile>
#include <catch2/catch_test_macros.hpp>

namespace {

class TempFile {

public:
  TempFile() {
    const auto temp_dir = std::filesystem::temp_directory_path();
    const auto filename = std::filesystem::path("qrlite_test_tempfile.png");
    _path = (temp_dir / filename).string();
  }

  ~TempFile() {
    std::error_code ec;
    std::filesystem::remove(_path, ec);
  }

  const QString fileName() const { return QString::fromStdString(_path); }

private:
  std::string _path;
};

} // namespace

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

  // Simulate reading the image back
  const auto scanResult = scanner.scan(writtenImage);

  REQUIRE(scanResult.has_value() == true);
  REQUIRE(scanResult.value() == originalString);
}

TEST_CASE("Saving a QR code to a file creates a valid image file",
          "[CodeWriter]") {
  QRLite::CodeWriter codeWriter;
  const QString testString = "File Save Test";
  TempFile tempFile;

  // Save the QR code to a file
  codeWriter.saveCodeToFile(testString, tempFile.fileName());

  QFile file(tempFile.fileName());
  REQUIRE(tempFile.fileName().isEmpty() == false);
  REQUIRE(file.exists() == true);

  // Load the saved image
  QImage loadedImage(tempFile.fileName());
  REQUIRE(loadedImage.isNull() == false);
}