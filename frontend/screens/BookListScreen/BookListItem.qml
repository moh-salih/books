// BookItem.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: bookItem
    width: ListView.view ? ListView.view.width : parent.width
    height: 60
    color: "lightgray"
    border.color: "gray"
    radius: 5

    // Properties for the book title and author
    property string title: ""
    property string author: ""

    // Signal emitted when the user presses and holds the item
    signal pressAndHold()

    // Display the book title
    Text {
        id: titleText
        text: title
        font.bold: true
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
    }

    // Display the book author
    Text {
        id: authorText
        text: author
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
    }

    // MouseArea to handle press-and-hold gesture
    MouseArea {
        anchors.fill: parent
        onPressAndHold: {
            bookItem.pressAndHold() // Emit the pressAndHold signal
        }
    }
}
