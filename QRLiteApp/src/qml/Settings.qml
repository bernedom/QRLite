import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    property bool darkModeEnabled: false
    property color backgroundColor: "#f5f5f5"
    property color panelColor: "#ffffff"
    property color textColor: "#111111"
    property color secondaryTextColor: "#666666"
    property color borderColor: "#111111"
    property color accentColor: "#005a9c"
    property int textMargin: 10

    color: backgroundColor

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: textMargin * 2
        spacing: textMargin * 1.5

        Label {
            text: "Settings"
            color: root.textColor
            font.pointSize: 20
            font.bold: true
        }

        Rectangle {
            Layout.fillWidth: true
            color: root.panelColor
            border.color: root.borderColor
            border.width: 2
            radius: 8
            implicitHeight: darkModeLayout.implicitHeight + root.textMargin * 2

            RowLayout {
                id: darkModeLayout
                anchors.fill: parent
                anchors.margins: root.textMargin
                spacing: 10

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 2

                    Label {
                        text: "Dark mode"
                        color: root.textColor
                    }

                    Label {
                        text: "Use a darker color theme for the app"
                        color: root.secondaryTextColor
                        font.pointSize: 9
                    }
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

        Label {
            Layout.fillWidth: true
            text: "More settings will be added here."
            color: root.secondaryTextColor
            horizontalAlignment: Text.AlignHCenter
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
