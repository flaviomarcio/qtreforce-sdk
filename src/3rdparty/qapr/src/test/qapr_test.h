#ifndef GOOGLE_TESTE_RPC_TEST_H
#define GOOGLE_TESTE_RPC_TEST_H
#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QStringList>
#include <QLocale>
#include <QTimer>
#include <QDebug>

#include "./appbase_server.h"
#include "./appbase_notify.h"
#include "./appbase_application.h"

#include "../../qrpc/src/qrpc_listen_protocol.h"
#include "../../qrpc/src/qrpc_request.h"
#include "../../qrpc/src/qrpc_types.h"

struct ConstsTest {
    const QString default_enviroment = "local";
    const QString default_protocol = "http";
    const QString default_hostname = "localhost";
    const QString default_route = "/";

    static const int default_port_http=9999;
    static const int default_port_amqp=5672;
    static const int default_port_web =8888;
    static const int default_port_tcp =7777;

    int server_port_http=default_port_http;

    QVariantList products;
    QVariantHash customer;
    QVariantHash atual;

    QVariantHash fileserver_prod;
    QVariantHash customer_prod;

    bool send=false;

    void init(){
       this->configureDefaultMap();
       auto&manager=RPCServerBase::Application::instance().manager();
       variables=manager.setting("test").variables();       
       auto server = variables.value("server").toString().simplified();
       if (server.isEmpty() || (!servers.contains(server))){
           server = "default";
       }
       if (server != "default"){
           configureMap(atual, server );
       } else {
           atual = configDefault;
       }
       products = variables.value("products").toList();
       send = variables.value("send").toBool();
       if (send){
           configureMapProd(customer_prod, "customer");
           configureMapProd(fileserver_prod, "fileserver");
       }
    }

private:
    QVariantHash configDefault;
    QVariantHash variables;
    const QVariantList envs = QVariantList() << "local" << "prod" << "hom";
    const QVariantList servers = QVariantList() << "customer" << "fileserver" << "redirect" << "default";

    void configureDefaultMap(){
        if (configDefault.isEmpty()){
            configDefault.insert("protocol",default_protocol);
            configDefault.insert("hostName",default_hostname);
            configDefault.insert("route",default_route);
            configDefault.insert("port", default_port_http);
            configDefault.insert("enviroment", default_enviroment);
        }
    }

    void configureMap(QVariantHash&map, QString tag){
        map=variables.value(tag).toHash();
        auto enviroment = map.value("enviroment").toString().trimmed();
        enviroment = (enviroment.isEmpty() || !envs.contains(enviroment))? default_enviroment:enviroment;
        if (map.isEmpty() || (!map.contains(enviroment))){
            map= configDefault;
        } else {
            map=map.value(enviroment).toHash();
        }
    }

    void configureMapProd(QVariantHash&map, QString tag){
        map=variables.value(tag).toHash();
        map=map.value("prod").toHash();
    }
};

Q_GLOBAL_STATIC(ConstsTest, __constsTest);

static const auto&constsTest=*__constsTest;

static void initTest(){
   __constsTest->init();
}

Q_COREAPP_STARTUP_FUNCTION(initTest);

class SDKGoogleTest : public testing::Test {
public:

    explicit SDKGoogleTest(){
        QLocale::setDefault(QLocale(QLocale::Portuguese, QLocale::Brazil));
    }

    ~SDKGoogleTest(){
    }

    static RPCServerBase::Server&service(){
        return RPCServerBase::Server::instance();
    }

    static RPCServerBase::Notify&notify(){
        return RPCServerBase::Notify::instance();
    }

    virtual bool serviceStart(){
        return service().start();
    }

    virtual bool notifyStart(){
        return notify().start();
    }

    virtual bool serviceStop(){
        return service().stop();
    }

    virtual bool notifyStop(){
        return notify().stop();
    }

    QStringList arguments(){
        return qApp->arguments();
    }

    static QByteArray toMd5(const QVariant&v){
        QByteArray bytes;
        if(v.type()==QVariant::List || v.type()==QVariant::StringList || v.type()==QVariant::Map || v.type()==QVariant::Hash)
            bytes=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
        else
            bytes=v.toByteArray();
        return VariantUtil().toMd5(bytes);
    }

    static QUuid toUUID(const QVariant&v){
        return VariantUtil().toUuid(v);
    }

    static QVariant toVar(const QVariant&v){
        if(v.type()==QVariant::String || v.type()==QVariant::ByteArray)
            return QJsonDocument::fromJson(v.toByteArray()).toVariant();
        else
            return v;
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
};


#endif // GOOGLE_TESTE_DEMO_H

