#pragma once

#include "./qapr_global.h"
#include "./qapr_session_credential.h"
#include <QMutex>
#include <QThread>
#include <QCoreApplication>

namespace QApr {

//!
//! \brief The Session class
//!
class Q_APR_EXPORT Session : public QStm::Object
{
    Q_OBJECT
public:
    //!
    //! \brief Session
    //! \param parent
    //!
    Q_INVOKABLE explicit Session(QObject *parent = nullptr);

    //!
    //! \brief ~Session
    //!
    Q_INVOKABLE ~Session();

    //!
    //! \brief instance
    //! \return
    //!
    Session&instance();

    //!
    //! \brief i
    //! \return
    //!
    Session&i();

    //!
    //! \brief credential
    //! \return
    //!
    virtual SessionCredential&credential();

    void init();

private:
    SessionCredential p_credential;
    QThread*session_thread=nullptr;
    QStm::Object*session=nullptr;
};

}
