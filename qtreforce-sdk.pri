INCLUDEPATH += $$PWD/src
exists($$PWD/src/includes/desktop){
INCLUDEPATH+=$$PWD/src/includes/desktop
}

CONFIG += silent

QTREFORCE_GIT_VERSION=$$system(git describe --always --abbrev=0)
DEFINES+=QTREFORCE_GIT_VERSION

QTREFORCE_NO_QSTM{
CONFIG+=QTREFORCE_NO_QRPC
CONFIG+=QTREFORCE_NO_QORM
CONFIG+=QTREFORCE_NO_QAPR
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QRPC')
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QORM')
message('QtReforce: QTREFORCE_NO_QSTM auto declare : QTREFORCE_NO_QAPR')
}


QTREFORCE_QANNOTATION_SOURCE=$$PWD/src/3rdparty/qnotation/qannotation.pri
QTREFORCE_QJSONWEBTOKEN_SOURCE=$$PWD/src/3rdparty/qjsonwebtoken/qjsonwebtoken.pri
QTREFORCE_QTOKENUTIL_SOURCE=$$PWD/src/3rdparty/qtokenutil/qtokenutil.pri
QTREFORCE_QCROSSCACHE_SOURCE=$$PWD/src/3rdparty/qcrosscache/qcrosscache.pri
QTREFORCE_QAPIDOC_SOURCE=$$PWD/src/3rdparty/qapidoc/qapidoc.pri
QTREFORCE_QSTM_SOURCE=$$PWD/src/3rdparty/qstm/qstm.pri
QTREFORCE_QORM_SOURCE=$$PWD/src/3rdparty/qorm/qorm.pri
QTREFORCE_QRPC_SOURCE=$$PWD/src/3rdparty/qrpc/qrpc.pri
QTREFORCE_QAPR_SOURCE=$$PWD/src/3rdparty/qapr/qapr.pri
QTREFORCE_QMFE_SOURCE=$$PWD/src/3rdparty/qmfe/qmfe-server.pri

exists($$QTREFORCE_QANNOTATION_SOURCE)    { QTREFORCE_QANNOTATION=true } else { QTREFORCE_QANNOTATION=false }
exists($$QTREFORCE_QJSONWEBTOKEN_SOURCE)  { QTREFORCE_QJSONWEBTOKEN=true } else { QTREFORCE_QJSONWEBTOKEN=false }
exists($$QTREFORCE_QTOKENUTIL_SOURCE)     { QTREFORCE_QTOKENUTIL=true } else { QTREFORCE_QTOKENUTIL=false }
exists($$QTREFORCE_QCROSSCACHE_SOURCE)    { QTREFORCE_QCROSSCACHE=true } else { QTREFORCE_QCROSSCACHE=false }
exists($$QTREFORCE_QAPIDOC_SOURCE)        { QTREFORCE_QAPIDOC=true } else { QTREFORCE_QAPIDOC=false }
exists($$QTREFORCE_QSTM_SOURCE)           { QTREFORCE_QSTM=true } else { QTREFORCE_QSTM=false }
exists($$QTREFORCE_QORM_SOURCE)           { QTREFORCE_QORM=true } else { QTREFORCE_QORM=false }
exists($$QTREFORCE_QRPC_SOURCE)           { QTREFORCE_QRPC=true } else { QTREFORCE_QRPC=false }
exists($$QTREFORCE_QAPR_SOURCE)           { QTREFORCE_QAPR=true } else { QTREFORCE_QAPR=false }
exists($$QTREFORCE_QMFE_SOURCE)           { QTREFORCE_QMFE=true } else { QTREFORCE_QMFE=false }


CONFIG(QTREFORCE_NO_QANNOTATION):      QTREFORCE_QANNOTATION=false
CONFIG(QTREFORCE_NO_QJSONWEBTOKEN):    QTREFORCE_QJSONWEBTOKEN=false
CONFIG(QTREFORCE_NO_QTOKENUTIL):       QTREFORCE_QTOKENUTIL=false
CONFIG(QTREFORCE_NO_QCROSSCACHE):      QTREFORCE_QCROSSCACHE=false
CONFIG(QTREFORCE_NO_QSTM):             QTREFORCE_QSTM=false
CONFIG(QTREFORCE_NO_QORM):             QTREFORCE_QORM=false
CONFIG(QTREFORCE_NO_QRPC):             QTREFORCE_QRPC=false
CONFIG(QTREFORCE_NO_QAPR):             QTREFORCE_QAPR=false
CONFIG(QTREFORCE_NO_QMFE):             QTREFORCE_QMFE=false

equals(QTREFORCE_QANNOTATION,true):     include($$QTREFORCE_QANNOTATION_SOURCE)
equals(QTREFORCE_QJSONWEBTOKEN,true):   include($$QTREFORCE_QJSONWEBTOKEN_SOURCE)
equals(QTREFORCE_QAPIDOC,true):         include($$QTREFORCE_QAPIDOC_SOURCE)
equals(QTREFORCE_QTOKENUTIL,true):      include($$QTREFORCE_QTOKENUTIL_SOURCE)
equals(QTREFORCE_QCROSSCACHE,true):     include($$QTREFORCE_QCROSSCACHE_SOURCE)
equals(QTREFORCE_QSTM,true):            include($$QTREFORCE_QSTM_SOURCE)
equals(QTREFORCE_QORM,true):            include($$QTREFORCE_QORM_SOURCE)
equals(QTREFORCE_QRPC,true):            include($$QTREFORCE_QRPC_SOURCE)
equals(QTREFORCE_QAPR,true):            include($$QTREFORCE_QAPR_SOURCE)
equals(QTREFORCE_QMFE,true):            include($$QTREFORCE_QMFE_SOURCE)


equals(QTREFORCE_QANNOTATION,true):     HEADERS+= $$PWD/src/includes/desktop/QtReforce/QAnnotation
equals(QTREFORCE_QCROSSCACHE,true):     HEADERS+= $$PWD/src/includes/desktop/QtReforce/QCrossCache
equals(QTREFORCE_QAPIDOC,true):         HEADERS+= $$PWD/src/includes/desktop/QtReforce/QApiDoc
equals(QTREFORCE_QSTM,true):            HEADERS+= $$PWD/src/includes/desktop/QtReforce/QStm
equals(QTREFORCE_QORM,true):            HEADERS+= $$PWD/src/includes/desktop/QtReforce/QOrm
equals(QTREFORCE_QRPC,true):            HEADERS+= $$PWD/src/includes/desktop/QtReforce/QRpc
equals(QTREFORCE_QAPR,true):            HEADERS+= $$PWD/src/includes/desktop/QtReforce/QApr
#equals(QTREFORCE_QMFE,true):            HEADERS+= $$PWD/src/includes/desktop/QtReforce/QMfe


message(" ")
message(-QTREFORCE MODULES-DEFINITION-ACCEPT)
message("   -MODULES")
equals(QTREFORCE_QANNOTATION,true)      {message("      +QNOTATION............... accepted") } else { message("      +QNOTATION............... ignored") }
equals(QTREFORCE_QJSONWEBTOKEN,true)    {message("      +QJSONWEBTOKEN........... accepted") } else { message("      +QJSONWEBTOKEN........... ignored") }
equals(QTREFORCE_QTOKENUTIL,true)       {message("      +QTOKENUTIL.............. accepted") } else { message("      +QTOKENUTIL.............. ignored") }
equals(QTREFORCE_QCROSSCACHE,true)      {message("      +QCROSSCACHE............. accepted") } else { message("      +QCROSSCACHE............. ignored") }
equals(QTREFORCE_QSTM,true)             {message("      +QSTM.................... accepted") } else { message("      +QSTM.................... ignored") }
equals(QTREFORCE_QORM,true)             {message("      +QORM.................... accepted") } else { message("      +QORM.................... ignored") }
equals(QTREFORCE_QRPC,true)             {message("      +QRPC.................... accepted") } else { message("      +QRPC.................... ignored") }
equals(QTREFORCE_QAPR,true)             {message("      +QAPR.................... accepted") } else { message("      +QAPR.................... ignored") }
equals(QTREFORCE_QAPIDOC,true)          {message("      +QAPIDOC................. accepted") } else { message("      +QAPIDOC................. ignored") }
equals(QTREFORCE_QMFE,true)             {message("      +QMFE.................... accepted") } else { message("      +QMFE.................... ignored") }
message("   -SOURCES")
equals(QTREFORCE_QANNOTATION,true):      message("      +QNOTATION............... "$$QTREFORCE_QANNOTATION_SOURCE)
equals(QTREFORCE_QJSONWEBTOKEN,true):    message("      +QJSONWEBTOKEN........... "$$QTREFORCE_QJSONWEBTOKEN_SOURCE)
equals(QTREFORCE_QTOKENUTIL,true):       message("      +QTOKENUTIL.............. "$$QTREFORCE_QTOKENUTIL_SOURCE)
equals(QTREFORCE_QCROSSCACHE,true):      message("      +QCROSSCACHE............. "$$QTREFORCE_QCROSSCACHE_SOURCE)
equals(QTREFORCE_QSTM,true):             message("      +QSTM.................... "$$QTREFORCE_QSTM_SOURCE)
equals(QTREFORCE_QORM,true):             message("      +QORM.................... "$$QTREFORCE_QORM_SOURCE)
equals(QTREFORCE_QRPC,true):             message("      +QRPC.................... "$$QTREFORCE_QRPC_SOURCE)
equals(QTREFORCE_QAPR,true):             message("      +QAPR.................... "$$QTREFORCE_QAPR_SOURCE)
equals(QTREFORCE_QAPIDOC,true):          message("      +QAPIDOC................. "$$QTREFORCE_QAPIDOC_SOURCE)
equals(QTREFORCE_QMFE,true):             message("      +QMFE.................... "$$QTREFORCE_QMFE_SOURCE)

HEADERS += \
    $$PWD/src/includes/desktop/QtReforce/QAnnotation

