#pragma once

#include <QCoreApplication>
#include <QObject>
#include "../application/qapr_global.h"
#include "../../qrpc/src/qrpc_service_manager.h"
#include "../../qorm/src/qorm_connection_manager.h"
#include "./qapr_consts.h"
#include "./qapr_circuit_breaker.h"

namespace QApr {

//!
//! \brief The Application class
//!
class Q_APR_EXPORT Application : public QObject
{
    Q_OBJECT
    QORM_SERVER_CONNECTION_MANAGER_SUPPORT(Application)
public:
    Q_INVOKABLE explicit Application(QObject *parent = nullptr);
    Q_INVOKABLE ~Application();

    //!
    //! \brief settings_SERVER
    //! \return
    //!
    Q_INVOKABLE virtual QVariant settings_SERVER() const;

    //!
    //! \brief manager
    //! \return
    //!configuracoes para servicos
    virtual QRpc::ServiceManager&manager();

    //!
    //! \brief exec
    //! \param a
    //! \return
    //!init application and resource to Application
    virtual int exec(QCoreApplication &a);

    //!
    //! \brief instance
    //! \return
    //!
    static Application&instance();

    //!
    //! \brief i
    //! \return
    //!
    static Application&i();

    //!
    //! \brief memoryUsage
    //! \return
    //!
    static qlonglong memoryUsage();

    //!
    //! \brief instanceUuid
    //! \return
    //!application instance
    virtual const QUuid &instanceUuid();

    //!
    //! \brief arguments
    //! \return
    //!mix entre qApp->arguments() e manager->arguments();
    virtual QVariantHash &arguments() const;

    //!
    //! \brief printArguments
    //! \return
    //!
    virtual Application &printArguments();

    //!
    //! \brief resourceExtract
    //! \return
    //!
    virtual Application &resourceExtract();

    //!
    //! \brief circuitBreaker
    //! \return
    //!
    virtual QApr::CircuitBreaker&circuitBreaker();

private:
    void*p=nullptr;
};

}
