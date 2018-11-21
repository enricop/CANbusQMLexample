import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import CANbusExample 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 640
    title: qsTr("CANbusQMLExample")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Connect")
            Action {
                text: qsTr("&SocketCAN")
                //icon.name: "edit-copy"
                onTriggered: channel.connectDevice()
            }
        }
        Menu {
            title: qsTr("&Disconnect")
        }
    }

    header: GroupBox {
        title: "Send CAN frame"
        GridLayout{
            columns: 3
            Label {
                text: "Frame ID (hex)"
            }
            Label {
                text: "Payload (hex)"
            }
            Label {

            }
            TextField {
                id: frameid
                placeholderText: "123"
                //validator:
            }
            TextField {
                id: framepayload
                placeholderText: "12 15 AA EE"
                //validator:
            }
            Button {
                text: "Send"
                onClicked: channel.sendFrame(frameid.text, framepayload.text)
            }
        }
    }

    ScrollView {
        anchors.fill: parent

        ListView {
            id: mainlist
            //focus: true
            //clip: true

            property var columnWidths: ({"timestamp": 100, "flags": 50})

            model: FrameListModel {
                id: canmodel
                list: framelist
            }

            header: Row {
                id: banner
                //width: parent.width
                //height: 50
                //gradient: clubcolors
                //border {color: "#9EDDF2"; width: 2}
                padding: 15
                Label {
                    text: "Timestamp"
                    //font.pixelSize: 20
                    width: mainlist.columnWidths.timestamp
                }
                Label {
                    //anchors.centerIn: parent
                    text: "Flags"
                    //font.pixelSize: 20
                    width: mainlist.columnWidths.flags
                }
                Label {
                    //anchors.centerIn: parent
                    text: "Data"
                    //font.pixelSize: 20
                    //width: 40
                }
            }

            delegate: ItemDelegate {
                contentItem: RowLayout {
                    Label {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: implicitHeight
                        Layout.preferredWidth: mainlist.columnWidths.timestamp
                        text: timestamp
                    }
                    Label {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: implicitHeight
                        Layout.preferredWidth: mainlist.columnWidths.flags
                        text: flags
                    }
                    Label {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: implicitHeight
                        text: message
                    }
                }

                //text: "Item " + index + " " + timestamp + " " + processname + " " + message
                //onClicked: console.log("clicked:", modelData)

                width: parent.width
                font.pixelSize: 14

                //anchors.left: parent.left
                //anchors.leftMargin: 2
            }
        }
    }

    footer: GroupBox {
        title: "Info Messages"
        Label {
            text: channel.connectioninfo
        }
    }
}
