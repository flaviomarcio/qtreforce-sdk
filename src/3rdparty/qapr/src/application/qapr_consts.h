#pragma once

#include "./qapr_global.h"
#include "./qstm_macro.h"
#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QUuid>
#include <QDir>
#include <QThread>

static const auto appInstanceUuid=QUuid::createUuidV5(QUuid::createUuid(),QUuid::createUuid().toString());
static const auto settings_HOME_DIR=QStringLiteral("%1/magma.files").arg(QDir::homePath());

#ifdef Q_APR_TEST
static const auto settings_SERVER_FILE=QStringLiteral("settings.test.json");
#elif QT_NO_DEBUG
static const auto settings_SERVER_FILE=QStringLiteral("settings.release.json");
#else
static const auto settings_SERVER_FILE=QStringLiteral("settings.debug.json");
#endif

#define CORE_OBJECT_INSTANCE(staticType)\
static staticType&instance(){\
    static staticType*_##staticType=nullptr;\
    if(_##staticType==nullptr)\
        _##staticType=new staticType(nullptr);\
    return*_##staticType;\
}


#define QAPR_LOG true
#define QAPR_LOG_VERBOSE false
#define QAPR_LOG_SUPER_VERBOSE false

#if QAPR_LOG_VERBOSE
#undef QAPR_LOG
#define QAPR_LOG true
#endif

#if QAPR_LOG_SUPER_VERBOSE
#undef QAPR_LOG
#undef QAPR_LOG_VERBOSE

#define QAPR_LOG true
#define QAPR_LOG_VERBOSE true
#endif


#if QAPR_LOG
#ifdef QT_DEBUG
#define QAPR_LOG_DEBUG true
#else
#define QAPR_LOG_DEBUG false
#endif

#ifdef QT_RELEASE
#define QAPR_LOG_RELEASE true
#else
#define QAPR_LOG_RELEASE false
#endif
#else
#define QAPR_LOG_DEBUG false
#define QAPR_LOG_RELEASE false
#endif

