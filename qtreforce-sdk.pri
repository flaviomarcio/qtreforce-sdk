#INCLUDEPATH+=$$PWD
#INCLUDEPATH+=$$PWD/src

include($$PWD/src/3rdparty/qjsonwebtoken/qjsonwebtoken.pri)
include($$PWD/src/3rdparty/qtokenutil/qtokenutil.pri)
include($$PWD/src/3rdparty/qstm/qstm.pri)
include($$PWD/src/3rdparty/qorm/qorm.pri)
include($$PWD/src/3rdparty/qrpc/qrpc.pri)
include($$PWD/src/3rdparty/qapr/qapr.pri)
include($$PWD/src/3rdparty/qcrosscache/qcrosscache.pri)


HEADERS+= \
    $$PWD/src/QtReforce/QtReforceInclude \
    $$PWD/src/QtReforce/QJsonWebToken \
    $$PWD/src/QtReforce/QStm \
    $$PWD/src/QtReforce/QOrm \
    $$PWD/src/QtReforce/QRpc \
    $$PWD/src/QtReforce/QApr \
    $$PWD/src/QtReforce/QCrossCache \
