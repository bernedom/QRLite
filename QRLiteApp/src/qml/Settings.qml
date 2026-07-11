import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    property bool darkModeEnabled: false
    property color panelColor: "#ffffff"
    property color textColor: "#111111"
    property color borderColor: "#111111"
    property color accentColor: "#005a9c"
    property int textMargin: 10

    color: panelColor
    border.color: borderColor
    border.width: 2
    radius: 6
    implicitWidth: contentLayout.implicitWidth + textMargin * 2
    implicitHeight: contentLayout.implicitHeight + textMargin * 2

    RowLayout {
        id: contentLayout
        anchors.fill: parent
        anchors.margins: textMargin
        spacing: 8

        Label {
            text: "Dark"
            color: root.textColor
        }

        Switch {
            id: darkModeSwitch
            checked: root.darkModeEnabled
            onToggled: root.darkModeEnabled = checked

            palette.windowText: root.textColor
            palette.text: root.textColor
            palette.buttonText: root.textColor
            palette.highlight: root.accentColor
        }
    }
}
