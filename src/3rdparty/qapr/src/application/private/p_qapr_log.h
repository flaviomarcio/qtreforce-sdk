#pragma once

#include "../qapr_log.h"
#include <QLoggingCategory>
#include <QDebug>
#include <QTime>
#include <QCoreApplication>

namespace QApr {

//!
//! \brief makeQtMsgTypeMap
//! \return
//!
static const QHash<int,QString>&makeQtMsgTypeMap();

//!
//! \brief qtMessageHandlerDefault
//!
static const QtMessageHandler qtMessageHandlerDefault = qInstallMessageHandler(0);

//!
//! \brief qtMsgTypeMap
//!
const static auto qtMsgTypeMap=makeQtMsgTypeMap();


}

