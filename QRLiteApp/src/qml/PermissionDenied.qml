// SPDX-FileCopyrightText: 2026 Dominik Berner
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick

Rectangle {
    id: permissionCheck
    width: parent.width
    height: parent.height
    property color backgroundColor: "black"
    property color textColor: "red"
    color: backgroundColor

    Text {
        id: permissionText
        text: "Camera permissions denied. Please enable camera permissions in system settings."
        color: permissionCheck.textColor
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
        width: parent.width * 0.8
    }
}
