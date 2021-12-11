#pragma once

#include <QObject>
#include <QThread>
#include <QMap>
#include <QVariant>
#include "./qapr_global.h"
#include "./qrpc_service_manager.h"
#include "./qapr_consts.h"
#include "./qapr_consts.h"
#include "./qorm_connection_manager.h"

namespace QApr {

class Agent;

//!
//! \brief The AgentBase class
//!
class Q_APR_EXPORT AgentBase : public QThread{
    Q_OBJECT
    QORM_CONNECTION_SUPPORT
    friend class AgentBasePvt;
public:
    //!
    //! \brief AgentBase
    //! \param parent
    //!
    Q_INVOKABLE explicit AgentBase(QObject*parent=nullptr);

    //!
    //! \brief ~AgentBase
    //!
    Q_INVOKABLE ~AgentBase();

    //!
    //! \brief agentSetting
    //! \return
    //!assiciate settings
    virtual QRpc::ServiceSetting&agentSetting();

    //!
    //! \brief run
    //!run thread
    void run() override;

    //!
    //! \brief canMethodExecute
    //! \param method
    //! \return
    //!verify can execute selected method
    virtual bool canMethodExecute(const QMetaMethod&method);

    //!
    //! \brief runCheck
    //! \return
    //!verify run method
    virtual bool runCheck();

    //!
    //! \brief start
    //! start thread
    virtual void start();

    //!
    //! \brief agentName
    //! \return
    //!agent name defined
    virtual QByteArray agentName() const;

    //!
    //! \brief setAgentName
    //! \param v
    //!agent name defined
    virtual void setAgentName(const QVariant &v);

    //!
    //! \brief stats
    //! \return
    //!current state
    virtual QVariantHash &stats();

    //!
    //! \brief settings_SERVER
    //! \return
    //!server setting file
    Q_INVOKABLE static const QVariant settings_SERVER();

signals:

    void serviceStart();


    void taskError(const QByteArray&agentName, const QVariant&error);


    void taskFinished(const QByteArray&agentName);


    void taskResume();
private:
    void*p=nullptr;
};
}
