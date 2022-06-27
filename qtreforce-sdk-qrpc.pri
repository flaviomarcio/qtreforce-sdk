INCLUDEPATH+=$$PWD/src/includes/desktop

QTREFORCE_GIT_VERSION=$$system(git describe --always --abbrev=0)
DEFINES+=QTREFORCE_GIT_VERSION

#message('QtReforce: git revision==' $$QTREFORCE_GIT_VERSION)

QTREFORCE_NO_QSTM{
CONFIG+=QTREFORCE_NO_QRPC
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QRPC')
}

!CONFIG(QTREFORCE_NO_QNOTATION){
include($$PWD/src/3rdparty/qnotation/qnotation.pri)
HEADERS+= $$PWD/src/includes/desktop/QtReforce/QNotation
}
!CONFIG(QTREFORCE_NO_QSTM){
include($$PWD/src/3rdparty/qstm/qstm.pri)
HEADERS+= $$PWD/src/includes/desktop/QtReforce/QStm
}
!CONFIG(QTREFORCE_NO_QRPC){
include($$PWD/src/3rdparty/qrpc/qrpc.pri)
HEADERS+= $$PWD/src/includes/desktop/QtReforce/QRpc
}


