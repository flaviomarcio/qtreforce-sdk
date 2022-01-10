include($$PWD/src/3rdparty/qjsonwebtoken/qjsonwebtoken.pri)
include($$PWD/src/3rdparty/qtokenutil/qtokenutil.pri)
include($$PWD/src/3rdparty/qcrosscache/qcrosscache.pri)
include($$PWD/src/3rdparty/qstm/test/qstm-test.pri)
include($$PWD/src/3rdparty/qrpc/test/qrpc-test.pri)
include($$PWD/src/3rdparty/qorm/test/qorm-test.pri)
include($$PWD/src/3rdparty/qapr/test/qapr-test.pri)

INCLUDEPATH += $$PWD/src/test

HEADERS+= \
    $$PWD/src/test/QtReforce/QApr \
    $$PWD/src/test/QtReforce/QStm \
    $$PWD/src/test/QtReforce/QOrm \
    $$PWD/src/test/QtReforce/QRpc \
    $$PWD/src/test/QtReforce/QCrossCache \
