#pragma once

#include <QObject>
#include "./qapr_global.h"

namespace QApr {

//!
//! \brief The Log class
//!
class Q_APR_EXPORT Log : public QObject
{
    Q_OBJECT
public:

    //!
    //! \brief Log
    //! \param parent
    //!
    Q_INVOKABLE explicit Log(QObject *parent = nullptr);

    //!
    //! \brief ~Log
    //!
    Q_INVOKABLE ~Log();

    //!
    //! \brief enabled
    //!
    static void enabled();

    //!
    //! \brief disabled
    //!
    static void disabled();
};

}
