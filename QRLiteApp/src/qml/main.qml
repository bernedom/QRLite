import QtQuick
import QtQuick.Window
import QtMultimedia
import QtQuick.Controls
import QRLite 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 640
    title: "QRLite"

    readonly property int horizontalMargin: 40
    readonly property int verticalMargin: 40
    readonly property int spacing: 20
    readonly property int textMargin: 10

    CodeReader {
        id: codeReader
        videoSink: preview.videoSink

        onValidCodeDetected: code => {
            scanResultText.text = code;
        }
    }

    PermissionChecker {
        id: permissionChecker
        onCameraPermissionGrantedChanged: {
            if (cameraPermissionGranted) {
                captureSession.camera.start();
            }
        }
        onCameraCheckPendingChanged: cameraCheckPending = permissionChecker.cameraCheckPending
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
            id: scanResultBox
            width: parent.width - horizontalMargin * 2
            // Height grows with text, up to 1/3 of window height
            height: Math.min(scanResultText.paintedHeight + spacing, mainWindow.height / 3)
            color: "transparent"
            border.color: "black"
            border.width: 2
            radius: 6
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: verticalMargin

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
                anchors.topMargin: textMargin
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: textMargin
                anchors.rightMargin: textMargin
                color: "black"
                font.pointSize: 16
            }
        }

        Rectangle {
            id: cameraView
            width: parent.width - horizontalMargin * 2
            height: parent.height - scanResultBox.height - verticalMargin * 2 - spacing
            color: "transparent"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: spacing
            anchors.horizontalCenter: parent.horizontalCenter

            PermissionCheck {
                id: permissionCheck
                anchors.fill: parent
                visible: cameraCheckPending
            }

            PermissionDenied {
                id: permissionDenied
                anchors.fill: parent
                visible: permissionChecker.cameraPermissionGranted === false && !cameraCheckPending
            }

            Item {
                id: cameraContainer
                anchors.fill: parent
                visible: permissionChecker.cameraPermissionGranted && !cameraCheckPending

                CaptureSession {
                    id: captureSession
                    camera: Camera {
                        id: camera
                        focusMode: Camera.FocusModeAutoNear
                    }

                    videoOutput: preview

                    Component.onCompleted: {
                        if (cameraPermissionGranted) {
                            camera.start();
                        }
                    }
                }

                VideoOutput {
                    id: preview
                    visible: camera.status === Camera.ActiveStatus
                    anchors.fill: parent
                }
            }
        }
    }
}
