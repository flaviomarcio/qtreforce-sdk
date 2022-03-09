QTREFORCE_NO_QSTM{
CONFIG+=QTREFORCE_NO_QRPC
CONFIG+=QTREFORCE_NO_QORM
CONFIG+=QTREFORCE_NO_QAPR
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QRPC')
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QORM')
message('QtReforce: QTREFORCE_NO_QAPR auto declare : QTREFORCE_NO_QAPR')
}


!CONFIG(QTREFORCE_NO_QJSONWEBTOKEN){
include($$PWD/src/3rdparty/qjsonwebtoken/qjsonwebtoken.pri)
}
!CONFIG(QTREFORCE_NO_QTOKENUTIL){
include($$PWD/src/3rdparty/qtokenutil/qtokenutil.pri)
}
!CONFIG(QTREFORCE_NO_QCROSSCACHE){
include($$PWD/src/3rdparty/qcrosscache/qcrosscache.pri)
HEADERS+= $$PWD/src/test/QtReforce/QCrossCache
}
!CONFIG(QTREFORCE_NO_QSTM){
include($$PWD/src/3rdparty/qstm/test/qstm-test.pri)
HEADERS+= $$PWD/src/test/QtReforce/QStm
}
!CONFIG(QTREFORCE_NO_QORM){
include($$PWD/src/3rdparty/qorm/test/qorm-test.pri)
HEADERS+= $$PWD/src/test/QtReforce/QOrm
}
!CONFIG(QTREFORCE_NO_QRPC){
include($$PWD/src/3rdparty/qrpc/test/qrpc-test.pri)
HEADERS+= $$PWD/src/test/QtReforce/QRpc
}
!CONFIG(QTREFORCE_NO_QAPR){
include($$PWD/src/3rdparty/qapr/test/qapr-test.pri)
HEADERS+= $$PWD/src/test/QtReforce/QApr
}
!CONFIG(QTREFORCE_NO_QAPIDOC){
include($$PWD/src/3rdparty/qapidoc/test/qapidoc-test.pri)
HEADERS+= $$PWD/src/test/QtReforce/QApiDoc
}

INCLUDEPATH += $$PWD/src/test
