#pragma once

#include <QCoreApplication>

#define QAPR_MAIN_DECLARE()\
int main(int argc, char* argv[])\
{\
    QCoreApplication a(argc, argv);\
    return QApr::MainService(nullptr).exec(a);\
}

namespace QApr{

//!
//! \brief The MainService class
//!
class MainService : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief MainService
    //! \param parent
    //!
    explicit MainService(QObject *parent = nullptr);

    //!
    //! \brief exec
    //! \param a
    //! \return
    //!
    static int exec(QCoreApplication &a);
};

}
