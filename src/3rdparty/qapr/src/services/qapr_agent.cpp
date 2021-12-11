#include "./qapr_agent.h"
#include "./qapr_application.h"
#include "./qapr_agent_base.h"
#include <QMultiHash>
#include <QMutex>
#include <QTimer>

namespace QApr {

#define dPvt()\
    auto&p =*reinterpret_cast<AgentPvt*>(this->p)

class AgentPvt: public QObject{
public:
    QString topicSetting;
    QMutex mutexAgent;
    Agent*agent=nullptr;
    QOrm::ConnectionNotify connectionNotify;
    QMultiHash<QByteArray, const QMetaObject*> services;
    QHash<QByteArray, AgentBase*> tasks;
    QHash<QByteArray, QDateTime> tasksInterval;
    QTimer*timer=nullptr;
    explicit AgentPvt(Agent*parent) : QObject(parent), agent(parent){


    }
    virtual ~AgentPvt(){
        this->freeTimer();
    }

    void freeTimer(){
        if(this->timer!=nullptr){
            QObject::disconnect(timer, &QTimer::timeout, this, &AgentPvt::taskCheck);
            this->timer->stop();
            this->timer=nullptr;
        }
    }

    QTimer*newTimer(){
        freeTimer();
        auto timer=new QTimer(nullptr);
        timer->setInterval(500);
        QObject::connect(timer, &QTimer::timeout, this, &AgentPvt::taskCheck);
        return timer;
    }

    AgentBase*taskInstance(const QByteArray&service){
        return this->tasks.value(service);
    }

    const QVariantHash taskStats(const QByteArray&service){
        QMutexLocker locker(&mutexAgent);
        auto task=this->taskInstance(service);
        return (task==nullptr)?QVariantHash():task->stats();
    }
public slots:
    void taskRun(const QByteArray&service){
        auto task = this->tasks.value(service);
        if(task==nullptr){
            auto metaObject=this->services.value(service);
            auto object=metaObject->newInstance(Q_ARG(QObject*, nullptr ));
            if(object!=nullptr){
                task=dynamic_cast<AgentBase*>(object);
                if(task==nullptr)
                    delete object;
                else{
                    //QObject::connect(task, &AgentBase::task_finished, this, &AgentPvt::taskFinished);
                    this->tasks.insert(service, task);
                    task->setAgentName(service);
                    task->start();
                }
            }
        }

        if(task!=nullptr){
            auto&settings=task->agentSetting();
            if(settings.enabled()){
                task->start();
                task->runCheck();
            }
        }
    }

    void taskCheck(){
        QMutexLOCKER locker(&mutexAgent);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QHashIterator<QByteArray, const QMetaObject*> i(this->services);
#else
        QMultiHashIterator<QByteArray, const QMetaObject*> i(this->services);
#endif
        while (i.hasNext()) {
            i.next();
            auto&service=i.key();
            auto task = this->tasks.value(service);
            if(task==nullptr){
                auto metaObject=this->services.value(service);
                auto object=metaObject->newInstance(Q_ARG(QObject*, nullptr ));
                if(object!=nullptr){
                    task=dynamic_cast<AgentBase*>(object);
                    if(task==nullptr)
                        delete object;
                    else{
                        //QObject::connect(task, &AgentBase::task_finished, this, &AgentPvt::taskFinished);
                        this->tasks.insert(service, task);
                        task->setAgentName(service);
                        task->start();
                    }
                }
            }

            this->taskRun(service);
        }
    }

    bool serviceRegister(const QMetaObject&metaObject, const QByteArray &methodNames){
        static auto chars=QStringList{qsl(";"),qsl("|"),qsl(","),qsl("  ")};
        QString service=methodNames;
        for(auto&c:chars){
            while(service.contains(c))
                service=service.replace(c,qsl_space);
        }
        auto listMethod=methodNames.split(' ');
        for(auto&service:listMethod){
            if(services.contains(service.trimmed()))
                services.replace(service.trimmed(), &metaObject);
            else
                services.insert(service.trimmed(), &metaObject);
        }
        return true;
    }


private slots:
    void db_notification(const QString &channel, const QVariant &payload){
        if(channel.toLower()==this->topicSetting){
            this->agent->notifySettingsChanged(payload);
        }
    }
    void taskFinished(const QVariant&v){
        auto service = v.toByteArray();
        auto task = this->tasks.value(service);
        if(task!=nullptr){
            emit task->taskResume();
        }
    }
};

Agent::Agent(QObject*parent):QThread(nullptr)
{
    Q_UNUSED(parent)
    this->p = new AgentPvt(this);
}

Agent::~Agent()
{
    dPvt();
    delete&p;
}

const QVariant Agent::settings_SERVER()
{
    return QApr::Application::instance().settings_SERVER();
}

void Agent::run()
{
    dPvt();
    p.topicSetting=qsl("agent:%1").arg(QT_STRINGIFY2(topicSetting)+qsl(":")+QString::fromUtf8(this->metaObject()->className()));
#ifdef QAPR_LOG_VERBOSE
    sWarning()<<qsl("started");
#endif
    p.timer=p.newTimer();
    p.timer->start();
    sDebug()<<qsl("Agent: running");
    this->exec();
    p.freeTimer();
}

bool Agent::start()
{
#ifdef QAPR_LOG_VERBOSE
    sWarning()<<qsl("started");
#endif
    auto objectName=this->objectName().trimmed();
    if(objectName.isEmpty()){
        objectName=this->metaObject()->className();
        while(objectName.contains(qsl(":")))
            objectName=objectName.replace(qsl(":"),qsl("_"));
        while(objectName.contains(qsl("__")))
            objectName=objectName.replace(qsl("__"),qsl("_"));
    }
    this->setObjectName(objectName);
    QThread::start();
    while(this->eventDispatcher()==nullptr)
        QThread::msleep(1);
    return true;
}

bool Agent::stop()
{
    this->quit();
    return true;
}

void Agent::serviceStart(const QByteArray&service)
{
    dPvt();
    p.taskRun(service);
}

QVariantHash Agent::serviceStats(const QByteArray&service)
{
    dPvt();
    return p.taskStats(service);
}

bool Agent::serviceRegister(const QMetaObject&metaObject, const QByteArray &service)
{
    dPvt();
    return p.serviceRegister(metaObject, service);
}

bool Agent::notifySettingsChanged(const QVariant&payload)
{
    dPvt();
    return p.connectionNotify.notify_send(p.topicSetting, payload);
}

}
