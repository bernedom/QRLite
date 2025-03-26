import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: "SimpleCollage"

    Item {
        id: root
        focus: true
        anchors.fill: parent

        Image {
            id: image
            source: "image://collage/collage"
            anchors.centerIn: parent
            width: 200
            height: 400
        }
        
        // Rectangle {
        //     id: generate
        //     width: 200
        //     height: 200
        //     color: "blue"
        //     anchors.centerIn: parent

        //     Text {
        //         id: name
        //         text: qsTr("generate collage")
        //     }

        //     MouseArea {
        //         anchors.fill: parent
        //         onClicked: {
        //             console.log("generate collage")
        //         }
        //     }
        // }
        

        Keys.onPressed: event => {
            if (event.key === Qt.Key_Escape) {
                Qt.quit();
            }
        }
    }
}
