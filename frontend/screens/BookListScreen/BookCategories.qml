import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: rootId
    signal showBooks(int categoryId);

    Rectangle{
        anchors.fill: parent

        ColumnLayout{
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            spacing: 10

            RowLayout{
                Layout.fillWidth: true
                spacing: 6

                TextField{
                    id: categTextFieldId
                    Layout.fillWidth: true
                    font.pointSize: 12
                    placeholderText: "Economy, AI, Politics, ..."
                }

                Button{
                    text: "Add"
                    background: Rectangle{
                        color: "#eee"
                        implicitHeight: categTextFieldId.implicitHeight
                        implicitWidth: categTextFieldId.implicitWidth / 2
                    }

                    onClicked: {
                        if(categTextFieldId.text.length < 3) return;
                        categoryListModel.addCategory(categTextFieldId.text, "");
                        categTextFieldId.clear();
                    }
                }
            }


            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: categoryListModel
                delegate: Item {
                    width: parent.width
                    height: 50

                    Rectangle{
                        anchors.fill: parent

                        ColumnLayout{
                            anchors.fill: parent
                            anchors.margins: 5

                            RowLayout {
                                Layout.fillWidth: true
                                Layout.fillHeight: true

                                Text {
                                    Layout.fillHeight: true
                                    text: 1 + model.index + "."
                                    font.pixelSize: 14
                                    color: "#aaa"
                                    font.bold: Font.Bold
                                }

                                Text {
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    text: model.name
                                }

                                Image { source: model.imagePath ; visible: false}

                            }

                            Rectangle{
                                Layout.fillWidth: true
                                color: "#eee"
                                Layout.preferredHeight: 1
                            }
                        }
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: rootId.showBooks(model.id);
                    }
                }
            }


            Rectangle{
                Layout.fillHeight: true
            }
        }
    }



    Component.onCompleted: categoryListModel.refreshCategories();
}
