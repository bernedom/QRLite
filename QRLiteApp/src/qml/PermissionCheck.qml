import QtQuick

Rectangle {
    id: permissionCheck
    width: parent.width
    height: parent.height
    color: "transparent"

    Timer {
        id: showTimer
        interval: 50
        repeat: false
        running: true
        onTriggered: permissionText.visible = true
    }

    Text {
        id: permissionText
        visible: false
        text: "Checking camera permissions. Please grant the camera permission if prompted."
        color: "gray"
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
        width: parent.width * 0.8
    }
}
