#pragma once

#include <QObject>
#include <QThread>
#include <QMap>
#include <QVariant>
#include "./qrpc_service_manager.h"
#include "./qrpc_service_setting.h"
#include "./qapr_consts.h"
#include "./qapr_consts.h"
#include "./qorm_connection_manager.h"

namespace QApr {

class Notify;

//!
//! \brief The NotifyBase class
//!
class Q_APR_EXPORT NotifyBase : public QThread{
    Q_OBJECT
    QORM_CONNECTION_SUPPORT
    QORM_DECLARE_TOPIC(qsl("nothing/null"))
public:
    //!
    //! \brief NotifyBase
    //! \param parent
    //!
    Q_INVOKABLE explicit NotifyBase(QObject*parent=nullptr);

    //!
    //! \brief ~NotifyBase
    //!
    Q_INVOKABLE ~NotifyBase();

    //!
    //! \brief notifySetting
    //! \return
    //!
    virtual QRpc::ServiceSetting&notifySetting();

    //!
    //! \brief run
    //!
    void run() override;

    //!
    //! \brief start
    //!
    virtual void start();

    //!
    //! \brief notifyName
    //! \return
    //!
    Q_INVOKABLE virtual QString notifyName() const;

    //!
    //! \brief setNotifyName
    //! \param v
    //!
    Q_INVOKABLE virtual void setNotifyName(const QVariant &v);

    //!
    //! \brief settings_SERVER
    //! \return
    //!
    Q_INVOKABLE static const QVariant settings_SERVER();

private slots:

    //!
    //! \brief onNotifyReceived
    //! \param channel
    //! \param payload
    //!
    virtual void onNotifyReceived(const QString&channel, const QVariant &payload);
signals:

    //!
    //! \brief notifyReceived
    //! \param channel
    //! \param payload
    //!
    void notifyReceived(const QString&channel, const QVariant&payload);
private:
    void*p=nullptr;
};
}
