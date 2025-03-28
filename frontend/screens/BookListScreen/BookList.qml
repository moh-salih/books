import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: rootId

    // properties
    property int numOfColumns: 2;
    property int columnHeight: 120
    required property var model;


    property bool selectionMode: false;

    signal viewBook();
    signal select(int index);
    signal unselect(int index);

    ColumnLayout{
        anchors.fill: parent
        spacing: 5

        Text {
            text: `${rootId.model.selectedCount} books selected`;
            visible: `${rootId.model.selectedCount > 0}`;
            Layout.fillWidth: true
            padding: 7
            font.bold: Font.Bold
            font.pixelSize: 14
            color: "#ccc"
            opacity: 0.765
        }

        RowLayout{
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            visible: rootId.selectionMode

            Button{
                text: "Select All"
                onClicked: rootId.model.selectAll();
            }

            Button{
                text: "Deselect All"
                onClicked: rootId.model.deselectAll();
            }

            Button{
                text: "Cancel"
                onClicked: rootId.exitSelectionMode();
            }

        }

        GridView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            cellWidth: width / rootId.numOfColumns
            cellHeight: rootId.columnHeight
            clip: true
            cacheBuffer: 3000

            model: rootId.model
            delegate: BookItem{
                width: GridView.view.cellWidth
                height: GridView.view.cellHeight
                book: model
                isSelected: model.isSelected



                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        if(rootId.selectionMode){
                            book.isSelected ? rootId.model.deselect(book.index) : rootId.model.select(book.index);
                        }else{
                            // view book
                        }
                    }

                    onPressAndHold: {
                        rootId.enterSelectionMode();
                        rootId.model.select(model.index);
                    }
                }
            }
        }
    }



    // functions
    function enterSelectionMode(){
        rootId.selectionMode = true;
    }

    function exitSelectionMode(){
        rootId.selectionMode = false;
        rootId.model.deselectAll();
    }



    Component.onCompleted: rootId.model.refreshBooks();
}
