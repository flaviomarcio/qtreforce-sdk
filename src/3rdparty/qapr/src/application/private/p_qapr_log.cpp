#include "./p_qapr_log.h"

namespace QApr {

const QHash<int, QString>&makeQtMsgTypeMap()
{
    static QHash<int,QString> vHash;
    vHash[QtDebugMsg   ]=QStringLiteral("D");
    vHash[QtWarningMsg ]=QStringLiteral("W");
    vHash[QtCriticalMsg]=QStringLiteral("C");
    vHash[QtFatalMsg   ]=QStringLiteral("F");
    vHash[QtInfoMsg    ]=QStringLiteral("I");
    vHash[QtSystemMsg  ]=QStringLiteral("S");
    qputenv(QByteArrayLiteral("QT_LOGGING_RULES"), QByteArrayLiteral("qt.network.ssl.warning=false;qml.debug=true;*.debug=true;*.warning=true;*.critical=true;*.info=true"));
    return vHash;
}


}

