CONFIG += console
CONFIG -= debug_and_release
CONFIG += testcase
LIBS += -L/usr/local/lib -lgmock
LIBS += -L/usr/local/lib -lgtest

Q_APR_TEST=true
QMAKE_CXXFLAGS += -DQ_APR_TEST=\\\"$$Q_APR_TEST\\\"

include($$PWD/test/qapr-test.pri)
