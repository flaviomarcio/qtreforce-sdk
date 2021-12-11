#pragma once

#include "./qorm_global.h"
#include "./qorm_object_db.h"
#include <QFileInfoList>
#include <QFileInfo>

namespace QOrm {

//!
//! \brief The ScriptExec class
//!class for execute script on database
class Q_ORM_EXPORT ScriptExec: public QOrm::ObjectDb
{
    Q_OBJECT
public:
    //!
    //! \brief ScriptExec
    //! \param parent
    //!
    Q_INVOKABLE explicit ScriptExec(QObject *parent = nullptr);

    //!
    virtual ~ScriptExec();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!replace all values
    ScriptExec&operator=(const QVariant &v);

    //!
    //! \brief operator =
    //! \param entryInfoList
    //! \return
    //!
    ScriptExec&operator=(const QFileInfoList &entryInfoList);

    //!
    //! \brief operator <<
    //! \param v
    //! \return
    //!
    ScriptExec&operator<<(const QVariant &v);

    //!
    //! \brief operator <<
    //! \param entryInfoList
    //! \return
    //!
    ScriptExec&operator<<(const QFileInfoList &entryInfoList);

    //!
    //! \brief scriptValues
    //! \return
    //!list of added values
    QVariantList scriptValues()const;

    //!
    //! \brief scriptedValues
    //! \return
    //!list of analyzed values
    const QStringList &scriptedValues();

    //!
    //! \brief exec
    //! \return
    //!execute values on database
    ResultValue&exec();

private:
    void*p=nullptr;
};

}
