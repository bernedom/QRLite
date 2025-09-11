import QtQuick 
import QtQuick.Window 
import QtMultimedia 
import QtQuick.Controls

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: "QRLite"

    property var currentImagePath : ":/images/images/test.png"

    function toggleImage() {
        if (currentImagePath === ":/images/images/test.png") {
            currentImagePath = ":/images/images/valid_qr_code_qrlite.png";
        } else {
            currentImagePath = ":/images/images/test.png";
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
            width: 300
            height: 300
            color: "white"
            anchors.centerIn: parent
            id: qrImage

            CaptureSession {
                id: captureSession
                camera: Camera {
                    id: camera
                }
               
                videoOutput: preview

                Component.onCompleted: {
                    camera.start()
                }
            }

            VideoOutput {
                id: preview
                visible: true
                anchors.fill: parent
                //        autoOrientation: true
            }


            // Image {
            //     source: "qrc" + currentImagePath
            //     anchors.fill: parent
            //     fillMode: Image.PreserveAspectFit
            // }
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
                    scanResultText.text = scanner.scan(currentImagePath);
                    toggleImage();
                }
            }
        }
    }
}
