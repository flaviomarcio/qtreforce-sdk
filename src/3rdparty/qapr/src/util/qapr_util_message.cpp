#include "./qapr_util_message.h"
#include "./qapr_application.h"
#include "./qstm_message.h"
#include "./qrpc_request.h"

namespace QApr {

//enum MessageType{dsMail=1, dsSms=2, dsPushNotification=4, dsTelegram=8, dsWhatsApp=16};


static bool sendMessage(const QRpc::ServiceSetting &setting, const QVariant&vMsg){

    QRpc::QRPCRequest request;
    request=setting;
    QVariantHash map;
    QStm::Message message(vMsg);
    map.insert(qsl("uuid"),message.uuid().toByteArray());
    map.insert(qsl("type"),message.typeId());
    map.insert(qsl("from"),message.from());
    map.insert(qsl("to"),message.to());
    map.insert(qsl("subject"),message.subject());
    if(!message.bodyHtml().isEmpty())
        map.insert(qsl("payload"), message.bodyHtml());
    else if (!message.bodyText().isEmpty())
        map.insert(qsl("payload"), message.bodyText());

    if(!message.attachment().isEmpty()){
        QVariantList attachment;
        for(auto&v:message.attachment()){
            QVariantMap vMap;
            Url url(v);
            vMap[qsl("name")]=url.name();
            vMap[qsl("body")]=url.readBody().toHex();
            attachment<<vMap;
        }

        map.insert(qsl("attachment"), attachment);
    }
    auto&response=request.call(qsl("v1/message/send"),map);
#if QAPR_LOG
    if(!response.isOk()){
        setting.print();
        request.header().print();
    }
#endif
    return response.isOk();
}

static bool sendMessage(const QRpc::ServiceSetting &setting, const QByteArray&serviceToken, const QString&type, const QString&to, const QString&payload, const QVariantList&attachment, QVariant&responseBody){
    auto base=qsl("%1%2").arg(__PRETTY_FUNCTION__, QDateTime::currentDateTime().toString()).toUtf8();
    auto uuid=QUuid::createUuidV3(QUuid::createUuid(),base);
    QRpc::QRPCRequest request;
    request=setting;
    if(!serviceToken.trimmed().isEmpty())
        request.header().setAuthorization(QRpc::Service, serviceToken);
    QVariantHash map;
    map.insert(qsl("uuid"),uuid);
    map.insert(qsl("type"),type);
    map.insert(qsl("to"),to);
    map.insert(qsl("payload"), payload);
    map.insert(qsl("attachment"), attachment);
    auto&response=request.call(qsl("v1/message/send"),map);
#if QAPR_LOG
    if(!response.isOk()){
        setting.print();
        request.header().print();
    }
#endif
    responseBody=response.body();
    return response.isOk();
}


UtilMessage::UtilMessage(QObject *parent) : QStm::Object(parent)
{
}

UtilMessage::~UtilMessage()
{

}

ResultValue &UtilMessage::send(const QRpc::ServiceSetting &setting, const QByteArray &serviceType, const QByteArray &serviceToken, const QString &to, const QString &body, const QVariantList &attachment)
{
    QVariant response;
    if(!sendMessage(setting, serviceType, serviceToken, to, body, attachment, response))
        return this->lr().setCritical("No send sms message");
    else
        return this->lr();
}

ResultValue &UtilMessage::sendSMS(const QRpc::ServiceSetting &setting, const QByteArray &serviceToken, const QString &to, const QString &body)
{
    QVariant response;
    if(!sendMessage(setting, serviceToken, qsl("sms"), to, body, QVariantList(), response))
        return this->lr().setCritical("No send sms message");
    else
        return this->lr();
}

ResultValue &UtilMessage::sendPushNotify(const QRpc::ServiceSetting &setting, const QByteArray &serviceToken, const QString &to, const QString &body)
{
    QVariant response;
    if(!sendMessage(setting, serviceToken, qsl("pushnotification"), to, body, QVariantList(), response))
        return this->lr().setCritical("No send push notification");
    else
        return this->lr();
}

ResultValue &UtilMessage::sendTelegram(const QRpc::ServiceSetting &setting, const QByteArray &serviceToken, const QString &to, const QString &body)
{
    QVariant response;
    if(!sendMessage(setting, serviceToken, qsl("telegram"), to, body, QVariantList(), response))
        return this->lr().setCritical("No send telegram message");
    else
        return this->lr();
}

ResultValue &UtilMessage::sendEmail(const QRpc::ServiceSetting &setting, const QByteArray &serviceToken, const QString &to, const QString &body)
{
    QVariant response;
    if(!sendMessage(setting, serviceToken, qsl("email"), to, body, QVariantList(), response))
        return this->lr().setCritical("No send email");
    else
        return this->lr();
}

ResultValue &UtilMessage::sendWhatsApp(const QRpc::ServiceSetting &setting, const QByteArray &serviceToken, const QString &to, const QString &body)
{
    QVariant response;
    if(!sendMessage(setting, serviceToken, qsl("whatsapp"), to, body, QVariantList(), response))
        return this->lr().setCritical("No send whatsapp message");
    else
        return this->lr();
}

ResultValue &UtilMessage::send(const QRpc::ServiceSetting &setting, const QVariant&message)
{
    if(!sendMessage(setting, message))
        return this->lr().setCritical("No send message");
    else
        return this->lr();
}

ResultValue &UtilMessage::sendSMS(const QRpc::ServiceSetting &setting, const QVariant&message)
{
    QStm::Message msg(message);
    if(!sendMessage(setting, msg.setType(qsl("sms"))))
        return this->lr().setCritical("No send message");
    else
        return this->lr();
}

ResultValue &UtilMessage::sendPushNotify(const QRpc::ServiceSetting &setting, const QVariant&message)
{
    QStm::Message msg(message);
    if(!sendMessage(setting, msg.setType(qsl("PushNotify"))))
        return this->lr().setCritical("No send message");
    else
        return this->lr();
}

ResultValue &UtilMessage::sendTelegram(const QRpc::ServiceSetting &setting, const QVariant&message)
{
    QStm::Message msg(message);
    if(!sendMessage(setting, msg.setType(qsl("telegram"))))
        return this->lr().setCritical("No send message");
    else
        return this->lr();
}

ResultValue &UtilMessage::sendEmail(const QRpc::ServiceSetting &setting, const QVariant&message)
{
    QStm::Message msg(message);
    if(!sendMessage(setting, msg.setType(qsl("email"))))
        return this->lr().setCritical("No send message");
    else
        return this->lr();
}

ResultValue &UtilMessage::sendWhatsApp(const QRpc::ServiceSetting &setting, const QVariant&message)
{
    QStm::Message msg(message);
    if(!sendMessage(setting, msg.setType(qsl("whatsApp"))))
        return this->lr().setCritical("No send message");
    else
        return this->lr();
}

}
