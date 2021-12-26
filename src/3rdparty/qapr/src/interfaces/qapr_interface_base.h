#pragma once

#include "../../qorm/src/qorm_object_db.h"
#include "../../qrpc/src/qrpc_interface_record.h"
#include "./application/qapr_consts.h"
#include "./application/qapr_global.h"
#include <QtSql/QSqlDatabase>

namespace QApr {

//!
//! \brief The InterfaceBase class
//!base inicial criada para aplicacoes, contem metodos e verificacao e alguns utilitarios
class Q_APR_EXPORT InterfaceBase : public QRpc::QRPCController
{
    Q_OBJECT
    Q_DECLARE_OBJECT()
    QORM_CONNECTION_SUPPORT
    Q_RPC_DECLARE_INTERFACE_METHOD_CHECK()
public:
    //!
    //! \brief InterfaceBase
    //! \param parent
    //!
    Q_INVOKABLE explicit InterfaceBase(QObject *parent = nullptr);

    //!
    //! \brief ~InterfaceBase
    //!
    ~InterfaceBase();

private:
    void *p = nullptr;
};

}
