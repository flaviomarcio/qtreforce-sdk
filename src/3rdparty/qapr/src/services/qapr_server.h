#pragma once

#include <QObject>
#include "./qrpc_server.h"
#include "./qapr_global.h"

namespace QApr {

//!
//! \brief The Server class
//!
class Q_APR_EXPORT Server : public QRpc::QRPCServer
{
    Q_OBJECT
    Q_DECLARE_INSTANCE(Server)
public:
    //!
    //! \brief Server
    //! \param parent
    //!
    Q_INVOKABLE explicit Server(QObject *parent = nullptr);

    //!
    //! \brief ~Server
    //!
    Q_INVOKABLE ~Server();

    //!
    //! \brief settings_SERVER
    //! \return
    //!
    Q_INVOKABLE const QVariant settings_SERVER();
private:
    void*p=nullptr;
};
}
