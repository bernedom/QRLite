import QtQuick
import QtQuick.Window
import QtMultimedia
import QtQuick.Controls
import QtQuick.Layouts
import QtCore as Core
import QRLite 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 640
    title: "QRLite"
    color: backgroundColor

    readonly property int horizontalMargin: 40
    readonly property int verticalMargin: 40
    readonly property int spacing: 20
    readonly property int textMargin: 10
    readonly property url picturesFolder: StandardPaths.writableLocation(StandardPaths.DownloadLocation) + "/QRLite/"
    property bool darkModeEnabled: false
    readonly property color backgroundColor: darkModeEnabled ? "#121212" : "#f5f5f5"
    readonly property color panelColor: darkModeEnabled ? "#1e1e1e" : "#ffffff"
    readonly property color textColor: darkModeEnabled ? "#f2f2f2" : "#111111"
    readonly property color secondaryTextColor: darkModeEnabled ? "#c8c8c8" : "#666666"
    readonly property color borderColor: darkModeEnabled ? "#8f8f8f" : "#111111"
    readonly property color statusBarColor: darkModeEnabled ? "#2a2a2a" : "#E0E0E0"
    readonly property color accentColor: darkModeEnabled ? "#7cc7ff" : "#005a9c"

    function startCameraIfPermitted(permitted: bool) {
        if (permitted) {
            camera.start();
        }
    }

    Core.Settings {
        id: appSettings
        category: "Appearance"
        property bool darkModeEnabled: false
    }

    Component.onCompleted: {
        darkModeEnabled = appSettings.darkModeEnabled;
        permissionChecker.cameraPermissionChanged.connect(startCameraIfPermitted);
    }

    onDarkModeEnabledChanged: {
        appSettings.darkModeEnabled = darkModeEnabled;
    }

    CodeWriter {
        id: codeWriter
    }

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
                console.log("Escape pressed, quitting.");
                Qt.quit();
            }
        }

        RowLayout {
            id: topLayout
            width: parent.width - horizontalMargin * 2
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: mainWindow.spacing

            Rectangle {
                id: scanResultBox
                Layout.fillWidth: true
                // Height grows with text, up to 1/3 of window height
                height: Math.min(scanResultText.paintedHeight + spacing, mainWindow.height / 3)
                color: mainWindow.panelColor
                border.color: mainWindow.borderColor
                border.width: 2
                radius: 6
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.topMargin: verticalMargin

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
                    color: mainWindow.textColor
                    font.pointSize: 16
                }
            }

            Settings {
                id: themeToggleContainer
                Layout.alignment: Qt.AlignTop | Qt.AlignRight
                Layout.topMargin: verticalMargin
                textMargin: mainWindow.textMargin
                panelColor: mainWindow.panelColor
                textColor: mainWindow.textColor
                borderColor: mainWindow.borderColor
                accentColor: mainWindow.accentColor
                darkModeEnabled: mainWindow.darkModeEnabled
                onDarkModeEnabledChanged: mainWindow.darkModeEnabled = darkModeEnabled
            }

            // Image {
            //     id: menu
            //     width: 30
            //     height: width
            //     source: "images/download_button.svg"
            //     sourceSize.width: width
            //     sourceSize.height: width

            //     Layout.alignment: Qt.AlignRight | Qt.AlignTop
            //     Layout.topMargin: verticalMargin + scanResultBox.border.width
            //     MouseArea {
            //         anchors.fill: parent
            //         onClicked: {
            //             codeWriter.saveCodeToFile("yupiduu", picturesFolder + "qrlite_generated_code.png");
            //             statusText.text = "QR code saved to " + picturesFolder + "qrlite_generated_code.png";
            //         }
            //     }
            // }
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
                visible: permissionChecker && permissionChecker.cameraCheckPending
                textColor: mainWindow.secondaryTextColor
            }

            PermissionDenied {
                id: permissionDenied
                anchors.fill: parent
                visible: permissionChecker && permissionChecker.cameraPermissionGranted === false && !permissionChecker.cameraCheckPending
                backgroundColor: mainWindow.panelColor
                textColor: "#ff7b72"
            }

            Item {
                id: cameraContainer
                anchors.fill: parent
                visible: permissionChecker && permissionChecker.cameraPermissionGranted && !permissionChecker.cameraCheckPending

                CaptureSession {
                    id: captureSession
                    camera: Camera {
                        id: camera
                        focusMode: Camera.FocusModeAutoNear
                    }

                    videoOutput: preview

                    Component.onCompleted: {
                        if (permissionChecker.cameraPermissionGranted) {
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
        Rectangle {
            id: statusBar
            width: parent.width
            height: 24
            color: mainWindow.statusBarColor
            anchors.bottom: parent.bottom
            anchors.bottomMargin: visible ? 0 : -height
            visible: statusText.text !== ""

            Behavior on anchors.bottomMargin {
                NumberAnimation {
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
            }

            Text {
                id: statusText
                text: ""
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                color: mainWindow.textColor
                font.pointSize: 8

                onTextChanged: function (text) {
                    if (text !== "") {
                        hideTimer.restart();
                    }
                }
            }

            Timer {
                id: hideTimer
                interval: 3000
                running: false
                repeat: false
                onTriggered: {
                    statusText.text = "";
                }
            }
        }
    }
}
