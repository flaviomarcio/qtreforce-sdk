#include "./qapr_agent_base.h"
#include "./qapr_agent.h"
#include "./qapr_application.h"
#include <QTimer>
#include <QCryptographicHash>
#include <QVariant>
#include <QMutex>
#include <QMetaProperty>

namespace QApr{

#define dPvt()\
    auto&p = *reinterpret_cast<AgentBasePvt*>(this->p)

class AgentBasePvt:public QObject{
public:
    QMutex serviceStartLock;
    QDateTime runner_date;
    QVariantHash stats;
    AgentBase*parent = nullptr;
    explicit AgentBasePvt(AgentBase*parent=nullptr):QObject(parent){
        this->parent=parent;
    }
public slots:
    void onServiceRun(){
#if QAPR_LOG_VERBOSE
        sWarning()<<this->parent->agentName()<<tr(": started");
#endif
        QMutexLocker locker(&serviceStartLock);
        auto&pp=*this->parent;
#if QAPR_LOG_SUPER_VERBOSE
        sInfo()<<"run "<<pp.agentName();
#endif
        this->runner_date=QDateTime::currentDateTime();
        auto&cnMng=Application::instance().connectionManager();
        auto manager=QOrm::ConnectionManager(cnMng, this);
        auto&pool=manager.pool();
        const auto&agentSetting=pp.agentSetting();
        Q_UNUSED(agentSetting)
        QSqlDatabase db;
#if QAPR_LOG_VERBOSE
        sInfo()<<this->agentName()<<", db connecting";
#endif
        if(!pool.get(db)){
#if QAPR_LOG
            sInfo()<<pp.agentName()<<qsl(", no connection db: ")<<pool.lastError().text();
#endif
        }
        else if(pp.setConnection(db)){
#if QAPR_LOG_VERBOSE
            sInfo()<<this->agentName()<<", "<<agentSetting.name();
#endif
            this->service_start();
            pool.finish(db);
        }
#if QAPR_LOG_VERBOSE
        sWarning()<<this->parent->agentName()<<tr(": finished");
#endif
    }
    void service_start(){
#if QAPR_LOG_VERBOSE
        aDebugMethodStart();
#endif
        auto&pp=*this->parent;
        auto agentName=pp.agentName();
        auto metaObject=pp.metaObject();
        auto methodName=agentName;
        auto message=tr("Method not found");
        for(int methodIndex = 0; methodIndex < metaObject->methodCount(); ++methodIndex) {
            auto method = metaObject->method(methodIndex);
            if(method.parameterCount()>0)
                continue;

            if(method.name().toLower() != methodName)
                continue;

            if(!pp.canMethodExecute(method))
                continue;

            if(!method.invoke(&pp, Qt::DirectConnection)){
                message=tr("Method not called");
#if QAPR_LOG_VERBOSE
                sDebug()<<"invoke method: error=="<<message;
#endif
                continue;
            }
#if QAPR_LOG_VERBOSE
            sDebug()<<"invoke method:"<<method.name();
#endif
            break;
        }
#if QAPR_LOG_VERBOSE
        aDebugMethodFinish();
#endif
        this->runner_date=this->makeNewDateRun();
    }

    QDateTime makeNewDateRun(){

        auto&agentSetting=this->parent->agentSetting();
        auto interval = agentSetting.activityInterval();
        auto next=QDateTime::currentDateTime();
        next=next.addMSecs(interval);

        return next;
    }

    bool runCheck()
    {
        auto&p=*this;
        auto service=this->parent->agentName();
        auto&agentSetting=this->parent->agentSetting();
        if(!agentSetting.enabled()){
#if QAPR_LOG_VERBOSE
            sInfo()<<service<<qsl(" disabled");
#endif
        }
        else{
            auto _run=[this, &p, &service](){
                Q_UNUSED(service)
                this->runner_date=this->makeNewDateRun();
                if(!p.serviceStartLock.tryLock(10)){
#if QAPR_LOG_VERBOSE
                    sInfo()<<service<<qsl(" skipped");
#endif
                }
                else{
                    emit this->parent->serviceStart();
                    p.serviceStartLock.unlock();
                    return true;
                }
                return false;
            };

            auto now=QDateTime::currentDateTime();
            if(p.runner_date.isNull())
                return _run();

            if(now>p.runner_date)
                return _run();
        }
        return false;
    }
};


AgentBase::AgentBase(QObject *parent):QThread(nullptr)
{
    Q_UNUSED(parent)
    this->p = new AgentBasePvt(this);
    this->moveToThread(this);
    dPvt();
    QObject::connect(this, &AgentBase::serviceStart, &p, &AgentBasePvt::onServiceRun);
}

AgentBase::~AgentBase()
{
    dPvt();
    delete&p;
}

QRpc::ServiceSetting &AgentBase::agentSetting()
{
    auto&manager=Application::instance().manager();
    auto agentName=this->agentName();
    auto&setting=manager.setting(agentName);
    if(!setting.enabled()){
        static QRpc::ServiceSetting __default;
        return __default;
    }
    else{
        return setting;
    }
}

void AgentBase::run()
{
#if QAPR_LOG_VERBOSE
    sInfo()<<tr("started");
#endif
    this->exec();
}

bool AgentBase::canMethodExecute(const QMetaMethod &method)
{
    Q_UNUSED(method)
    return true;
}

bool AgentBase::runCheck()
{
    dPvt();
    return p.runCheck();
}

void AgentBase::start()
{
    if(this->agentSetting().enabled()){
        if(!this->isRunning()){
            QThread::start();
            while(this->eventDispatcher()==nullptr)
                QThread::msleep(1);
        }
    }
}

QByteArray AgentBase::agentName() const
{
    auto v=this->property(qbl("agentName")).toByteArray();
    return v;
}

void AgentBase::setAgentName(const QVariant &v)
{
    this->setProperty(qbl("agentName"),v);
    auto c_name=QString(this->metaObject()->className());
    auto a_name=QString(this->agentName());
    auto objectName=qsl("%1::%2").arg(c_name, a_name);
    objectName=objectName.replace(qsl(":"),qsl("_")).replace(qsl("__"),qsl("_"));
    this->setObjectName(objectName);
}

QVariantHash &AgentBase::stats()
{
    dPvt();
    return p.stats;
}

const QVariant AgentBase::settings_SERVER()
{
    return QApr::Application::instance().settings_SERVER();
}



}
