import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: "QRLite"

    Item {
        id: root
        focus: true
        anchors.fill: parent

        Keys.onPressed: event => {
            if (event.key === Qt.Key_Escape) {
                Qt.quit();
            }
        }

        Rectangle {
            width: 300
            height: 300
            color: "white"
            anchors.centerIn: parent

            Image {
                source: "qrc:/images/images/test.png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }
        }

        Rectangle {
            width: 120
            height: 50
            color: "green"
            radius: 8
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40

            Text {
                text: "scan"
                color: "white"
                anchors.centerIn: parent
                font.bold: true
                font.pointSize: 18
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    scanResultText.text = scanner.scan("qrc:/images/images/test.png");
                }
            }
        }

        Rectangle {
            width: parent.width - 40
            height: 40
            color: "transparent"
            border.color: "black"
            border.width: 2
            radius: 6
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 40

            Text {
                id: scanResultText
                objectName: "scanResultText"
                text: "abracadabra"
                anchors.centerIn: parent
                color: "black"
                font.pointSize: 16
            }
        }
    }
}
