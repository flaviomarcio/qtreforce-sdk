#include "./qapr_interface_base.h"
#include "./qapr_application.h"

namespace QApr {


#define dPvt()\
    auto&p =*reinterpret_cast<InterfacePvt*>(this->p)

class InterfacePvt{
public:
    QRpc::QRPCController*parent=nullptr;
    explicit InterfacePvt(QRpc::QRPCController*parent){
        this->parent=parent;
    }

    virtual ~InterfacePvt(){
    }
};

InterfaceBase::InterfaceBase(QObject *parent):QRpc::QRPCController(parent)
{
    this->p = new InterfacePvt(this);
}

InterfaceBase::~InterfaceBase()
{
    dPvt();
    delete&p;
}

}
