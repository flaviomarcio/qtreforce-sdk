#pragma once

#include "./qapr_global.h"
#include "./qstm_macro.h"
#include "./qorm_controller.h"
#include "./qrpc_listen_request.h"
#include "./qrpc_service_setting.h"
#include <QUuid>

namespace QApr {
class InterfaceDatabase;

//!
//! \brief The Controller class
//!class controller to business
class Q_APR_EXPORT Controller : public QOrm::Controller
{
    Q_OBJECT
public:
    //!
    //! \brief Controller
    //! \param parent
    //!
    Q_INVOKABLE explicit Controller(QObject *parent = nullptr);

    //!
    //! \brief ~Controller
    //!
    Q_INVOKABLE ~Controller();

    //!
    //! \brief resultInfo
    //! \return
    //!
    Q_INVOKABLE virtual const QVariant resultInfo();

    //!
    //! \brief interfaceRequest
    //! \return
    //!
    virtual InterfaceDatabase *interfaceRequest();

    //!
    //! \brief irq
    //! \return
    //!alias for interfaceRequest
    virtual InterfaceDatabase *irq();

    //!
    //! \brief transactionRollbackForce
    //! \return
    //!se true mesmo com tudo correto ocorrerá o rollback da transacao
    virtual bool transactionRollbackForce() const;

    //!
    //! \brief setTransactionRollbackForce
    //! \param value
    //!se true mesmo com tudo correto ocorrerá o rollback da transacao
    virtual void setTransactionRollbackForce(bool value);

private:
    void *p = nullptr;
};

}
