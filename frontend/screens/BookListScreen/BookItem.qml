
import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Item{
    id: rootId
    property var book

    readonly property string favoriteIcon: "../../../images/heart_icon.png";
    readonly property string unfavoriteIcon: "../../../images/unheart_icon.png";
    property int bookTilePadding: 5
    property int bookTileMargins: 3
    property int bookTileSpacingInBetween: 0
    property bool isSelected: false;

    clip: true

    FontLoader{
        id: fontLoaderId
        source: "../../../fonts/comic-khazi-font/ComicKhazi-X05j.ttf"
    }
    FontLoader{
        id: heartIconLoaderId
        source: "../../../icons/fontello-07c00b8d/font/fontello.ttf"
    }



    function extractName(fileName) {
      // Remove the extension (if any)
      let name = fileName.replace(/\.[^/.]+$/, "");

      // Remove any hyphens
      name = name.replace(/-|_/g, " ");

      return name;
    }

    Rectangle{
        id: bookIconId
        anchors.fill: parent
        color: "white"
        radius: 5
        border.width: rootId.book.isSelected ? 2 : 0
        border.color: rootId.book.isSelected ? "greenyellow" : "#eee"

        // border.color: book.isFavorite ? "greenyellow" : "#eee"
        anchors.margins: rootId.bookTileMargins


        ColumnLayout{
            anchors.fill: parent
            anchors.margins: rootId.bookTilePadding
            spacing: rootId.bookTileSpacingInBetween

            Rectangle{
                color: "transparent"
                Layout.fillWidth: true
                Layout.preferredHeight: bookIconId.height * 0.10
                clip: true

                RowLayout{
                    anchors.fill: parent

                    Rectangle{
                        Layout.fillWidth: true
                    }

                    Image{
                        Layout.fillHeight: true
                        Layout.preferredWidth: bookIconId.height * 0.10
                        source: book.isFavorite ? rootId.favoriteIcon : rootId.unfavoriteIcon
                        opacity: book.isFavorite ? 0.95 : 0.1
                    }
                }
            }

            Rectangle{
                color: "transparent"
                Layout.fillWidth: true
                Layout.preferredHeight: bookIconId.height * 0.50
                clip: true


                Image {
                    width: parent.width
                    height: parent.height
                    source: "../../../images/books_icon2.png"
                    // source: book.coverImagePath ? book.coverImagePath : "images/books_icon2.png"
                    fillMode: Image.PreserveAspectFit
                    opacity: 0.8
                }
            }

            Rectangle{
                Layout.fillHeight: false
                color: "transparent"
            }

            Rectangle{
                color: "transparent"
                Layout.fillWidth: true
                Layout.fillHeight: true
                // clip: true

                Text {
                    id: bookTitleId
                    anchors.fill: parent
                    anchors.centerIn: parent
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text: rootId.extractName(book.title).substring(0, 50)
                    font.pixelSize: 7
                    wrapMode: Text.WordWrap
                    font.family: fontLoaderId.name
                    opacity: 0.9
                    clip: true
                }
            }
        }

        ColumnLayout {
           anchors.fill: parent
           anchors.margins: 5
           spacing: 5
            visible: false
           RowLayout{
               Layout.fillWidth: true
               Layout.preferredHeight: 20

               Rectangle{
                   Layout.fillWidth: true
                   color: "transparent"
               }

               Image{
                   source: book.isFavorite ? rootId.favoriteIcon : rootId.unfavoriteIcon
                   fillMode: Image.PreserveAspectFit
                   Layout.preferredWidth: 20
                   Layout.fillHeight: true
                   opacity: 0.5
               }
           }

           Image {
               Layout.fillWidth: true
               Layout.preferredHeight: 50
               source: "../../../images/books_icon2.png"
               // source: book.coverImagePath ? book.coverImagePath : "images/books_icon2.png"
               fillMode: Image.PreserveAspectFit
           }

            RowLayout{
                Layout.fillWidth: true
                Layout.fillHeight: true
                anchors.bottomMargin: 10

                Text {
                    Layout.fillWidth: true
                    text: rootId.extractName(book.title).substring(0, 50)
                    font.pixelSize: 8
                    wrapMode: Text.WordWrap
                    font.family: fontLoaderId.name
                    opacity: 0.8
                }
            }
        }

    }
}
