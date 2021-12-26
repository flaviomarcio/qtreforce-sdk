#pragma once

#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDebug>
#include <QUuid>
#include <QStringList>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLocale>
#include <QJsonDocument>
#include <gtest/gtest.h>
#include "./qrpc_types.h"
#include "./qrpc_request.h"
#include "./qstm_util_variant.h"
#include "./qapr_server.h"
#include "./qrpc_listen_protocol.h"
#include "./qorm_test.h"

template <class T=QRpc::QRPCRequest>
bool Q_APR_CRUD_CHECK_FUNC(T*request, const QByteArray&method, const QVariant&body)
{
    request->setBody(body);
    auto&response=request->call(QRpc::Get, method);
    EXPECT_TRUE(response.isOk());
    if(!response.isOk())
        return false;
    auto ___hash=response.bodyHash();
    for(auto&property:Q_ORM_CRUD_PROPERTY_LIST){
        if(!___hash.contains(property))
            return false;
    }
    return true;
}

#define Q_APR_CRUD_CHECK(__CLASS__, __REQUEST__, __METHOD__, __BODY__)          \
TEST_F(__CLASS__, crud_##__METHOD__){                                           \
        __REQUEST__(request);                                                   \
        auto __return=Q_APR_CRUD_CHECK_FUNC(&request, #__METHOD__, __BODY__ );  \
        EXPECT_TRUE(__return);                                                  \
}


namespace QApr{
class SDKGoogleTest : public testing::Test{
public:
    explicit SDKGoogleTest(){
        this->clear();
        QLocale::setDefault(QLocale(QLocale::Portuguese, QLocale::Brazil));
    }

    static QApr::Server&service(){
        return QApr::Server::instance();
    }

    virtual bool clear(){
        return true;
    }

    virtual bool serviceStart(){
        return service().start();
    }


    virtual bool serviceStop(){
        return service().stop();

    }

    virtual QStringList arguments(){
        return qApp->arguments();
    }

    static QByteArray toMd5(const QVariant&v){
        QByteArray bytes=QStmTypesListObjects.contains(qTypeId(v))
                               ?
                               QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact)
                               :
                               v.toByteArray();
        return QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
    }

    static QVariant toVar(const QVariant&v){
        return
            QStmTypesListString.contains(qTypeId(v))
                ?
                QJsonDocument::fromJson(v.toByteArray()).toVariant()
                :
                v;
    }

    QByteArray fakeBody(const int maxloop=1){
        QByteArray __return;
        Q_LOOP_LIMIT(maxloop){
            __return.append(QUuid::createUuid().toByteArray());
        }
        return __return;
    };

    static QUuid toUUID(const QVariant&v){
        return VariantUtil().toUuid(v);
    }

    static void SetUpTestCase()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    static void TearDownTestCase()
    {
    }

public:

};

}
