import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: rootId

    property color actionButtonBorderColor: "wheat"
    signal viewBook(var book);


    ColumnLayout{
        anchors.fill: parent
        spacing: 3


        GridView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            cellWidth: width / 3  // Each book takes half the width
            cellHeight: cellWidth * 1.4      // Adjust height as needed
            model: favoriteBookListModel
            clip: true
            cacheBuffer: 2000

            delegate: BookItem {
                width: GridView.view.cellWidth
                height: GridView.view.cellHeight
                book: model

                MouseArea{
                    anchors.fill: parent
                    onClicked: viewBook(book)
                    onPressAndHold: actionMenu.openActionMenu(book);
                }
            }



            Menu{
                id: actionMenu

                property var book;

                function openActionMenu(book){
                    if(!book) return;
                    actionMenu.book = book;
                    actionMenu.open();
                }

                MenuItem{
                    text: "Unfavorite"
                    onTriggered:  favoriteBookListModel.removeBook(actionMenu.book.index);
                }
                MenuItem{
                    text: "Delete"
                    contentItem: Text{
                        color: "red"
                        text: parent.text
                    }
                    onTriggered:  favoriteBookListModel.deleteBook(actionMenu.book.index);
                }
                MenuItem{
                    text: "Share"
                }
            }
        }


        Text{
            id: totalBookCountId
            Layout.fillWidth: true
            padding: 5
            font.pointSize: 9
            color: "gray"
            horizontalAlignment: Qt.AlignHCenter


            function updateCount(){
                text = `Total books found: ${favoriteBookListModel.rowCount}`;
            }
        }

    }




    Connections{
        target: favoriteBookListModel
        function onRowCountChanged(){
            totalBookCountId.updateCount()
        }
    }


    Component.onCompleted: {
        favoriteBookListModel.refreshBooks();
        totalBookCountId.updateCount();
    }
}
