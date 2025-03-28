import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "./frontend/screens/PdfScreen";
import "./frontend/screens/BookListScreen"
import "./frontend/screens/WelcomeScreen"

ApplicationWindow{
    id: root
    width: 620
    height: 1360
    x: 1480
    visible: true
    title: qsTr("Let's read!")

    StackView{
        id: appStack
        anchors.fill: parent
        anchors.margins: 5

        initialItem: BookListScreen{
            onViewBook: function(book){
                console.log(book.filePath, book.title)
                if(book && book.filePath){
                    appStack.push("frontend/screens/PdfScreen/PdfScreen.qml", {pdfSource:  `file:///${book.filePath}`});
                }
            }

            onShowBooks: function(categoryId){
                appStack.push("frontend/screens/BookListScreen/CategoryBooks.qml", {categoryId:  categoryId});
            }
        }


        focus: true

        Keys.onBackPressed: function(event){
            if(appStack.depth > 1){
                appStack.pop();
            }else{
                Qt.quit();
            }

            event.accepted = true;
        }
    }

}

