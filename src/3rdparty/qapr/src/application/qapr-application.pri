QT += core
QT += network

INCLUDEPATH+=$$PWD

HEADERS += \
    $$PWD/private/p_qapr_circuit_breaker.h \
    $$PWD/private/p_qapr_application.h \
    $$PWD/private/p_qapr_log.h \
    $$PWD/private/p_qapr_log_telegram.h \
    $$PWD/private/p_qapr_log_elk.h \
    $$PWD/qapr_consts.h \
    $$PWD/qapr_global.h \
    $$PWD/qapr_log.h \
    $$PWD/qapr_circuit_breaker.h \
    $$PWD/qapr_runnable.h \
    $$PWD/qapr_mainservice.h \
    $$PWD/qapr_application.h \


SOURCES += \
    $$PWD/qapr_log.cpp \
    $$PWD/qapr_circuit_breaker.cpp \
    $$PWD/qapr_runnable.cpp \
    $$PWD/qapr_mainservice.cpp \
    $$PWD/qapr_application.cpp \
