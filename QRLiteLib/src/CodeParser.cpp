#include "CodeParser.h"

#include <QtCore/QRegularExpression>
#include <expected>
namespace QRLite::CodeParser {

std::expected<QString, QString> processUrl(const QString &input) {
  // Check if the string already has a protocol
  QRegularExpression protocolRegex(R"(^https?://.+)");
  if (protocolRegex.match(input).hasMatch()) {
    return input; // Already has protocol, return as-is
  }

  // Regex to match URL-like strings without protocol
  // Based on the provided regex but without the protocol part
  QRegularExpression urlRegex(
      R"(^(www\.)?[-a-zA-Z0-9@:%._\+~#=]{2,256}\.[a-z]{2,4}\b([-a-zA-Z0-9@:%_\+.~#?&//=]*)$)");

  if (urlRegex.match(input).hasMatch()) {
    return "http://" + input;
  }

  return std::unexpected(input); // Not a URL, return original string
}

std::expected<QString, QString> parse(const QString &code) noexcept {
  // Simple validation: check if the code is non-empty and has at least 5
  // characters
  if (code.isEmpty()) {
    return std::unexpected("Code is empty");
  }
  const auto processed = processUrl(code);
  if (processed.has_value()) {
    return QString("<a href=\"%1\">%2</a>")
        .arg(processed.value(), processed.value());
  }
  return code; // Return the original code if no conditions are met
}
} // namespace QRLite::CodeParser
