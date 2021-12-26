#include "./qapr_server.h"
#include "./qapr_application.h"
#include <QCoreApplication>
#include <QFile>
#include <QMutex>

namespace QApr {

#define dPvt()\
    auto&p = *reinterpret_cast<ServerPvt*>(this->p)

class ServerPvt{
public:
    explicit ServerPvt(Server*parent=nullptr){
        Q_UNUSED(parent)
    }
    virtual ~ServerPvt(){
    }
};

Server::Server(QObject *parent) : QRpc::QRPCServer(Application::instance().settings_SERVER(), parent)
{
    this->p=new ServerPvt(this);
}

Server::~Server()
{
    dPvt();
    delete&p;
}

const QVariant Server::settings_SERVER()
{
    return QApr::Application::instance().settings_SERVER();
}

}
