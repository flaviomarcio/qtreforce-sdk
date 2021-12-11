#pragma once

#include <QCoreApplication>
#include <QFile>
#include <QTimer>
#include <QDir>
#include <QMutex>
#include "./qapr_application.h"

namespace QApr {

static QString applicationSettingDir;

#define dPvt()\
    auto&p = *reinterpret_cast<ApplicationPvt*>(this->p)

class ApplicationPvt:public QObject{
    Q_OBJECT
public:
    QApr::CircuitBreaker circuitBreaker;
    QVariant _settings_SERVER;
    QVariantHash __arguments;
    QRpc::ServiceManager manager;
    Application*application=nullptr;
    explicit ApplicationPvt(Application*parent=nullptr):QObject(parent),circuitBreaker(parent){
        if(applicationSettingDir.isEmpty())
            applicationSettingDir=qsl("%1/%2").arg(settings_HOME_DIR, qApp->applicationName().toLower());
        this->application=parent;
    }

    QVariant settings_SERVER()
    {
        if(_settings_SERVER.isNull()){
            QStringList vList;
            {
                auto settingsFile=qsl("%1.json").arg(qApp->applicationFilePath());
                if(!QFile::exists(settingsFile))
                    settingsFile=qsl("%1/%2").arg(applicationSettingDir,settings_SERVER_FILE);

                if(QFile::exists(settingsFile))
                    vList<<settingsFile;
            }

            {
                auto settingsFile=qsl("%1/%2/%3.json").arg(settings_HOME_DIR,qAppName(),settings_SERVER_FILE);
                if(QFile::exists(settingsFile))
                    vList<<settingsFile;
            }
            this->_settings_SERVER=vList;
        }
        return this->_settings_SERVER;
    }

    static void resourceExtract()
    {
        QDir dirHome(applicationSettingDir);
        if(!dirHome.exists())
            dirHome.mkpath(applicationSettingDir);

        if(dirHome.exists()){
            QDir dir(qsl(":"));
            dir.setNameFilters(QStringList{qsl("*.json")});
            for(auto&info:dir.entryInfoList()){
                QFile fileSrc(info.filePath());
                QFile fileDst(qsl("%1/%2").arg(applicationSettingDir,info.fileName()));
                if(fileDst.exists())
                    continue;

                if(!fileSrc.open(fileSrc.ReadOnly)){
#if Q_RPC_LOG
                    sWarning()<<qsl("No open file:")<<fileSrc.fileName()<<qsl(", error: ")<<fileSrc.errorString();
#endif

                }
                if(!fileDst.open(fileDst.Truncate | fileDst.Unbuffered | fileDst.WriteOnly)){
#if Q_RPC_LOG
                    sWarning()<<qsl("No open file:")<<fileDst.fileName()<<qsl(", error: ")<<fileDst.errorString();
#endif

                }

                fileDst.write(fileSrc.readAll());
                fileDst.close();
                if(fileDst.isOpen())
                    fileSrc.close();
            }
        }
    }

    QVariantHash&arguments(){
        if(__arguments.isEmpty()){
            for(auto&v:qApp->arguments()){
                auto l=v.split(qsl("="));
                if(l.isEmpty()){
                    continue;
                }

                if(l.size()==1){
                    auto key=l.first();
                    auto value=l.last();
                    __arguments[key]=value;
                }
                else{
                    auto key=l.first().toLower();
                    auto value=l.last();
                    __arguments[key]=value;
                }
            }

            QHashIterator<QString, QVariant> i(manager.arguments());
            while (i.hasNext()) {
                i.next();
                __arguments[i.key()]=i.value();
            }
        }
        return __arguments;
    }
};

}
