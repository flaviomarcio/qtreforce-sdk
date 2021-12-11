#pragma once

#include <QObject>
#include "./qapr_global.h"

namespace QApr{

//!
//! \brief The NotifyDispatch class
//!
class Q_APR_EXPORT NotifyDispatch// : public QObject
{
public:
    //!
    //! \brief NotifyDispatch
    //! \param parent
    //!
    Q_INVOKABLE explicit NotifyDispatch(QObject*parent=nullptr);

    //!
    //! \brief NotifyDispatch
    //! \param name
    //! \param md5
    //! \param parent
    //!
    Q_INVOKABLE explicit NotifyDispatch(const QByteArray&name, const QByteArray&md5, QObject*parent=nullptr);

    //!
    //! \brief ~NotifyDispatch
    //!
    Q_INVOKABLE ~NotifyDispatch();

    //!
    //! \brief clear
    //!
    void clear();

    //!
    //! \brief channel
    //! \return
    //!
    QByteArray channel() const;

    //!
    //! \brief setChannel
    //! \param value
    //!
    void setChannel(const QByteArray &value);

    //!
    //! \brief md5
    //! \return
    //!
    QByteArray md5() const;

    //!
    //! \brief setMd5
    //! \param value
    //!
    void setMd5(const QByteArray &value);

    //!
    //! \brief notify
    //! \param payload
    //!
    void notify(const QVariant&payload);

    //!
    //! \brief notify
    //! \param channel
    //! \param payload
    //!
    static void notify(const QString &channel, const QVariant&payload);

private:
    void*p=nullptr;
};

//static auto&NotifyApp=Notify::instance();
}
