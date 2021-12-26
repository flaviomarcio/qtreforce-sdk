#include "./qapr_controller_backoffice.h"
#include "./qrpc_controller.h"
#include "./qapr_interface.h"

namespace QApr {

QVector<QApr::Interface*> makeInterfaces(QObject*parent)
{
    QVector<QApr::Interface*> __return;
    auto&staticInterfaceList=QRpc::QRPCController::staticInterfaceList();
    for(auto&v:staticInterfaceList){
        if(!QApr::Interface::staticMetaObject.inherits(v)){
            auto&metaObject=*v;
            auto object=metaObject.newInstance(Q_ARG(QObject*, parent));
            if(object!=nullptr){
                auto parser=dynamic_cast<QApr::Interface*>(object);
                if(parser==nullptr)
                    delete object;
                else
                    __return<<parser;
            }
        }
    }
    return __return;
}

static QVariantList&menuMaker(ControllerBackOffice*parent){
    static QVariantList rootMenuMaked;
    if(rootMenuMaked.isEmpty()){
        QHash<QString,QVariant> cacheMenu;
        auto makedInterfaces = makeInterfaces(parent);
        for(auto&v:makedInterfaces){
            auto vMenuList=v->backOfficeMenu();
            if(vMenuList.isEmpty())
                continue;
            else{
                for(auto&v:vMenuList){
                    MenuObject menu(v);
                    auto name=menu.text();
                    if(menu.isEmpty())
                        continue;
                    else if(!cacheMenu.contains(name))
                        cacheMenu[name]=menu.build();
                    else{
                        MenuObject menuRoot(cacheMenu[name]);
                        for(auto&v:menu.menu()){
                            MenuObject menuItem(v);
                            auto vMenu=v.toMap();
                            if(vMenu.isEmpty())
                                continue;
                            else
                                menuRoot.menu(v);
                        }
                        cacheMenu[name]=menuRoot.build();
                    }
                }
            }
        }
        qDeleteAll(makedInterfaces);
        auto keys=cacheMenu.keys();
        keys.sort();
        for(auto&k:keys){
            MenuObject menu(cacheMenu[k]);
            rootMenuMaked<<menu.build();
        }
    }
    return rootMenuMaked;
}


ControllerBackOffice::ControllerBackOffice(QObject *parent) : QApr::Controller(parent)
{
}

ControllerBackOffice::~ControllerBackOffice()
{
}

ResultValue &ControllerBackOffice::sessionAccount()
{
    auto&credential=this->irq()->sessionObject().credential();
    auto vHash=credential.toVariant();
    return this->lr(vHash);
}

ResultValue &ControllerBackOffice::rootObject()
{
    QVariantHash vHash;
    vHash[qsl_fy(sessionAccount)]=this->sessionAccount().resultVariant();
    vHash[qsl_fy(menu)]=menuMaker(this);
    vHash[qsl_fy(enviroment)]=this->enviroment().resultVariant();
    return this->lr(vHash);
}

ResultValue &ControllerBackOffice::menuInfo(const QVariant &body)
{
    Q_UNUSED(body)
//    Q_DECLARE_VU;
//    auto vBody=vu.toHash(body);
//    auto uuid=vu.toUuid(vBody[qsl_fy(uuid)]);
//    auto name=vBody[qsl_fy(name)].toString();
//    Q_UNUSED(uuid)
//    Q_UNUSED(name)
    return this->lr(qvh_null);
}

ResultValue &ControllerBackOffice::enviroment()
{
//    QVariantHash vMap;
//    //--**--////--**--////--**--////--**--////--**--////--**--////--**--////--**--//
//    vMap[qsl("colors")]=QVariant();
//    vMap[qsl("captions")]=QVariant();
//    vMap[qsl("images")]=QVariant();
//    return this->lr(vMap);
    return this->lr(qvh_null);
}

}
