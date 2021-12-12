INCLUDEPATH+=$$PWD
INCLUDEPATH+=$$PWD/src
include($$PWD/src/3rdparty/qjsonwebtoken/qjsonwebtoken.pri)
include($$PWD/src/3rdparty/qtokenutil/qtokenutil.pri)
include($$PWD/src/3rdparty/qstm/qstm.pri)
include($$PWD/src/3rdparty/qrpc/qrpc.pri)
include($$PWD/src/3rdparty/qorm/qorm.pri)
include($$PWD/src/3rdparty/qapr/qapr.pri)


HEADERS+= \
    $$PWD/src/QtReforceInclude
