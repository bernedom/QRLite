import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: "SimpleCollage"

    property var game
    

    Item {
        id: root
        focus: true
        anchors.fill: parent

        signal startGame()

        Keys.onPressed: event => {
            if (event.key === Qt.Key_Escape) {
                Qt.quit();
            }
        }
    }
}
