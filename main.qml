import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    property var rectSize: 10
    Component.onCompleted: {
        gameField.cellsChanged.connect(function() {
            cField.requestPaint();
        });
    }
    Button {
        id: bStart
        text: tTimer.running ? "Stop" : "Start"
        anchors {
            right: parent.right
        }
        onClicked: {
            tTimer.running = !tTimer.running;
        }
    }
    TextField {
        id: tfInterval
        selectByMouse: true
        anchors {
            right: parent.right
            top: bStart.bottom
        }
        text: "500"
        validator: IntValidator {
            bottom: 50
        }
    }

    Canvas {
        id: cField
        anchors.fill: parent
        onPaint: {
            let ctx = getContext("2d");
            ctx.fillStyle = Qt.rgba(1, 1, 1, 1);
            ctx.fillRect(0, 0, gameField.width * rectSize, gameField.height * rectSize);
            ctx.fillStyle = Qt.rgba(0, 0, 0, 1);
            for (let i = 0; i < gameField.height; ++i) {
                for (let j = 0; j < gameField.width; ++j) {
                    if (gameField.cells[i][j]) {
                        ctx.fillRect(i * rectSize, j * rectSize, rectSize, rectSize);
                    }
                }
            }
            //ctx.rect(0, 0, gameField.width * rectSize, gameField.height * rectSize);
        }
    }
    MouseArea {
        width: gameField.width * rectSize
        height: gameField.height * rectSize
        acceptedButtons: Qt.LeftButton
        onClicked: {
            let x = Math.floor(mouseX / rectSize);
            let y = Math.floor(mouseY / rectSize);
            gameField.set(x, y, !gameField.get(x, y));
        }
    }

    Timer {
        id: tTimer
        interval: tfInterval.text
        repeat: true
        onTriggered: {
            gameField.tick();
        }
    }
}
