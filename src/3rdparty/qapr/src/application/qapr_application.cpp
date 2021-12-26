#include "./qapr_application.h"
#include "./private/p_qapr_application.h"
#include <QProcess>
#include <QJsonDocument>
#include <QJsonArray>

namespace QApr {

struct PSInfo{
public:
    QVariant USER,PID,CPU_percent, MEM_percent, VSZ, RSS , TTY , STAT, START;
};

struct ConstsApplicationBase{
    QRpc::ServiceSetting circuit_breaker;
    void init(){
        auto&manager=QApr::Application::instance().manager();
        circuit_breaker=manager.setting(qsl("circuit-breaker"));
    }
};

static ConstsApplicationBase*____constsApplicationBase=nullptr;

static Application*____instance=nullptr;

static void init(Application&i){
#ifdef QT_DEBUG
    i.resourceExtract();
#endif
    auto settingFile=i.settings_SERVER();
    auto&manager=i.manager();
    manager.load(settingFile);
    ____constsApplicationBase=new ConstsApplicationBase();
    ____constsApplicationBase->init();
    auto&cnn=i.connectionManager();
    if(!cnn.isLoaded())
        sWarning()<<qtr("Connection manager is not loaded");
}

static void init(){
    if(____instance==nullptr){
        static QMutex ____instance_mutex;
        QMutexLocker locker(&____instance_mutex);/*garantia de unica instancia*/
        if(____instance==nullptr){
            ____instance=new Application(nullptr);
            init(*____instance);
        }
    }
}

Q_COREAPP_STARTUP_FUNCTION(init)

Application::Application(QObject *parent) : QObject(parent)
{
    this->p=new ApplicationPvt(this);
}

Application::~Application()
{
    if(this==&this->instance())
        ____instance=nullptr;
    dPvt();
    delete&p;
}

QVariant Application::settings_SERVER()const
{
    dPvt();
    auto vList=p.settings_SERVER();
    return vList;
}

QRpc::ServiceManager &Application::manager()
{
    dPvt();
    return p.manager;
}

int Application::exec(QCoreApplication&a)
{
    dPvt();
    p.circuitBreaker.setSettings(____constsApplicationBase->circuit_breaker.toHash());
    if(p.circuitBreaker.start())
        p.circuitBreaker.print();
    return a.exec();
}

Application &Application::instance()
{
    init();
    return*____instance;
}

Application &Application::i()
{
    return Application::instance();
}

qlonglong Application::memoryUsage()
{
    QProcess process;
    process.start(qsl("cat"), qvsl_null<<qsl("/proc/%1/status").arg(qApp->applicationPid()));
    if(process.waitForStarted(1000)){
        if(!process.waitForFinished(1000)){
            process.terminate();
        }
        else{
            QString bytes=process.readAllStandardOutput().toLower();
            bytes=bytes.replace(qsl("\t"), qsl_null);
            while(bytes.contains(qsl("  ")))
                   bytes=bytes.replace(qsl("  "), qsl_space);
            auto vList=bytes.split(qsl("\n"));
            for(auto&s:vList){
                if(s.contains(qsl_fy(vmpeak))){
                    auto vmRSS=s.split(qsl(":")).last().trimmed().replace(qsl("kb"),qsl_null).trimmed();
                    return vmRSS.toLongLong();
                }
            }
        }
    }
    return 0;
}

const QUuid &Application::instanceUuid()
{
    return appInstanceUuid;
}

QVariantHash &Application::arguments()const
{
    dPvt();
    return p.arguments();
}

Application&Application::printArguments()
{
#if QAPR_LOG
    dPvt();
    QHashIterator<QString, QVariant> i(p.__arguments);
    while (i.hasNext()) {
        i.next();
        sInfo()<<qsl("%1 : %2").arg(i.key(), i.value().toString());
    }
#endif
    return*this;
}

Application &Application::resourceExtract()
{
    dPvt();
    p.resourceExtract();
    return*this;
}

QApr::CircuitBreaker &Application::circuitBreaker()
{
    dPvt();
    return p.circuitBreaker;
}

}
