#include "./qapr_session_credential.h"
#include "./qstm_util_variant.h"

#define dPvt()\
        auto&p = *reinterpret_cast<CredentialsPvt*>(this->p)

namespace QApr {

    class CredentialsPvt{
    public:
        SessionCredential*parent=nullptr;
        QUuid uuid;
        QVariantHash permits;
        QVariantHash body;
        explicit CredentialsPvt(SessionCredential*parent){
            this->parent=parent;
        }
    };


    SessionCredential::SessionCredential(QObject *parent) : QObject(parent)
    {
        this->p=new CredentialsPvt(this);
    }

    SessionCredential::~SessionCredential()
    {
        dPvt();
        delete&p;
    }

    QVariantHash SessionCredential::toVariant() const
    {
        QVariantHash vHash;
        vHash[qsl_fy(session_uuid)]=this->session_uuid();
        vHash[qsl_fy(account_uuid)]=this->account_uuid();
        vHash[qsl_fy(profile)]=this->profile();
        vHash[qsl_fy(session)]=this->session();
        vHash[qsl_fy(permits)]=this->permits();
        return vHash;
    }

    bool SessionCredential::isValid() const
    {
        auto&credentials=*this;
        if(!credentials.service_uuid().isNull())
            return true;

        if(!credentials.account_uuid().isNull() && !credentials.session_uuid().isNull())
            return true;

        return false;
    }

    QVariantHash&SessionCredential::permits()const
    {
        dPvt();
        return p.permits;
    }

    SessionCredential&SessionCredential::setPermits(const QVariantHash &permits)
    {
        dPvt();
        p.permits = permits;
        return*this;
    }

    QUuid&SessionCredential::uuid() const
    {
        dPvt();
        return p.uuid;
    }

    SessionCredential&SessionCredential::setUuid(const QUuid &value)
    {
        dPvt();
        p.uuid = value;
        return*this;
    }

    QUuid SessionCredential::domain_uuid() const
    {
        dPvt();
        Q_DECLARE_VU;
        return p.body[qsl_fy(domain_uuid)].toUuid();
    }

    SessionCredential &SessionCredential::set_domain_uuid(const QVariant &uuid)
    {
        dPvt();
        Q_DECLARE_VU;
        p.body[qsl_fy(domain_uuid)]=vu.toUuid(uuid);
        return*this;
    }

    QUuid SessionCredential::account_uuid() const
    {
        dPvt();
        Q_DECLARE_VU;
        return p.body.value(qsl_fy(account_uuid)).toUuid();
    }

    SessionCredential &SessionCredential::set_account_uuid(const QVariant &uuid)
    {
        dPvt();
        Q_DECLARE_VU;
        p.body[qsl_fy(account_uuid)]=vu.toUuid(uuid);
        return*this;
    }

    QUuid SessionCredential::session_uuid() const
    {
        dPvt();
        Q_DECLARE_VU;
        return p.body.value(qsl_fy(session_uuid)).toUuid();
    }

    SessionCredential &SessionCredential::set_session_uuid(const QVariant &uuid)
    {
        dPvt();
        Q_DECLARE_VU;
        p.body[qsl_fy(session_uuid)]=vu.toUuid(uuid);
        return*this;
    }

    QUuid SessionCredential::service_uuid() const
    {
        dPvt();
        Q_DECLARE_VU;
        return p.body.value(qsl_fy(service_uuid)).toUuid();
    }

    SessionCredential &SessionCredential::set_service_uuid(const QVariant &uuid)
    {
        dPvt();
        Q_DECLARE_VU;
        p.body[qsl_fy(service_uuid)]=vu.toUuid(uuid);
        return*this;
    }

    QVariantHash &SessionCredential::body() const
    {
        dPvt();
        return p.body;
    }

    SessionCredential &SessionCredential::setBody(const QVariantHash &value)
    {
        dPvt();
        p.body=value;
        return*this;
    }

    QVariant SessionCredential::profile() const
    {
        dPvt();
        return p.body.value(qsl_fy(profile));
    }

    SessionCredential &SessionCredential::setProfile(const QVariant &value)
    {
        dPvt();
        p.body[qsl_fy(profile)]=value;
        return*this;
    }

    QVariant SessionCredential::session() const
    {
        dPvt();
        return p.body.value(qsl_fy(session));
    }

    SessionCredential &SessionCredential::setSession(const QVariant &value)
    {
        dPvt();
        p.body[qsl_fy(session)]=value;
        return*this;
    }

    QVariant SessionCredential::token() const
    {
        dPvt();
        return p.body.value(qsl_fy(token));
    }

    SessionCredential &SessionCredential::setToken(const QVariant &value)
    {
        dPvt();
        p.body[qsl_fy(token)]=value;
        return*this;
    }








}
