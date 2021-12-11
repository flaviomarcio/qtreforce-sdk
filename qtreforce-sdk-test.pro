CONFIG += testcase
CONFIG += console
CONFIG -= debug_and_release
CONFIG += c++17
CONFIG += silent

TARGET = QtReforceSDK_1_Test
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

include($$PWD/qtreforce-sdk-test.pri)

QT -= widgets
QT -= qml qmldebug

LIBS += -L/usr/local/lib -lgmock
LIBS += -L/usr/local/lib -lgtest

SOURCES += $$PWD/test/main.cpp
