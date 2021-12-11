#pragma once

#include "./qapr_global.h"
#include "./qstm_message.h"
#include "./qorm_controller.h"
#include "./qrpc_service_setting.h"

namespace QApr {

//!
//! \brief The UtilMessage class
//!
class Q_APR_EXPORT UtilMessage:public QStm::Object
{
public:

    //!
    //! \brief UtilMessage
    //! \param parent
    //!
    Q_INVOKABLE explicit UtilMessage(QObject *parent = nullptr);

    //!
    //! \brief ~UtilMessage
    //!
    Q_INVOKABLE ~UtilMessage();

    //!
    //! \brief send
    //! \param setting
    //! \param serviceType
    //! \param serviceToken
    //! \param to
    //! \param body
    //! \param attachment
    //! \return
    //!
    ResultValue &send(const QRpc::ServiceSetting &setting, const QByteArray &serviceType, const QByteArray &serviceToken, const QString &to, const QString &body, const QVariantList&attachment);

    //!
    //! \brief sendSMS
    //! \param setting
    //! \param serviceToken
    //! \param to
    //! \param body
    //! \return
    //!
    ResultValue &sendSMS(const QRpc::ServiceSetting &setting, const QByteArray &serviceToken, const QString&to, const QString&body);

    //!
    //! \brief sendPushNotify
    //! \param setting
    //! \param serviceToken
    //! \param to
    //! \param body
    //! \return
    //!
    ResultValue &sendPushNotify(const QRpc::ServiceSetting &setting, const QByteArray&serviceToken, const QString&to, const QString&body);

    //!
    //! \brief sendTelegram
    //! \param setting
    //! \param serviceToken
    //! \param to
    //! \param body
    //! \return
    //!
    ResultValue &sendTelegram(const QRpc::ServiceSetting &setting, const QByteArray&serviceToken, const QString&to, const QString&body);

    //!
    //! \brief sendEmail
    //! \param setting
    //! \param serviceToken
    //! \param to
    //! \param body
    //! \return
    //!
    ResultValue &sendEmail(const QRpc::ServiceSetting &setting, const QByteArray &serviceToken, const QString&to, const QString&body);

    //!
    //! \brief sendWhatsApp
    //! \param setting
    //! \param serviceToken
    //! \param to
    //! \param body
    //! \return
    //!
    ResultValue &sendWhatsApp(const QRpc::ServiceSetting &setting, const QByteArray&serviceToken, const QString&to, const QString&body);

    //!
    //! \brief send
    //! \param setting
    //! \param message
    //! \return
    //!
    ResultValue &send(const QRpc::ServiceSetting &setting, const QVariant&message);

    //!
    //! \brief sendSMS
    //! \param setting
    //! \param message
    //! \return
    //!
    ResultValue &sendSMS(const QRpc::ServiceSetting &setting, const QVariant&message);

    //!
    //! \brief sendPushNotify
    //! \param setting
    //! \param message
    //! \return
    //!
    ResultValue &sendPushNotify(const QRpc::ServiceSetting &setting, const QVariant&message);

    //!
    //! \brief sendTelegram
    //! \param setting
    //! \param message
    //! \return
    //!
    ResultValue &sendTelegram(const QRpc::ServiceSetting &setting, const QVariant&message);

    //!
    //! \brief sendEmail
    //! \param setting
    //! \param message
    //! \return
    //!
    ResultValue &sendEmail(const QRpc::ServiceSetting &setting, const QVariant&message);

    //!
    //! \brief sendWhatsApp
    //! \param setting
    //! \param message
    //! \return
    //!
    ResultValue &sendWhatsApp(const QRpc::ServiceSetting &setting, const QVariant&message);

};

}
