import QtQuick 2.15
import QtQuick.Pdf

Item {
    id: pdfScreenRootId
    property alias pdfSource: docId.source
    anchors.fill: parent
    Rectangle{
        anchors.fill: parent
        color: "green"
    }

    PdfMultiPageView{
        anchors.fill: parent
        document: PdfDocument{
            id: docId
        }
    }
}
