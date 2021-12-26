#pragma once

#include <QDateTime>
#include "../qapr_circuit_breaker.h"
#include "../qapr_application.h"
#include "../../../../qstm/src/qstm_setting_base.h"
#include <QTimer>
#include <QCoreApplication>

namespace QApr {

class Q_APR_EXPORT CircuitBreakerPvt : public QObject
{
    Q_OBJECT
public:
    QStm::SettingBase settingService;
    QVariantHash setting;
    QTimer*timerBreaker=nullptr;

    QDateTime activityLimit;
    qlonglong memoryLimitKB=0;

    explicit CircuitBreakerPvt(QObject *parent = nullptr);

    Q_INVOKABLE ~CircuitBreakerPvt();

    bool start();

    bool stop();

private:
    void onCheck();

    void onBreak();
};


}
