CONFIG += console
CONFIG -= debug_and_release
CONFIG += c++17
CONFIG += silent

TARGET = QtReforceSDK
TEMPLATE = lib

INCLUDEPATH += $PWD/src

include($$PWD/qtreforce-sdk.pri)

QT -= widgets
QT -= qml qmldebug

