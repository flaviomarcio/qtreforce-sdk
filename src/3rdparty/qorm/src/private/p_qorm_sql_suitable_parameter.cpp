#include "./p_qorm_sql_suitable_parameter.h"
#include "./p_qorm_sql_suitable_parser_strategy.h"
#include "./qstm_util_variant.h"
#include <QJsonDocument>

#define dPvt()\
    auto&p = *reinterpret_cast<SearchParametersPvt*>(this->p)

#define dPvt2()\
    auto&p = *reinterpret_cast<SearchParamPvt*>(this->p)

class SearchParamPvt{
public:
    explicit SearchParamPvt()
    {
    }

    virtual ~SearchParamPvt()
    {
    }
};

class SearchParametersPvt{
public:
    QVariantList values;
    QList<SearchParam> vList;
    explicit SearchParametersPvt()
    {
    }

    virtual ~SearchParametersPvt()
    {
    }

    void insert(const QVariant &valueA, const QVariant &valueB, const QVariant &valueC, const QVariant &keywordOperator, const QVariant &keywordLogical)
    {
        SearchParam vHash(valueA, valueB, valueC, keywordOperator, keywordLogical);
        if(vHash.isValid())
            this->values<<vHash;
    }

    void remove(const QVariant &searchField)
    {
        Q_UNUSED(searchField)
        this->values.clear();
    }
};


SearchParam::SearchParam(const QVariant &v):QVariantHash(v.toHash())
{
}

SearchParam::SearchParam(const QVariant &valueA, const QVariant &valueB, const QVariant &valueC, const QVariant &keywordOperator, const QVariant &keywordLogical):qvh{{qsl("valueA"),valueA}, {qsl("valueB"),valueB}, {qsl("valueC"),valueC}, {qsl("keywordOperator"), keywordOperator},{qsl("keywordLogical"), keywordLogical}}
{
}

SearchParam::SearchParam(const QVariant &valueA, const QVariant &valueB, const QVariant &keywordOperator, const QVariant &keywordLogical):qvh{{qsl("valueA"),valueA}, {qsl("valueB"),valueB}, {qsl("keywordOperator"), keywordOperator},{qsl("keywordLogical"), keywordLogical}}
{
}

SearchParam::~SearchParam()
{
}

bool SearchParam::isValid()
{
    auto va=this->valueA();
    switch (qTypeId(va)) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    {
        if(!va.toHash().isEmpty())
            return true;
        break;
    }
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    {
        if(!va.toList().isEmpty())
            return true;
        break;
    }
    default:
        break;
    }

    auto vb=this->valueB();
    switch (qTypeId(vb)) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    {
        if(!vb.toHash().isEmpty())
            return true;
        break;
    }
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    {
        if(!vb.toList().isEmpty())
            return true;
        break;
    }
    default:
        break;
    }
    return false;
}

QString SearchParam::key() const
{
    auto va=this->valueA().toString().trimmed();
    auto vb=this->valueB().toString().trimmed();
    if(!va.isEmpty())
        return va;

    if(!vb.isEmpty())
        return vb;

    return qsl_null;
}

QVariant SearchParam::valueA() const
{
    return this->value(qsl("valueA"));
}

QVariant SearchParam::valueB() const
{
    return this->value(qsl("valueB"));
}

QVariant SearchParam::valueC() const
{
    return this->value(qsl("valueC"));
}

QOrm::KeywordOperator SearchParam::keywordOperator() const
{
    auto v = this->value(qsl("keywordOperator"));
    auto i = v.toInt();
    if(QOrm::KeywordOperators.contains(i))
        return QOrm::KeywordOperator(i);
    return QOrm::koEqual;
}

QOrm::KeywordLogical SearchParam::keywordLogical() const
{
    auto v = this->value(qsl("keywordLogical"));
    auto i = QOrm::KeywordLogical(v.toInt());
    switch (i) {
    case QOrm::klAnd:
        return i;
    case QOrm::klOr:
        return i;
    default:
        return QOrm::klAnd;
    }
}

SearchParam SearchParam::from(const QVariant &value)
{
    switch (qTypeId(value)) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    {
        auto vHash=value.toHash();
        if(vHash.contains(qsl("valueA")) || vHash.contains(qsl("valueB"))){
            SearchParam __return(vHash);
            return __return;
        }

        if(vHash.size()==1){
            Q_V_HASH_ITERATOR(vHash){
                i.next();
                SearchParam __return(i.key(), i.value(), QVariant(), QVariant());
                return __return;
            }
        }
        break;
    }
    default:
        break;
    }
    SearchParam __return;
    return __return;
}

SearchParameters::SearchParameters(const QVariant &other):QVariant()
{
    this->p = new SearchParametersPvt();
    dPvt();
    switch (qTypeId(other)) {
    case QMetaType_QVariantList:
    {
        for(auto&v:other.toList()){
            auto s=SearchParam::from(v);
            if(v.isValid())
                p.insert(s.valueA(), s.valueB(), s.valueC(), s.keywordOperator(), s.keywordLogical());
        }
        break;
    }
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    {
        Q_V_HASH_ITERATOR (other.toHash()){
            i.next();
            auto s=SearchParam::from(i.value());
            if(!s.isValid()){
                const auto&k=i.key();
                const auto&v=i.value();

                auto keywordOperator=QOrm::koEqual;
                auto keywordLogical=QOrm::klAnd;

                auto vA=QOrm::SqlParserItem::from(k);
                auto vB=QOrm::SqlParserItem::from(v);

                if(!vA.value().isValid() && !vB.value().isValid())
                    continue;

                if(vA.isValue() && QStmTypesListString.contains(qTypeId(vA.value()))){
                    auto s=vA.value().toString();
                    if(!s.contains(qsl("%")))
                        s+=qsl("%");
                    keywordOperator=QOrm::koLike;
                    vB.setValue(s);
                }

                if(vB.isValue() && QStmTypesListString.contains(qTypeId(vB.value()))){
                    auto s=vB.value().toString();
                    if(!s.contains(qsl("%")))
                        s+=qsl("%");
                    keywordOperator=QOrm::koLike;
                    vB.setValue(s);
                }

                s=SearchParam(vA, vB, keywordOperator, keywordLogical);
            }
            p.insert(s.valueA(), s.valueB(), s.valueC(), s.keywordOperator(), s.keywordLogical());
        }
        break;
    }
    default:
        break;
    }
}

SearchParameters::~SearchParameters()
{
    dPvt();
    delete&p;
}

bool SearchParameters::canRead(const QVariant &v)
{
    this->p = new SearchParametersPvt();
    auto typeId=qTypeId(v);
    switch (typeId) {
    case QMetaType_QVariantList:
    {
        for(auto&v:v.toList()){
            auto s=SearchParam::from(v);
            if(v.isValid())
                return true;
        }
        break;
    }
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    {
        Q_V_HASH_ITERATOR (v.toHash()){
            i.next();
            auto v=i.value().toHash();
            auto s=SearchParam::from(v);
            if(s.isValid())
                return true;

            auto va=QOrm::SqlParserItem::from(s.valueA());
            auto vb=QOrm::SqlParserItem::from(s.valueB());
            auto vc=QOrm::SqlParserItem::from(s.valueC());
            if(va.isValid() || vb.isValid() || vc.isValid())
                return true;
        }
        break;
    }
    default:
        break;
    }
    return false;
}

bool SearchParameters::isEmpty()const
{
    dPvt();
    return p.values.isEmpty();
}

SearchParameters &SearchParameters::operator=(const QVariant &v)
{
    dPvt();
    Q_DECLARE_VU;
    QVariant::clear();
    p.values.clear();
    auto typeId=qTypeId(v);
    switch (typeId) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    {
        auto vList=vu.toList(v);
        for(auto&v:vList) {
            SearchParam param(v.toHash());
            if(param.isValid())
                p.values<<v;
        }
        break;
    }
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    {
        auto vHash=vu.toHash(v);
        Q_V_HASH_ITERATOR (vHash){
            i.next();
            auto v=i.value().toHash();
            SearchParam param(v);
            if(param.isValid()){
                p.values<<i.value();
            }
        }
        break;
    }
    default:
        break;
    }
    return*this;
}

SearchParameters &SearchParameters::operator+=(const QVariant &v)
{
    dPvt();
    Q_DECLARE_VU;
    switch (qTypeId(v)) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    {
        auto vList=vu.toList(v);
        for(auto&v:vList) {
            SearchParam param(v.toHash());
            if(param.isValid())
                p.values<<v;
        }
        return*this;
    }
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    {
        auto vHash=vu.toHash(v);
        Q_V_HASH_ITERATOR (vHash){
            i.next();
            auto v=i.value().toHash();
            SearchParam param(v);
            if(param.isValid()){
                p.values<<i.value();
            }
        }
        return*this;
    }
    default:
        return*this;
    }
}

SearchParameters SearchParameters::from(const QVariantHash &v)
{
    SearchParameters vvm;
    vvm+=v;
    return vvm;
}

SearchParameters SearchParameters::from(const QVariantMap &v)
{
    SearchParameters param;
    param+=v;
    return param;
}

SearchParameters &SearchParameters::insert(const QVariant &valueA, const QVariant &valueB)
{
    dPvt();
    p.insert(valueA, valueB, QVariant(), QVariant(), QVariant());
    return*this;
}

SearchParameters &SearchParameters::insert(const QVariant &valueA, const QVariant &valueB, const QVariant &keywordOperator)
{
    dPvt();
    p.insert(valueA, valueB, QVariant(), keywordOperator, QVariant());
    return*this;
}

SearchParameters &SearchParameters::insert(const QVariant &valueA, const QVariant &valueB, const QVariant&keywordOperator, const QVariant&keywordLogical)
{
    dPvt();
    p.insert(valueA, valueB, QVariant(), keywordOperator, keywordLogical);
    return*this;
}

SearchParameters &SearchParameters::insert(const QVariant &valueA, const QVariant &valueB, const QVariant &valueC, const QVariant &keywordOperator, const QVariant &keywordLogical)
{
    dPvt();
    p.insert(valueA, valueB, valueC, keywordOperator, keywordLogical);
    return*this;
}

QList<SearchParam> SearchParameters::build() const
{
    dPvt();
    p.vList.clear();
    for(auto&i:p.values){
        p.vList << SearchParam::from(i);
    }
    return p.vList;
}

QVariant SearchParameters::buildVariant() const
{
    dPvt();
    p.vList.clear();
    QVariantList vList;
    for(auto&i:p.values){
        auto v=i.toHash();
        p.vList << SearchParam::from(v);
        vList<<v;
    }
    return vList.isEmpty()?QVariant():vList;
}

