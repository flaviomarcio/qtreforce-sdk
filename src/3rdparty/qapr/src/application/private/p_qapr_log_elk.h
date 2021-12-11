#pragma once

#include <QObject>
#include <QJsonDocument>
#include "./qapr_global.h"

namespace QApr {

class Q_APR_EXPORT LogELK : public QThread
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LogELK(QObject *parent = nullptr):QThread(nullptr){
        Q_UNUSED(parent)
    }
    Q_INVOKABLE ~LogELK(){
    }

    void run()override{
        this->exec();
    }
public slots:
    void recebeMessage(const QVariant&v){
        auto msg=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Indented);
    }
};

}
