#pragma once

#include <QObject>
#include <QThread>
#include "./qrpc_service_manager.h"
#include "./qorm_connection_manager.h"
#include "./qapr_global.h"
#include "./qapr_consts.h"
#include "./qapr_notify_base.h"
#include "./qapr_notify_dispatch.h"

#define DECLARE_NOTIFY_DISPACHER(NotifyClass, methodName)\
static QApr::NotifyDispatch&methodName##_dispatch = QApr::Notify::instance().dispatcherRegister(NotifyClass::staticMetaObject, QByteArrayLiteral(#methodName));

namespace QApr{
//!
//! \brief The Notify class
//!
class Q_APR_EXPORT Notify : public QThread
{
    Q_OBJECT
    QORM_DECLARE_INSTANCE(Notify)
public:

    //!
    //! \brief Notify
    //! \param parent
    //!
    Q_INVOKABLE explicit Notify(QObject*parent=nullptr);

    //!
    //! \brief ~Notify
    //!
    Q_INVOKABLE ~Notify();

    //!
    //! \brief settings_SERVER
    //! \return
    //!
    Q_INVOKABLE static const QVariant settings_SERVER();

    void run() override;

    //!
    //! \brief start
    //! \return
    //!
    virtual bool start();

    //!
    //! \brief stop
    //! \return
    //!
    virtual bool stop();

    //!
    //! \brief serviceStart
    //! \param service
    //!
    virtual void serviceStart(const QByteArray &service);

    //!
    //! \brief dispatcherRegister
    //! \param metaObject
    //! \param name
    //! \return
    //!
    virtual NotifyDispatch &dispatcherRegister(const QMetaObject &metaObject, const QByteArray &name);

    //!
    //! \brief notify
    //! \param channel
    //! \param payload
    //! \return
    //!
    virtual bool notify(const QString&channel, const QVariant&payload);

private:
    void*p=nullptr;
};

//static auto&NotifyApp=Notify::instance();
}
