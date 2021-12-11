#include "./private/p_qapr_circuit_breaker.h"
#include "./qstm_util_variant.h"

#define dPvt()\
    auto&p = *reinterpret_cast<CircuitBreakerPvt*>(this->p)

namespace QApr {

    CircuitBreaker::CircuitBreaker(QObject *parent):QObject(parent)
    {
        this->p=new CircuitBreakerPvt(this);
    }

    CircuitBreaker::~CircuitBreaker()
    {
        dPvt();
        delete&p;
    }

    QVariantHash CircuitBreaker::settings() const
    {
        dPvt();
        return p.setting;
    }

    CircuitBreaker &CircuitBreaker::settings(const QVariantHash &v)
    {
        dPvt();
        p.setting=v;
        return*this;
    }

    CircuitBreaker &CircuitBreaker::setSettings(const QVariantHash &v)
    {
        dPvt();
        p.setting=v;
        return*this;
    }

    bool CircuitBreaker::start()
    {
        dPvt();
        return p.start();
    }

    bool CircuitBreaker::stop()
    {
        dPvt();
        return p.stop();
    }

    void CircuitBreaker::print()const
    {
        dPvt();
        Q_DECLARE_VU;
        sInfo()<<qsl(".");
        QStm::SettingBase settingService;
        settingService=p.setting;
        settingService.print();
    }

    bool CircuitBreaker::isRunning()
    {
        dPvt();
        return p.timerBreaker!=nullptr;
    }

}

