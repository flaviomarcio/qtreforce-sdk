#pragma once

#include <QObject>
#include <QCoreApplication>
#include "./qapr_global.h"

namespace QApr {

//!
//! \brief The Runnable class
//!
class Q_APR_EXPORT Runnable : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief a
    //! \return
    //!
    static QCoreApplication&a();

    //!
    //! \brief Runnable
    //! \param parent
    //!
    Q_INVOKABLE explicit Runnable(QObject *parent = nullptr);

    //!
    //! \brief ~Runnable
    //!
    Q_INVOKABLE ~Runnable();

    //!
    //! \brief run
    //! \return
    //!
    virtual int run();

public slots:

    //!
    //! \brief resoucesInitialize
    //! \return
    //!
    Q_INVOKABLE virtual bool resoucesInitialize();

    //!
    //! \brief settingInitialize
    //! \return
    //!
    Q_INVOKABLE virtual bool settingInitialize();

    //!
    //! \brief serviceSecondPlanInitialize
    //! \return
    //!
    Q_INVOKABLE virtual bool serviceSecondPlanInitialize();

    //!
    //! \brief serviceFirstPlanInitialize
    //! \return
    //!
    Q_INVOKABLE virtual bool serviceFirstPlanInitialize();

    //!
    //! \brief serviceGUIInitialize
    //! \return
    //!
    Q_INVOKABLE virtual bool serviceGUIInitialize();

};


}
