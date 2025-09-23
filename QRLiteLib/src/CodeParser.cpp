#include "CodeParser.h"

namespace QRLite::CodeParser {
std::expected<QString, QString> parse(const QString &code) noexcept {
  // Simple validation: check if the code is non-empty and has at least 5
  // characters
  if (code.isEmpty()) {
    return std::unexpected("Code is empty");
  }
  if (code.startsWith("http://") || code.startsWith("https://")) {
    return "<a href=\"" + code + "\">" + code +
           "</a>"; // Return as a link if it's a URL
  }
  return code; // Return the original code if no conditions are met
}
} // namespace QRLite::CodeParser
