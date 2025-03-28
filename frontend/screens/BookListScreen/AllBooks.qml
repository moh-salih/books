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



        RowLayout{
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            visible: true
            Button{
                text: "Update"
                icon.source: "../../../images/update_icon_1.png"
                icon.color: "transparent"
                onClicked: bookListModel.updateDatabase(androidHelper.getAllPdfs())
                font.pointSize: 10
                background: Rectangle{
                    color: "transparent"
                    border.width: 1
                    border.color: rootId.actionButtonBorderColor
                }
            }

            Button{
                text: "Clear all"
                icon.source: "../../../images/delete_icon_1.png"
                icon.color: "transparent"
                onClicked: bookListModel.clearDatabase()
                font.pointSize: 10
                background: Rectangle{
                    color: "transparent"
                    border.width: 1
                    border.color: rootId.actionButtonBorderColor
                }
            }

            Button{
                text: "Authorize"
                icon.source: "../../../images/permission_icon_1.png"
                icon.color: "transparent"
                onClicked: androidHelper.requestStoragePermission()
                font.pointSize: 10
                background: Rectangle{
                    color: "transparent"
                    border.width: 1
                    border.color: rootId.actionButtonBorderColor

                }
                enabled: !androidHelper.isStoragePermissionGranted();
            }
        }

        GridView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            cellWidth: width / 3  // Each book takes half the width
            cellHeight: cellWidth * 1.4      // Adjust height as needed
            model: bookListModel
            clip: true
            cacheBuffer: 2000



            delegate: BookItem {
                width: GridView.view.cellWidth
                height: GridView.view.cellHeight
                book: model

                MouseArea{
                    anchors.fill: parent

                    property bool singleClickPending: false;

                    onClicked: {
                        singleClickPending = true;
                        clickTimerId.restart();
                    }

                    onDoubleClicked: {
                        singleClickPending = false;
                        clickTimerId.stop();
                        bookListModel.toggleFavorite(book.index);
                    }
                    onPressAndHold: actionMenu.openActionMenu(book);

                    Timer{
                        id: clickTimerId
                        interval: 200
                        onTriggered: {
                            if(parent.singleClickPending){
                                rootId.viewBook(book);
                                parent.singleClickPending = false;
                            }
                        }
                    }
                }

            }

            Menu{
                id: actionMenu
                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

                property var book;

                function openActionMenu(book){
                    if(!book) return;
                    actionMenu.book = book;
                    actionMenu.open();
                }

                MenuItem{
                    text: actionMenu.book?.isFavorite ?  "Unfavorite" : "Favorite";
                    onTriggered: bookListModel.toggleFavorite(actionMenu.book.index);

                }

                MenuItem{
                    text: "Remove"
                    onTriggered:  bookListModel.removeBook(actionMenu.book.index);
                }

                MenuItem{
                    text: "Delete"
                    contentItem: Text{
                        color: "red"
                        text: parent.text
                    }
                    onTriggered:  bookListModel.deleteBook(actionMenu.book.index);
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
                text = `Total books found: ${bookListModel.rowCount}`;
            }
        }

    }



    Connections{
        target: bookListModel
        function onRowCountChanged(){
            totalBookCountId.updateCount()
        }
    }

    Component.onCompleted: {
        bookListModel.refreshBooks();
        totalBookCountId.updateCount();
    }
}
