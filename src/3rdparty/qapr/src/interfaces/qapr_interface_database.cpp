#include "./qapr_interface_database.h"
#include "./qapr_application.h"
#include "./qapr_application.h"
#include "./qapr_session.h"
#include "./qorm_transaction.h"

namespace QApr {


#define dPvt()\
    auto&p =*reinterpret_cast<InterfaceDatabasePvt*>(this->p)

class InterfaceDatabasePvt{
public:
    bool connectionDb=true;
    bool transactionRollbackForce=false;
    QOrm::Transaction transaction;
    QOrm::ConnectionPool pool;
    QRpc::QRPCController*parent=nullptr;
    Session session;

    explicit InterfaceDatabasePvt(QRpc::QRPCController*parent):
        transaction(parent),
        pool(QApr::Application::i().pool()),
        session(parent)
    {
        this->parent=parent;
    }

    virtual ~InterfaceDatabasePvt(){
        transaction.rollback();
    }

    auto&credentials(){
        return this->session.credential();
    }
};

InterfaceDatabase::InterfaceDatabase(QObject *parent):QApr::InterfaceBase(parent)
{
    this->p = new InterfaceDatabasePvt(this);
}

InterfaceDatabase::~InterfaceDatabase()
{
    dPvt();
    delete&p;
}

Session &InterfaceDatabase::sessionObject()
{
    dPvt();
    return p.session;
}

const SessionCredential &InterfaceDatabase::credential()
{
    dPvt();
    return p.credentials();
}

bool InterfaceDatabase::requestBeforeInvoke()
{
    if(!QApr::InterfaceBase::requestBeforeInvoke())
        return false;


    auto&rq=this->rq();
    if(rq.isMethodOptions())
        return true;

    const auto requestPath=rq.requestPath();
    const auto flg=this->routeFlags(requestPath);
    const auto connection_db_ignore=flg.value(qsl("connection_db_ignore")).toBool();//permitir nao criar conexao
    auto flags_connection_db_transaction=flg.value(qsl("connection_db_transaction")).toBool();//permite criar transacao em qualquer metodo logo get e options nao criam transacao
    if(connection_db_ignore)
        return true;

    dPvt();
    auto&pool=p.pool;

    QSqlDatabase connection;
    if(flags_connection_db_transaction){
        //conexao normal que tera transacao iniciada
        if(!pool.get(connection))
            return false;
    }
    else if(!(rq.isMethodGet() || rq.isMethodOptions())){
        flags_connection_db_transaction=true;
        if(!pool.get(connection))
            return false;
    }
    else{
        if(!pool.getReadOnly(connection))
            return false;
    }

    if(!this->setConnection(connection)){
#ifdef QAPR_LOG
        sWarning()<<qbl("invalid database connection");
#endif
        rq.co().setInternalServerError();
        return false;
    }

    if(!flags_connection_db_transaction){
        return true;
    }

    return p.transaction.transaction();
}

bool InterfaceDatabase::requestAfterInvoke()
{
    if(!QApr::InterfaceBase::requestAfterInvoke())
        return false;

    dPvt();
    auto db=this->connection();
    if(!db.isOpen())
        return false;

    if(p.transactionRollbackForce)
        p.transaction.rollback();//rollback obrigatorio
    else if(this->rq().co().isOK())
        p.transaction.commit();
    else
        p.transaction.rollback();

    db.close();
    p.pool.finish(db);

    return true;
}

bool InterfaceDatabase::connectionDb() const
{
    dPvt();
    return p.connectionDb;
}

void InterfaceDatabase::setConnectionDb(bool value)
{
    dPvt();
    p.connectionDb = value;
}

bool InterfaceDatabase::transactionRollbackForce() const
{
    dPvt();
    return p.transactionRollbackForce;
}

void InterfaceDatabase::setTransactionRollbackForce(bool value)
{
    dPvt();
    p.transactionRollbackForce = value;
}

}
