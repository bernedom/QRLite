import QtQuick

Rectangle {
    id: permissionCheck
    width: parent.width
    height: parent.height
    color: "black"

    Text {
        id: permissionText
        text: "Camera permissions denied. Please enable camera permissions in system settings."
        color: "red"
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
        width: parent.width * 0.8
    }
}
