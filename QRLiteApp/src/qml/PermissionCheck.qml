import QtQuick

Rectangle{
    id: permissionCheck
    width: parent.width
    height: parent.height
    color: "black"

    Text {
        id: permissionText
        text: "Checking camera permissions. Please grant the camera permission if prompted."
        color: "white"
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
        width: parent.width * 0.8
    }
}