import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts


Item {
    required property int categoryId;

    Rectangle{
        anchors.fill: parent

        ColumnLayout{
            anchors.fill: parent
            anchors.margins: 10
            Text {
                visible: false
                id: categoryTitle
                text: categoryId
            }
            BookList{
                model: bookListModel
                numOfColumns: 4
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }


    Component.onCompleted: {

    }
}
