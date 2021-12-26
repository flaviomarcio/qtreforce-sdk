#include "./qapr_runnable.h"
#include <QProcess>

namespace QApr {

    QCoreApplication &Runnable::a()
    {
        return*QCoreApplication::instance();
    }

    Runnable::Runnable(QObject *parent):QObject(parent)
    {
    }

    Runnable::~Runnable()
    {
    }

    int Runnable::run()
    {
        return QProcess::NormalExit;
    }

    bool Runnable::resoucesInitialize()
    {
        return true;
    }

    bool Runnable::settingInitialize()
    {
        return true;
    }

    bool Runnable::serviceSecondPlanInitialize()
    {
        return true;
    }

    bool Runnable::serviceFirstPlanInitialize()
    {
        return true;
    }

    bool Runnable::serviceGUIInitialize()
    {
        return true;
    }

}

