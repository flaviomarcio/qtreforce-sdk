#include "./qapr_notify_dispatch.h"
#include "./qapr_notify.h"
#include "./qstm_util_variant.h"

namespace QApr {

#define dPvt()\
    auto&p = *reinterpret_cast<NotifyDispatchPvt*>(this->p)

class NotifyDispatchPvt//:public QObject
{
public:
    QByteArray channel;
    QByteArray md5;
    NotifyDispatch*parent=nullptr;
    VariantUtil vu;
    explicit NotifyDispatchPvt(NotifyDispatch*parent=nullptr)//:QObject(parent)
    {
        this->parent=parent;
    }
};

NotifyDispatch::NotifyDispatch(QObject *parent)//:QObject(parent)
{
    Q_UNUSED(parent)
    this->p= new NotifyDispatchPvt(this);
}

NotifyDispatch::NotifyDispatch(const QByteArray &name, const QByteArray &md5, QObject *parent)//QObject(parent)
{
    Q_UNUSED(parent)
    this->p= new NotifyDispatchPvt(this);
    dPvt();
    p.channel=name;
    p.md5=md5;
}

NotifyDispatch::~NotifyDispatch(){
    dPvt();
    delete&p;
}

void NotifyDispatch::clear()
{
    this->setChannel(qbl_null);
    this->setMd5(qbl_null);
}

QByteArray NotifyDispatch::channel() const
{
    dPvt();
    return p.channel;
}

void NotifyDispatch::setChannel(const QByteArray &value)
{
    dPvt();
    p.channel=value;
}

QByteArray NotifyDispatch::md5() const
{
    dPvt();
    return p.md5;
}

void NotifyDispatch::setMd5(const QByteArray &value)
{
    dPvt();
    p.md5=value;
}

void NotifyDispatch::notify(const QVariant &payload)
{
    Notify::instance().notify(this->channel(), payload);
}

void NotifyDispatch::notify(const QString &channel, const QVariant &payload)
{
    Notify::instance().notify(channel, payload);
}

}

