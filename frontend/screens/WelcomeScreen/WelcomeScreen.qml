import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Item {
    Rectangle{
        color: "white"
        anchors.fill: parent

        ColumnLayout{
            anchors.fill: parent
            Text{
                Layout.fillWidth: true
                text: `All Books: ${bookListModel.rowCount}`
            }
            Text{
                Layout.fillWidth: true
                text: `Favorite Books: ${favoriteBookListModel.rowCount}`
            }

            ListView{
                id: allBooksListId
                Layout.fillWidth: true
                Layout.preferredHeight: 400
                clip: true
                model: bookListModel
                delegate: Item {
                    width: ListView.view.width
                    height: 50
                    Rectangle{
                        anchors.fill: parent
                        border.width: 1
                        border.color: "#eee"
                        color: "transparent"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: bookListModel.toggleFavorite(model.index)
                        }

                        RowLayout{
                            anchors.fill: parent
                            Text{
                                Layout.fillWidth: true
                                text: `${model.id}. ${model.title}`
                                font.weight: Font.Bold
                            }


                            Button{
                                Layout.fillHeight: true
                                Layout.minimumWidth: 50
                                text: ""
                                icon.source: model.isFavorite ? "../../../images/heart_icon.png" : "../../../images/unheart_icon.png"
                                icon.color: "transparent"
                                onClicked: {}
                                font.pointSize: 10
                                background: Rectangle{
                                    color: "transparent"
                                    // border.color: rootId.actionButtonBorderColor
                                }
                            }
                        }
                    }
                }
            }


            ListView{
                id: favoriteBooksListId
                Layout.fillWidth: true
                Layout.preferredHeight: 400
                clip: true
                model: favoriteBookListModel
                delegate: Item {
                    width: ListView.view.width
                    height: 50
                    Rectangle{
                        anchors.fill: parent
                        border.width: 1
                        border.color: "#eeffee"
                        color: "transparent"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: favoriteBookListModel.toggleFavorite(model.index)
                        }

                        RowLayout{
                            anchors.fill: parent
                            Text{
                                Layout.fillWidth: true
                                text: `${model.id}. ${model.title}`
                            }


                            Button{
                                Layout.fillHeight: true
                                Layout.minimumWidth: 50
                                text: ""
                                icon.source: model.isFavorite ? "../../../images/heart_icon.png" : "../../../images/unheart_icon.png"
                                icon.color: "transparent"
                                onClicked: {}
                                font.pointSize: 10
                                background: Rectangle{
                                    color: "transparent"
                                }
                            }
                        }
                    }
                }
            }

            Rectangle{
                color: "transparent"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }

    Component.onCompleted: {
        bookListModel.refreshBooks();
        favoriteBookListModel.refreshBooks();
    }
}
