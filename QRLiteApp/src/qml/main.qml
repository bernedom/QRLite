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

        onValidCodeDetected: code => {
            scanResultText.text = code;
        }
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
            // Height grows with text, up to 1/3 of window height
            height: Math.min(scanResultText.paintedHeight + 20, mainWindow.height / 3)
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
                text: ""
                textFormat: Text.RichText
                wrapMode: Text.Wrap
                onLinkActivated: function (link) {
                    Qt.openUrlExternally(link);
                }

                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                color: "black"
                font.pointSize: 16
            }
        }

        Rectangle {
            id: qrImage
            width: 300
            height: 300
            color: "white"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter

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
