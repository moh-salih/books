import QtQuick 2.15
import QtQuick.Pdf

Item {
    id: pdfScreenRootId
    property alias pdfSource: docId.source


    PdfViewer{
        id: pdfViewer
        anchors.fill: parent
        document: PdfDocument{
            id: docId
        }


        onRenderScaleChanged: function(value){
            console.log(`Your render scale is ${renderScale}`)
        }

        Component.onCompleted: {
            pdfViewer.scaleToWidth(pdfViewer.width, pdfViewer.height)
        }
    }

    Component.onCompleted: {
        console.log("Reading book: ", docId.source)
    }
}
