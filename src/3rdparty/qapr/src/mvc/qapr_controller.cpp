#include "./qapr_controller.h"
#include "./qapr_interface_database.h"
#include "./qapr_application.h"
#include "./qrpc_controller.h"

namespace QApr {

#define dPvt()\
    auto&p = *reinterpret_cast<ControllerPvt*>(this->p)

class ControllerPvt{
public:
    Controller*parent=nullptr;
    InterfaceDatabase*request_=nullptr;
    QVariantHash accountModel;
    explicit ControllerPvt(Controller*parent){
        this->parent=parent;
    }
    virtual ~ControllerPvt(){
    }

    InterfaceDatabase*request(){
        if(this->request_==nullptr){
            QObject*__parent=this->parent;
            while(__parent!=nullptr){
                if(__parent->metaObject()->inherits(&InterfaceBase::staticMetaObject)){
                    request_=dynamic_cast<InterfaceDatabase*>(__parent);
                    if(request_!=nullptr)
                        break;
                }
                __parent=__parent->parent();
            }
        }
        return this->request_;
    }
};

Controller::Controller(QObject *parent) : QOrm::Controller(parent)
{
    this->p=new ControllerPvt(this);
}

Controller::~Controller()
{
    dPvt();
    delete&p;
}

const QVariant Controller::resultInfo()
{
    if(this->parent()==nullptr)
        return this->lr().resultVariantInfo();

    auto interface=dynamic_cast<QRpc::QRPCController*>(this->parent());
    if(interface==nullptr)
        return this->lr().resultVariantInfo();

    auto&rq=interface->rq();
    if(this->lr().isNotOk())
        rq.co(this->lr().sc());
    return this->lr().resultVariantInfo();
}

InterfaceDatabase *Controller::interfaceRequest()
{
    dPvt();
    return p.request();
}

InterfaceDatabase *Controller::irq()
{
    dPvt();
    return p.request();
}

bool Controller::transactionRollbackForce() const
{
    dPvt();
    if(p.request()==nullptr){
        sWarning()<<tr("Request não identificado");
        return false;
    }
    return p.request()->transactionRollbackForce();
}

void Controller::setTransactionRollbackForce(bool value)
{
    dPvt();
    if(p.request()==nullptr){
        sWarning()<<tr("Request não identificado");
        return;
    }
    p.request()->setTransactionRollbackForce(value);
}

}
