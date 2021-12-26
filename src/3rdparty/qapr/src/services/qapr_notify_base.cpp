#include "./qapr_notify_base.h"
#include "./qapr_notify.h"
#include "./qapr_application.h"
#include <QTimer>
#include <QCryptographicHash>
#include <QVariant>
#include <QMutex>
#include <QMetaProperty>

namespace QApr{

#define dPvt()\
    auto&p = *reinterpret_cast<NotifyBasePvt*>(this->p)

class NotifyBasePvt:public QObject{
public:
    NotifyBase*parent=nullptr;
    VariantUtil vu;
    explicit NotifyBasePvt(NotifyBase*parent=nullptr):QObject(parent){
        this->parent=parent;
    }
};


NotifyBase::NotifyBase(QObject *parent):QThread(nullptr)
{
    Q_UNUSED(parent)
    this->p = new NotifyBasePvt(this);
    this->moveToThread(this);
}

NotifyBase::~NotifyBase()
{
    dPvt();
    delete&p;
}

QRpc::ServiceSetting &NotifyBase::notifySetting()
{
    auto&manager=Application::instance().manager();
    auto notifyName=this->notifyName();
    auto&setting=manager.setting(notifyName);
    if(!setting.enabled()){
        static QRpc::ServiceSetting __default;
        return __default;
    }
    else{
        return setting;
    }
}

void NotifyBase::run()
{
    QObject::connect(this, &NotifyBase::notifyReceived, this, &NotifyBase::onNotifyReceived);
    this->exec();
    QObject::disconnect(this, &NotifyBase::notifyReceived, this, &NotifyBase::onNotifyReceived);
}

void NotifyBase::start()
{
    if(this->notifySetting().enabled()){
        QThread::start();
        while(this->eventDispatcher()==nullptr)
            QThread::msleep(1);
    }
}

QString NotifyBase::notifyName() const
{
    auto v=this->property(qbl("notifyName")).toString();
    return v;
}

void NotifyBase::setNotifyName(const QVariant &v)
{
    this->setProperty(qbl("notifyName"),v);
    auto objectName=qsl("%1::%2").arg(QString(this->metaObject()->className()), QString(this->notifyName()));
    objectName=objectName.replace(qsl(":"),qsl("_")).replace(qsl("__"),qsl("_"));
    this->setObjectName(objectName);
}

const QVariant NotifyBase::settings_SERVER()
{
    return QApr::Application::instance().settings_SERVER();
}

void NotifyBase::onNotifyReceived(const QString &channel, const QVariant &payload){
    dPvt();
    Q_UNUSED(channel)
    auto metaObject=this->metaObject();
    auto methodName=this->notifyName();
    auto message=tr("Method not found");
    for(int methodIndex = 0; methodIndex < metaObject->methodCount(); ++methodIndex) {
        auto method = metaObject->method(methodIndex);
        if(method.parameterCount()>2)
            continue;

        if(method.name().toLower() != methodName)
            continue;

        auto pType=QMetaType_UnknownType;
        if(method.parameterCount()==1){
            pType=method.parameterType(0);
        }
        else if(method.parameterCount()==2){
            pType=method.parameterType(1);
        }

        QVariant vPayload=payload;
        //se o tipo de parametro de entrar for um objeto tentaremos converter para compativilidade de objeto json/cbor
        if(pType==QMetaType_QVariantHash || pType==QMetaType_QVariantMap || pType==QMetaType_QVariantList || pType==QMetaType_QStringList){
            vPayload=p.vu.toVariant(vPayload);
        }

        auto argChannel=QGenericArgument(qbl("QVariant"), &channel);
        auto arcPayload=QGenericArgument(qbl("QVariant"), &vPayload);
        QOrm::ConnectionManager manager(Application::instance().connectionManager(), this);
        auto&pool=manager.pool();
        QSqlDatabase db;
        if(!pool.get(db)){
            pool.finish(db);
        }
        else if(this->setConnection(db)){
            pool.finish(db);
        }
        else{
            if(method.parameterCount()==0 && !method.invoke(this, Qt::DirectConnection)){
                message=tr("Method not called");
#if QAPR_LOG_VERBOSE
                sDebug()<<tr("invoke method: error==")<<message;
#endif
            }
            else if(method.parameterCount()==1 && !method.invoke(this, Qt::DirectConnection, arcPayload)){
                message=tr("Method not called");
#if QAPR_LOG_VERBOSE
                sDebug()<<tr("invoke method: error==")<<message;
#endif
            }
            else if(method.parameterCount()==2 && !method.invoke(this, Qt::DirectConnection, argChannel, arcPayload)){
                message=tr("Method not called");
#if QAPR_LOG_VERBOSE
                sDebug()<<tr("invoke method: error==")<<message;
#endif
            }
            else{
#if QAPR_LOG_VERBOSE
                sDebug()<<tr("invoke method:")<<method.name();
#endif
                pool.finish(db);
                break;
            }
        }
    }
}

}
