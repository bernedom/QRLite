import QtQuick
import QtQuick.Window
import QtMultimedia
import QtQuick.Controls
import QRLite 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: "QRLite"

    CodeReader {
        id: codeReader
        videoSink: preview.videoSink
    }

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

        Rectangle {
            id: qrImage
            width: 300
            height: 300
            color: "white"
            anchors.centerIn: parent

            CaptureSession {
                id: captureSession
                camera: Camera {
                    id: camera
                    focusMode: Camera.FocusModeAutoNear
                }

                videoOutput: preview

                Component.onCompleted: {
                    camera.start();
                }
            }

            VideoOutput {
                id: preview
                visible: true
                anchors.fill: parent
            }
        }
    }
}
