CONFIG += console
CONFIG -= debug_and_release
CONFIG += c++17
CONFIG += silent

TARGET = QRpc
TEMPLATE = lib

include($$PWD/qtreforce-sdk.pri)

QT -= widgets
QT -= qml qmldebug

