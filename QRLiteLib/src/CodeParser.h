#pragma once

#include <QtCore/QString>
#include <expected>

namespace QRLite {

namespace CodeParser {
std::expected<QString, QString> parse(const QString &code) noexcept;

}
} // namespace QRLite