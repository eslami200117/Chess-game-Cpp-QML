import QtQuick 2.15
import QtQuick.Window 2.15
import com.chess.controller 1.0
import QtQuick.Layouts 1.15
import "utils.js" as Utils

Window {
    width: 845
    height: 845
    visible: true
    title: qsTr("Chess Game")
    color: "white"


    Rectangle {
        id: endGame
        visible: false
        radius: 50

        Text {
            id: winer
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 30
        }
        onVisibleChanged: {
            winer.text = "Winer: " + GameController.getTurn()
        }

        height: 300
        width: 500
        color: "#8A9A5B"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: quit
        visible: endGame.visible
        property color clr: "#e9ac75"
        radius: 20
        anchors {
            top: endGame.bottom
            left: endGame.left
            right: endGame.horizontalCenter
            margins: 5
        }

        height: 80

        Text {
            text: qsTr("Quit")
            font.pointSize: 20
            anchors.centerIn: parent
        }

        color: if (mouseArea1.containsPress) {
                   return Qt.lighter(clr)
               } else if (mouseArea1.containsMouse) {
                   return Qt.darker(clr)
               } else {
                   return clr
               }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                Qt.quit()
            }
        }
    }

    Rectangle {
        id: plyagn
        visible: endGame.visible
        property color clr: "#e9ac75"
        radius: 20
        anchors {
            top: endGame.bottom
            right: endGame.right
            left: endGame.horizontalCenter
            margins: 5
        }

        height: 80

        Text {
            text: qsTr("Play again")
            font.pointSize: 20
            anchors.centerIn: parent
        }

        color: if (mouseArea2.containsPress) {
                   return Qt.lighter(clr)
               } else if (mouseArea2.containsMouse) {
                   return Qt.darker(clr)
               } else {
                   return clr
               }

        MouseArea {
            id: mouseArea2
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                GameController.loadGame()
                endGame.visible = GameController.isDone();
                Utils.refreshAll();
                board.visible = !endGame.visible;


            }
        }
    }

    GridLayout {
        id: board
        width: 800
        height: 800
        x: 5
        y: 5
        columns: 8
        rows: 8
        Repeater {
            id: boardRepeater
            property var moves: []
            property bool readyToSelect: false
            property int source
            model: 64

            onReset: {
                moves = [];
                readyToSelect = false;
            }

            signal reset();
            Rectangle {
                property int row: (index-(index%8))/8
                property int column: index%8
                property bool selected: false
                property color baseColor: (row + column)%2 === 0? "#e9ac75":"#854a15"
                property int piece: selected? GameController.getPieceChar(row, column):GameController.getPieceChar(row, column)
                width: 100
                height: 100
                color: if(selected){
                           return (row + column)%2 === 0? "#8A9A5B":"#454B1B";
                       } else {
                           return baseColor;
                       }

                Image {
                    id: pieceImage
                    source: Utils.getAddressImage(piece)
                    anchors.fill: parent
                }

                onUnSelect: {
                    selected = false
                }
                onSelect_: {
                    selected = true
                }

                signal unSelect()
                signal select_()

                MouseArea {
                    id: ma
                    anchors.fill: parent
                    onClicked: {
                        if(!Utils.isNextMove(boardRepeater.moves, index)){
                            Utils.unSelecteOthers()
                            selected = !selected
                            boardRepeater.source = index
                            Utils.selectAll(GameController.validMoves(row, column))
                        } else {
                            GameController.move(boardRepeater.source, index);
                            Utils.unSelecteOthers();
                            boardRepeater.reset();
                            endGame.visible = GameController.isDone();
                            board.visible = !endGame.visible;
                            GameController.nextTurn();
                        }
                    }
                }
            }
        }
    }
}
