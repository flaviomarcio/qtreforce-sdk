#pragma once


#include "./qapr_menu_object.h"
#include "./qapr_interface_database.h"

namespace QApr {

#define QAPR_DECLARE_IRQ()                                                          \
QApr::Interface*irq(){                                                              \
    if(this->___irq==nullptr){                                                      \
        QObject*__parent=this->parent();                                            \
        while(__parent!=nullptr){                                                   \
            if(__parent->metaObject()->inherits(&Interface::staticMetaObject)){     \
                ___irq=dynamic_cast<QApr::Interface*>(__parent);                    \
                if(___irq!=nullptr){                                                \
                    break;                                                          \
                }                                                                   \
            }                                                                       \
            __parent=__parent->parent();                                            \
        }                                                                           \
    }                                                                               \
    return this->___irq;                                                            \
}                                                                                   \
private:                                                                            \
QApr::Interface*___irq=nullptr;                                                     \
public:                                                                             \
                                                                                    \
/**                                                                                 \
* @brief transactionRollbackForce                                                   \
* @return                                                                           \
*                                                                                   \
* se true mesmo com tudo correto ocorrerá o rollback da transacao                   \
*/                                                                                  \
virtual bool transactionRollbackForce() const                                       \
{                                                                                   \
    dPvt();                                                                         \
    if(this->irq()==nullptr)                                                        \
        sWarning()<<tr("Request não identificado");                                 \
    else                                                                            \
        ->irq()->transactionRollbackForce();                                        \
    return false;                                                                   \
}                                                                                   \
                                                                                    \
virtual void setTransactionRollbackForce(bool value)                                \
{                                                                                   \
    dPvt();                                                                         \
    if(this->irq()==nullptr)                                                        \
        sWarning()<<tr("Request não identificado");                                 \
    else                                                                            \
        this->irq()->setTransactionRollbackForce(value);                            \
}                                                                                   \


//!
//! \brief The Interface class
//!base inicial criada para aplicacoes, contem metodos e verificacao e alguns utilitarios
class Q_APR_EXPORT Interface : public InterfaceDatabase
{
    Q_OBJECT
    Q_DECLARE_OBJECT()
    QRPC_DECLARE_MODULE(qsl_fy(QApr))
    QRPC_DECLARE_DESCRIPTION(qsl_fy(QApr::Interface))
public:
    //!
    //! \brief Interface
    //! \param parent
    //!
    Q_INVOKABLE explicit Interface(QObject *parent = nullptr);

    //!
    //! \brief ~Interface
    //!
    Q_INVOKABLE ~Interface();

    //!
    //! \brief backOfficeMenu
    //! \return
    //!
    Q_INVOKABLE virtual QVariantList backOfficeMenu() const;
};

}
