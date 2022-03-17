#INCLUDEPATH+=$$PWD
#INCLUDEPATH+=$$PWD/src

QTREFORCE_GIT_VERSION=$$system(git describe --always --abbrev=0)
DEFINES+=QTREFORCE_GIT_VERSION

#message('QtReforce: git revision==' $$QTREFORCE_GIT_VERSION)

QTREFORCE_NO_QSTM{
CONFIG+=QTREFORCE_NO_QRPC
CONFIG+=QTREFORCE_NO_QORM
CONFIG+=QTREFORCE_NO_QAPR
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QRPC')
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QORM')
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QORM')
}

!CONFIG(QTREFORCE_NO_QNOTATION){
include($$PWD/src/3rdparty/qnotation/qnotation.pri)
HEADERS+= $$PWD/src/QtReforce/QNotation
}
!CONFIG(QTREFORCE_NO_QJSONWEBTOKEN){
include($$PWD/src/3rdparty/qjsonwebtoken/qjsonwebtoken.pri)
}
!CONFIG(QTREFORCE_NO_QTOKENUTIL){
include($$PWD/src/3rdparty/qtokenutil/qtokenutil.pri)
}
!CONFIG(QTREFORCE_NO_QCROSSCACHE){
include($$PWD/src/3rdparty/qcrosscache/qcrosscache.pri)
HEADERS+= $$PWD/src/QtReforce/QCrossCache
}
!CONFIG(QTREFORCE_NO_QSTM){
include($$PWD/src/3rdparty/qstm/qstm.pri)
HEADERS+= $$PWD/src/QtReforce/QStm
}
!CONFIG(QTREFORCE_NO_QORM){
include($$PWD/src/3rdparty/qorm/qorm.pri)
HEADERS+= $$PWD/src/QtReforce/QOrm
}
!CONFIG(QTREFORCE_NO_QRPC){
include($$PWD/src/3rdparty/qrpc/qrpc.pri)
HEADERS+= $$PWD/src/QtReforce/QRpc
}
!CONFIG(QTREFORCE_NO_QAPR){
include($$PWD/src/3rdparty/qapr/qapr.pri)
HEADERS+= $$PWD/src/QtReforce/QApr
}
!CONFIG(QTREFORCE_NO_QAPIDOC){
include($$PWD/src/3rdparty/qapidoc/qapidoc.pri)
HEADERS+= $$PWD/src/QtReforce/QApiDoc
}

INCLUDEPATH += $$PWD/src

DISTFILES += \
    $$PWD/src/QtReforce/QNotation



