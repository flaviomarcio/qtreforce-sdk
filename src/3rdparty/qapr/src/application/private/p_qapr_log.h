#pragma once

#include "../qapr_log.h"
#include <QLoggingCategory>
#include <QDebug>
#include <QTime>
#include <QCoreApplication>

namespace QApr {

static const QHash<int,QString> makeQtMsgTypeMap(){
    QHash<int,QString> map;
    map[QtDebugMsg   ]=qsl("D");
    map[QtWarningMsg ]=qsl("W");
    map[QtCriticalMsg]=qsl("C");
    map[QtFatalMsg   ]=qsl("F");
    map[QtInfoMsg    ]=qsl("I");
    map[QtSystemMsg  ]=qsl("S");
    qputenv(qbl("QT_LOGGING_RULES"), qbl("qt.network.ssl.warning=false;qml.debug=true;*.debug=true;*.warning=true;*.critical=true;*.info=true"));
    return map;
}

static const QtMessageHandler qtMessageHandlerDefault = qInstallMessageHandler(0);
const static auto qtMsgTypeMap=makeQtMsgTypeMap();


}

