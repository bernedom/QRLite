/*
 * SPDX-FileCopyrightText: 2026 Dominik Berner
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QtCore/QString>
#include <expected>

namespace QRLite {

namespace CodeParser {
std::expected<QString, QString> parse(const QString &code) noexcept;

}
} // namespace QRLite