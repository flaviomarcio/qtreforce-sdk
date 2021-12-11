#pragma once

#include <QDateTime>
#include "../qapr_circuit_breaker.h"
#include "../qapr_application.h"
#include "./qstm_setting_base.h"
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

        Q_INVOKABLE explicit CircuitBreakerPvt(QObject *parent = nullptr):QObject(parent){
        }

        Q_INVOKABLE ~CircuitBreakerPvt(){
            this->stop();
        }

        bool start(){
            settingService<<this->setting;
            if(!settingService.enabled())
                this->stop();
            else if(settingService.activityLimit()<=0)
                this->stop();
            else if(this->timerBreaker==nullptr){
                this->timerBreaker=new QTimer(this);
                QObject::connect(this->timerBreaker, &QTimer::timeout,this, &CircuitBreakerPvt::onCheck);
                this->timerBreaker->setInterval(1000);
                this->timerBreaker->start();
            }
            return (this->timerBreaker!=nullptr) && (this->timerBreaker->isActive());
        }

        bool stop(){
            if(this->timerBreaker!=nullptr){
                QObject::disconnect(this->timerBreaker, &QTimer::timeout, this, &CircuitBreakerPvt::onCheck);
                timerBreaker->stop();
                delete timerBreaker;
                this->timerBreaker=nullptr;
            }
            return (this->timerBreaker==nullptr);
        }

    private:
        void onCheck(){
            const auto _activityLimit=settingService.activityLimit();
            const auto _memoryLimit=settingService.memoryLimit();
            const auto _now = QDateTime::currentDateTime();

            if(!this->activityLimit.isValid() || this->activityLimit.isNull())
                this->activityLimit=_activityLimit<=0?QDateTime():_now.addMSecs(_activityLimit);

            if(this->memoryLimitKB<=0)
                this->memoryLimitKB=_memoryLimit/1024;//to KB

            if(activityLimit.isValid() && (_now>this->activityLimit)){
                sWarning()<<qsl("break application by timeout");
                this->onBreak();
            }

            const auto memoryUsage=Application::memoryUsage();
            const auto&memoryLimitKB=this->memoryLimitKB;

            if(memoryLimitKB>0 && (memoryUsage > memoryLimitKB)){
                sWarning()<<qsl("break application by memory limit(limitMem: %1 KB, curMen==%2 KB)").arg(memoryUsage, memoryLimitKB);
                this->onBreak();
            }
        }


        void onBreak(){
            QObject::disconnect(this->timerBreaker, &QTimer::timeout,this, &CircuitBreakerPvt::onCheck);
            this->timerBreaker->stop();
            sWarning()<<qsl("circuit will be stopped");
            qApp->quit();
        }
    };


}
