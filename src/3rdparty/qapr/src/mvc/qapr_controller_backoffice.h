#pragma once

#include "./qapr_controller.h"

namespace QApr {

//!
//! \brief The ControllerBackOffice class
//!controller for administering sessions and permissions
class ControllerBackOffice : public QApr::Controller
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ControllerBackOffice(QObject *parent = nullptr);
    Q_INVOKABLE ~ControllerBackOffice();

    //!
    //! \brief sessionAccount
    //! \return
    //!create account object of session
    virtual ResultValue &sessionAccount();

    //!
    //! \brief rootObject
    //! \return
    //!create main session object
    virtual ResultValue &rootObject();

    //!
    //! \brief menuInfo
    //! \param body
    //! \return
    //!return information with specific menu
    virtual ResultValue &menuInfo(const QVariant &body);

    //!
    //! \brief enviroment
    //! \return
    //!create session enviroment variables
    virtual ResultValue &enviroment();

};

}
