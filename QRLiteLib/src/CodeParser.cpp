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
  // If the code looks like a URL without a scheme, prefix with "http://"
  int lastDot = code.lastIndexOf('.');
  if (lastDot > 0 && !code.contains(' ')) {
    QString tld = code.mid(lastDot + 1);
    // Check TLD length and that it ends with a letter
    if ((tld.length() == 2 || tld.length() == 3) && tld.back().isLetter() &&
        code.back().isLetter()) {
      return "<a href=\"http://" + code + "\">http://" + code + "</a>";
    }
  }
  return code; // Return the original code if no conditions are met
}
} // namespace QRLite::CodeParser
