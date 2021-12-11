#pragma once

#include "./qapr_interface_database.h"

namespace QApr {

//!
//! \brief The InterfaceBackOffice class
//!camada criada para organizar menus e aesso do backoffice
class Q_APR_EXPORT InterfaceBackOffice : public QApr::InterfaceDatabase
{
    Q_OBJECT
    Q_DECLARE_OBJECT()
    QRPC_DECLARE_MODULE(qsl_fy(QApr))
    QRPC_DECLARE_DESCRIPTION(qsl_fy(QApr::BackOffice))
public:
    //!
    //! \brief InterfaceBackOffice
    //! \param parent
    //!
    Q_INVOKABLE explicit InterfaceBackOffice(QObject *parent = nullptr);

    //!
    //! \brief ~InterfaceBackOffice
    //!
    Q_INVOKABLE ~InterfaceBackOffice();

    //!
    //! \brief rootObject
    //! \return
    //!objeto principal com toda a informacao
    Q_INVOKABLE virtual const QVariant rootObject();

    //!
    //! \brief sessionAccount
    //! \return
    //!objeto com a informacao da sessao e conta relacionada ao request
    Q_INVOKABLE virtual const QVariant sessionAccount();

    //!
    //! \brief enviroment
    //! \return
    //!variaveis de ambiente para ajustes no front
    Q_INVOKABLE virtual const QVariant enviroment();

    //!
    //! \brief menu
    //! \return
    //!menu principal com todos as opcoes
    Q_INVOKABLE virtual const QVariant menu();

    //!
    //! \brief menuInfo
    //! \return
    //!requisita da dos de um menu especifico
    Q_INVOKABLE virtual const QVariant menuInfo();

private:
    void *p = nullptr;
};

}
