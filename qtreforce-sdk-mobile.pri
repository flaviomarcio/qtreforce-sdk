#INCLUDEPATH+=$$PWD
#INCLUDEPATH+=$$PWD/src

INCLUDEPATH+=$$PWD/src/includes/mobile

QTREFORCE_GIT_VERSION=$$system(git describe --always --abbrev=0)
DEFINES+=QTREFORCE_GIT_VERSION

#message('QtReforce: git revision==' $$QTREFORCE_GIT_VERSION)

QTREFORCE_NO_QSTM{
CONFIG+=QTREFORCE_NO_QRPC
CONFIG+=QTREFORCE_NO_QAPR
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QRPC')
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QAPR')
}

!CONFIG(QTREFORCE_NO_QNOTATION){
include($$PWD/src/3rdparty/qnotation/qnotation.pri)
HEADERS+= $$PWD/src/includes/mobile/QtReforce/QNotation
}
#!CONFIG(QTREFORCE_NO_QJSONWEBTOKEN){
#include($$PWD/src/3rdparty/qjsonwebtoken/qjsonwebtoken.pri)
#}
!CONFIG(QTREFORCE_NO_QCROSSCACHE){
include($$PWD/src/3rdparty/qcrosscache/qcrosscache.pri)
HEADERS+= $$PWD/src/includes/mobile/QtReforce/QCrossCache
}
!CONFIG(QTREFORCE_NO_QSTM){
include($$PWD/src/3rdparty/qstm/qstm.pri)
HEADERS+= $$PWD/src/includes/mobile/QtReforce/QStm
}
!CONFIG(QTREFORCE_NO_QRPC){
include($$PWD/src/3rdparty/qrpc/qrpc-mobile.pri)
HEADERS+= $$PWD/src/includes/mobile/QtReforce/QRpc
}
!CONFIG(QTREFORCE_NO_QAPR){
include($$PWD/src/3rdparty/qapr/qapr-mobile.pri)
HEADERS+= $$PWD/src/includes/mobile/QtReforce/QApr
}

!CONFIG(QTREFORCE_NO_QSTATUSBAR){
include($$PWD/src/3rdparty/qstatusbar/qstatusbar.pri)
HEADERS+= $$PWD/src/includes/mobile/QtReforce/QStatusBar
}

!CONFIG(QTREFORCE_NO_QTINYAES){
include($$PWD/src/3rdparty/qtinyaes/qtinyaes.pri)
HEADERS+= $$PWD/src/includes/mobile/QtReforce/QtInyAES
}

!CONFIG(QTREFORCE_NO_QMETAUI){
include($$PWD/src/3rdparty/qmetaui/src/v1/qmetaui.pri)
HEADERS+= $$PWD/src/includes/mobile/QtReforce/QMetaUi
}

INCLUDEPATH += $$PWD/src

DISTFILES += \
    $$PWD/src/includes/mobile/QtReforce/QNotation



