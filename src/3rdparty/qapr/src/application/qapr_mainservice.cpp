#include "./qapr_mainservice.h"
#include "./qapr_application.h"
#include "./qapr_server.h"
#include "./qapr_agent.h"
#include "./qapr_notify.h"
#include <QProcess>
#include <QDir>

namespace QApr {

MainService::MainService(QObject *parent):QObject(parent)
{
    QLocale::setDefault(QLocale(QLocale::Portuguese, QLocale::Brazil));
}

int MainService::exec(QCoreApplication &a)
{
    Q_UNUSED(a)
    bool RETURN=false;


    auto&appInstance=Application::instance();


    const auto&arguments = appInstance.arguments();

    if(arguments.contains(qsl("ws"))){
        auto&service = Server::instance();
        service.start();
        RETURN = service.isRunning() || RETURN;
    }

    if(arguments.contains(qsl("agent"))){
        auto&service = Agent::instance();
        service.start();
        RETURN = service.isRunning() || RETURN;
    }

    if(arguments.contains(qsl("notify"))){
        auto&service = Notify::instance();
        service.start();
        RETURN = service.isRunning() || RETURN;
    }

    if(RETURN)
        return appInstance.exec(a);

    return QProcess::NormalExit;
}

}
