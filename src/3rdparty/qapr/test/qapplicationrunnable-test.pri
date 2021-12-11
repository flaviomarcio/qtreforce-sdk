include($$PWD/../qapplicationrunnable.pri)

INCLUDEPATH+=$$PWD

CONFIG += console
CONFIG -= debug_and_release
CONFIG += testcase
LIBS += -L/usr/local/lib -lgmock
LIBS += -L/usr/local/lib -lgtest

Q_APR_RUNNABLE_TEST=true
QMAKE_CXXFLAGS += -DQ_APR_RUNNABLE_TEST=\\\"$$Q_APR_RUNNABLE_TEST\\\"

HEADERS += \
    $$PWD/qapr_test.h \
    $$PWD/qapr_test_unit.h

SOURCES += \
    $$PWD/qapr_test_unit_variant_util.cpp


