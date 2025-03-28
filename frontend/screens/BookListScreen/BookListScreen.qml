import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: rootId
    signal viewBook(var book);
    signal showBooks(int categoryId);

    FontLoader{
        id: fontLoaderId
        source: "../../../fonts/Boldonse/Boldonse-Regular.ttf"
    }

    ColumnLayout{
        anchors.fill: parent

        Image {
            id: logoImage
            source: "../../../images/trans_full_me.png"
            fillMode: Image.PreserveAspectFit
            Layout.fillWidth: true
            Layout.preferredHeight: 150
        }
        TabBar {
            id: bar
            Layout.fillWidth: true

            TabButton {
                text: qsTr("Categories")
                font.family: fontLoaderId.name
                font.bold: Font.Bold
                font.pixelSize: 10

                contentItem: Text{
                    font: parent.font
                    text: parent.text
                    color: parent.checked ? "white" : "red"
                    horizontalAlignment: Qt.AlignHCenter
                }

                background: Rectangle{
                    color:  parent.checked ? "red" : "white"
                    radius: 5
                    border.width: 0
                }
            }

            TabButton {
                text: qsTr("All")

                font.family: fontLoaderId.name
                font.bold: Font.Bold
                font.pixelSize: 10

                contentItem: Text{
                    font: parent.font
                    text: parent.text
                    color: parent.checked ? "white" : "red"
                    horizontalAlignment: Qt.AlignHCenter
                }

                background: Rectangle{
                    color:  parent.checked ? "red" : "white"
                    radius: 5
                    border.width: 0
                }
            }

            TabButton {
                text: qsTr("Favorite")

                font.family: fontLoaderId.name
                font.bold: Font.Bold
                font.pixelSize: 10
                onClicked: favoriteBookListModel.refreshBooks();

                contentItem: Text{
                    font: parent.font
                    text: parent.text
                    color: parent.checked ? "white" : "red"
                    horizontalAlignment: Qt.AlignHCenter
                }

                background: Rectangle{
                    color:  parent.checked ? "red" : "white"
                    radius: 5
                    border.width: 0
                }

            }
        }

        StackLayout {
            Layout.fillWidth: true
            currentIndex: bar.currentIndex

            BookCategories{
                id: bookCategories
                onShowBooks: function(categoryId){
                    rootId.showBooks(categoryId);
                }
            }

            AllBooks {
                id: allTab
                onViewBook: function(book){
                    rootId.viewBook(book);
                }
            }

            FavoriteBooks{
                id: favoriteTab
                onViewBook: function(book){
                    rootId.viewBook(book);
                }
            }
        }
    }

    Component.onCompleted: {


    }
}
