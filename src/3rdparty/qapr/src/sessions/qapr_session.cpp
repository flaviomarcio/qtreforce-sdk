#include "./qapr_session.h"

namespace QApr {

static QHash<QThread*, QObject*>*static_session_instance=nullptr;
static QMutex*static_session_instance_mutex=nullptr;

static void init()
{
    static_session_instance=new QHash<QThread*, QObject*>();
    static_session_instance_mutex=new QMutex();
}

Q_COREAPP_STARTUP_FUNCTION(init);


Session::Session(QObject *parent) : QStm::Object(parent), p_credential(parent)
{
    this->session_thread=QThread::currentThread();
    this->session=dynamic_cast<Session*>(static_session_instance->value(this->session_thread));
    if(this->session==nullptr){
        QMutexLocker locker(static_session_instance_mutex);
        this->session=dynamic_cast<QStm::Object*>(static_session_instance->value(this->session_thread));
        if(this->session==nullptr){
            static_session_instance->insert(session_thread, session);
            this->session=this;
        }
    }
}

Session::~Session()
{
}

Session &Session::instance()
{
    return*dynamic_cast<Session*>(this->session);
}

Session &Session::i()
{
    return*dynamic_cast<Session*>(this->session);
}

SessionCredential &Session::credential()
{
    return this->p_credential;
}

}
