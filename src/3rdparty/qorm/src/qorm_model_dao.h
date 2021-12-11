#pragma once

#include "./qorm_model.h"
#include "./private/p_qorm_model_dao.h"

namespace QOrm{

typedef SqlParserConditions<SqlParserCommand> DaoConditions;

//!
//! \brief The ModelDao class
//!
template <class T>
class ModelDao : public PrivateQOrm::ModelDao
{
public:
    //!
    //! \brief ModelDao
    //! \param parent
    //!
    Q_INVOKABLE explicit ModelDao(QObject *parent = nullptr) : PrivateQOrm::ModelDao(parent){
    }

    //!
    //! \brief variantToParameters
    //! \param value
    //! \return
    //!
    QVariant variantToParameters(const QVariant&value)const{
        auto __return=PrivateQOrm::ModelDao::variantToParameters(this->modelRef, value);
        return __return;
    }

    //!
    //! \brief record
    //! \return
    //!
    auto&record(){
        return this->record(QVariant());
    }

    //!
    //! \brief record
    //! \param v
    //! \return
    //!
    auto&record(const QVariant&v){
        Query query(this);
        auto&strategy=query.builder().select();
        strategy.limit(1).fieldsFrom(modelRef);
        QVariant value;
        if(v.isValid()){
            SearchParameters vv(this->variantToParameters(v));
            vv+=this->modelRef.tableDeactivateField();
            value=vv.buildVariant();
        }
        if(value.isValid())
            strategy.where().condition(value);
        if(!query.exec())
            return this->lr(query.lastError());

        if(!query.next())
            return this->lr()=false;

        return this->lr(query.makeRecord(this->modelRef));
    }


    //!
    //! \brief recordList
    //! \return
    //!
    auto&recordList(){
        return this->recordList(QVariant());
    }

    //!
    //! \brief recordList
    //! \param v
    //! \return
    //!
    auto&recordList(const QVariant&v){
        Query query(this);
        auto&strategy=query.builder().select();
        strategy.fieldsFrom(modelRef);
        QVariant value(this->variantToParameters(v));
        if(value.isValid()){
            strategy
                .where()
                .condition(value);
        }
        QHashIterator<QString, QVariant> i(this->modelRef.tableDeactivateField());
        while (i.hasNext()) {
            i.next();
            strategy.where().notEqual(i.key(), i.value());
        }

        for(const auto&v:this->modelRef.tableOrderByField())
            strategy.orderby().f(v);

        if(!query.exec())
            return this->lr(query.lastError());

        return this->lr(query.makeRecordList());
    }

    //!
    //! \brief recordMap
    //! \return
    //!
    auto&recordMap(){
        return this->recordMap(QVariant());
    }

    //!
    //! \brief recordMap
    //! \param v
    //! \return
    //!
    auto&recordMap(const QVariant&v){
        auto tablePk=this->modelRef.tablePk();
        if(tablePk.isEmpty())
            return this->lr(QVariant())=true;

        Query query(this);
        auto&strategy=query.builder().select();
        strategy.fieldsFrom(modelRef);
        QVariant value(this->variantToParameters(v));
        if(value.isValid()){
            strategy
                .where()
                .condition(value);
        }
        QHashIterator<QString, QVariant> i(this->modelRef.tableDeactivateField());
        while (i.hasNext()) {
            i.next();
            strategy.where().notEqual(i.key(), i.value());
        }

        if(!query.exec())
            return this->lr(query.lastError());

        QVariantHash map;
        for(auto&v:query.makeRecordList()){
            QVariantHash vMap(v.toHash());
            QStringList key;
            QObject model;
            for(auto&pkField:tablePk){
                const auto property = modelRef.propertyByFieldName(pkField);
                const auto vMapValue=vMap.value(pkField);
                const auto vType=qTypeId(property);
                if(vType==vMapValue.Invalid || !vMapValue.isValid() || vMapValue.isNull())
                    key<<qsl_null;
                else if(vType==vMapValue.Uuid)
                    key<<vMapValue.toUuid().toString();
                else if(vType==vMapValue.Url)
                    key<<vMapValue.toUrl().toString();
                else
                    key<<vMapValue.toString();
            }
            map.insert(key.join('.'),v);
        }
        return this->lr(QVariant(map));
    }

    //!
    //! \brief exists
    //! \return
    //!
    auto&exists(){
        return this->exists(QVariant());
    }

    //!
    //! \brief exists
    //! \param model
    //! \return
    //!
    auto&exists(T&model){
        auto map=model.toMapPKValues();
        if(map.isEmpty())
            map=model.toMapFKValues();
        return this->exists(map);
    }

    //!
    //! \brief exists
    //! \param v
    //! \return
    //!
    auto&exists(const QVariant&v){
        QOrm::Query query(this);
        auto&strategy=query.builder().select();
        strategy.fromExists(modelRef);

        QVariant value=this->variantToParameters(v);
        if(value.isValid()){
            strategy
                .where()
                .condition(value);
        }

        QHashIterator<QString, QVariant> i(this->modelRef.tableDeactivateField());
        while (i.hasNext()) {
            i.next();
            strategy.where().notEqual(i.key(), i.value());
        }

        if(!query.exec())
            return this->lr(query.lastError());

        if (!query.next())
            return this->lr()=false;

        return this->lr()=true;
    }

    //!
    //! \brief insert
    //! \param value
    //! \return
    //!
    auto&insert(T&value){
        return this->insert(value.toHashModel());
    }

    //!
    //! \brief insert
    //! \param value
    //! \return
    //!
    auto&insert(const QVariant&value){
        if(value.isNull() || !value.isValid())
            return this->lr()=false;

        QVariantList list;
        if(qTypeId(value)==QMetaType_QVariantList){
            for(auto&v:value.toList()){
                T model(v);
                model.autoMakeUuid();
                list<<model.toHashModel();
            }
        }
        else{
            T model(value);
            model.autoMakeUuid();
            list<<model.toHashModel();
        }
        for(auto&v:list){
            QOrm::Query query(this);
            query.builder()
                .insert()
                .destine(modelRef)
                .values(v);
            if(!query.exec())
                return this->lr(query.lastError());
        }
        return this->lr()=true;
    }

    //!
    //! \brief update
    //! \param value
    //! \return
    //!
    auto&update(T&value){
        Q_UNUSED(value)
        return this->update(value.toHashModel());
    }

    //!
    //! \brief update
    //! \param value
    //! \return
    //!
    auto&update(const QVariant&value){
        if(value.isNull() || !value.isValid())
            return this->lr()=false;
        QVariantList list;
        if(qTypeId(value)==QMetaType_QVariantList){
            for(auto&v:value.toList()){
                T model(v);
                list<<model.toHashModel();
            }
        }
        else{
            list<<value;
        }
        for(auto&v:list){
            QOrm::Query query(this);
            query.builder()
                .update()
                .destine(modelRef)
                .values(v);
            if(!query.exec())
                return this->lr(query.lastError());
        }
        return this->lr()=true;
    }

    //!
    //! \brief upsert
    //! \param value
    //! \return
    //!
    auto&upsert(T&value){
        auto map=value.toHashModel();
        if(this->upsert(map)){
            value.readFrom(map);
            return this->lr()=true;
        }
        return this->lr()=false;
    }

    //!
    //! \brief upsert
    //! \param value
    //! \return
    //!
    auto&upsert(const QVariant&value){
        if(value.isNull() || !value.isValid())
            return this->lr()=false;
        QVariantList list;
        if(qTypeId(value)==QMetaType_QVariantList){
            for(auto&v:value.toList()){
                T model(v);
                model.autoMakeUuid();
                list<<model.toHashModel();
            }
        }
        else{
            T model(value);
            model.autoMakeUuid();
            list<<model.toHashModel();
        }
        for(auto&v:list){
            QOrm::Query query(this);
            query.builder()
                .upsert()
                .destine(modelRef)
                .values(v);
            if(!query.exec())
                return this->lr(query.lastError());
        }
        return this->lr()=true;
    }

    //!
    //! \brief deactivate
    //! \param value
    //! \return
    //!
    auto&deactivate(T&value){
        auto map=value.toHashModel();
        if(!value.deactivateSetValues()){
            return this->lr(value.lr())=false;
        }

        if(this->upsert(map)){
            value.readFrom(map);
            return this->lr()=true;
        }

        return this->lr()=false;
    }

    //!
    //! \brief deactivate
    //! \param value
    //! \return
    //!
    auto&deactivate(const QVariant&value){
        QVariantList list;
        if(qTypeId(value)==QMetaType_QVariantList){
            for(auto&v:value.toList()){
                T model(v);
                list<<model.toHashModel();
            }
        }
        else{
            list<<value;
        }
        for(auto&v:list){
            T model(this, v);
            if(!this->deactivate(model))
                return this->lr();
        }
        return this->lr()=true;
    }


    //!
    //! \brief remove
    //! \param model
    //! \return
    //!
    auto&remove(T&model){
        auto map=model.toMapPKValues();
        if(map.isEmpty())
            map=model.toMapFKValues();
        return this->remove(map);
    }

    //!
    //! \brief remove
    //! \param v
    //! \return
    //!
    auto&remove(const QVariant&v){
        Query query(this);
        auto&strategy=query.builder().remove();
        strategy.from(modelRef);
        QVariant value(this->variantToParameters(v));
        if(value.isValid()){
            strategy
                .where()
                .condition(value);
        }
        QHashIterator<QString, QVariant> i(this->modelRef.tableDeactivateField());
        while (i.hasNext()) {
            i.next();
            strategy.where().notEqual(i.key(), i.value());
        }
        if(!query.exec())
            return this->lr(query.lastError());

        return this->lr()=true;
    }

    //!
    //! \brief remove
    //! \return
    //!
    auto&remove(){
        auto list=this->lr().resultList();
        if(list.isEmpty())
            return this->lr()=true;

        for(auto&v:list){
            T model(this, v);
            if(!this->remove(model))
                return this->lr()=false;
        }
        return this->lr()=true;
    }

    //!
    //! \brief reload
    //! \param model
    //! \return
    //!
    auto&reload(T&model){
        auto map=model.toMapPKValues();
        if(map.isEmpty())
            map=model.toMapFKValues();
        return this->reload(model, map);
    }

    //!
    //! \brief reload
    //! \param model
    //! \param v
    //! \return
    //!
    auto&reload(T&model, const QVariant&v){
        auto record = this->record(v).resultVariant();
        if(!record.isValid()){
            model.clear();
            return this->lr()=false;
        }

        if(!model.readFrom(record))
            return this->lr()=false;

        return this->lr(record)=true;
    }

    //!
    //! \brief lock
    //! \param model
    //! \return
    //!
    auto&lock(T&model){
        auto map=model.toMapPKValues();
        if(map.isEmpty())
            map=model.toMapFKValues();
        if(!this->lock(map))
            return this->lr()=false;

        if(!model.readFrom(this->lr()))
            return this->lr()=false;

        if(!model.storedProperty())
            return this->lr()=false;

        return this->lr()=true;

    }

    //!
    //! \brief lock
    //! \param model
    //! \param value
    //! \return
    //!
    auto&lock(T&model, const QVariant&value){
        if(!this->lock(value))
            return this->lr()=false;

        if(!model.readFrom(this->lr()))
            return this->lr()=false;

        if(!model.storedProperty())
            return this->lr()=false;

        return this->lr()=true;
    }

    //!
    //! \brief lock
    //! \param v
    //! \return
    //!
    auto&lock(const QVariant&v){
        Query query(this);
        auto&strategy=query.builder().select();
        strategy.lock().fieldsFrom(modelRef);
        QVariant value(this->variantToParameters(v));
        if(value.isValid()){
            strategy
                .where()
                .condition(value);
        }
        if(!query.exec())
            return this->lr(query.lastError());
        auto vList=query.makeRecordList(this->modelRef);
        if(vList.isEmpty())
            return this->lr()=false;

        return this->lr((vList.size()==1)?vList.first():vList);
    }

    //!
    //! \brief truncateTable
    //! \return
    //!
    auto&truncateTable(){
        Query query(this);
        query
            .builder()
            .structure()
            .truncateTable(this->modelRef);
        if(!query.exec())
            return this->lr(query.lastError());

        if(!query.next())
            return this->lr()=false;

        return this->lr()=true;
    }

    //!
    //! \brief truncateTableCascade
    //! \return
    //!
    auto&truncateTableCascade(){
        Query query(this);
        query
            .builder()
            .structure()
            .truncateTableCascade(this->modelRef);
        if(!query.exec())
            return this->lr(query.lastError());

        if(!query.next())
            return this->lr()=false;

        return this->lr()=true;
    }

    //!
    //! \brief nextVal
    //! \return
    //!
    auto&nextVal(){
        return this->nextVal(this->modelRef.tableSequence());
    }

    //!
    //! \brief nextVal
    //! \param v
    //! \return
    //!
    auto&nextVal(const QVariant&v){
        Query query(this);
        query
            .builder()
            .function()
            .nextVal(v);
        if(!query.exec())
            return this->lr().clear()=query.lastError();
        if(!query.next())
            return this->lr().clear()=false;
        return this->lr(query.value(0));
    }

    //!
    //! \brief values
    //!
    auto values(){
        QVariantList __return;
        auto vListRecord=this->lr().resultList();
        if(!vListRecord.isEmpty()){
            auto tablePk=this->modelRef.tablePkField();
            if(tablePk.size()==1)
                return this->values(tablePk.first());

            for(auto&v:vListRecord){
                auto map=v.toHash();
                QVariantHash record;
                for(auto&v:tablePk){
                    auto vField=SqlParserItem::from(v);
                    auto f_name=vField.name().toString();
                    auto f_value=map.value(f_name);
                    if(!record.contains(f_name))
                        record.insert(f_name, f_value);
                }
                __return.append(record);
            }
        }
        return __return;
    }

    //!
    //! \brief values
    //! \param field
    //!
    auto values(const SqlParserItem&field){
        QVariantList __return;
        auto vListRecord=this->lr().resultList();
        auto vField=SqlParserItem::from(field);
        if(vField.isObject()){
            for(auto&v:vListRecord){
                auto map=v.toHash();;
                auto f_value=map.value(vField.name().toString());
                if(!__return.contains(f_value))
                    __return<<f_value;
            }
        }
        return __return;
    }

    //!
    //! \brief setRecordsValues
    //! \param field
    //! \param values
    //! \return
    //!
    auto&setRecordsValues(const SqlParserItem&field, QVariantList&values){
        values=this->values(field);
        return this->lr();
    }

    //!
    //! \brief setRecords
    //! \param values
    //! \return
    //!
    auto&setRecords(QVariantList&values){
        values=this->lr().resultList();
        return this->lr();
    }

public:
    const QOrm::ModelInfo &modelRef=QOrm::ModelInfo::modelInfo(T::staticMetaObject);
};

}
