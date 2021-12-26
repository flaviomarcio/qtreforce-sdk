#include "./private/p_qapr_log.h"

namespace QApr {


static void qtMessageHandlerCustomized(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const static auto replaceText=QStringList{QT_STRINGIFY(ResultValue&),QT_STRINGIFY(ResultValue&),QT_STRINGIFY(ServerService::),QStringLiteral("\"")};
    auto line = context.line<=0?QTime::currentTime().toString(QStringLiteral("hh:mm:ss")):QString::number(context.line).rightJustified(5,'0');
    auto message=QStringLiteral("#%1-%2:%3").arg(qtMsgTypeMap.value(type),line,msg);
    for(auto&key:replaceText){
        message.replace(key,qsl_null);
    }
    fprintf(stderr, QByteArrayLiteral("%s\n"), message.toUtf8().constData());
}

static void init(){
    QApr::Log::enabled();
}

Q_COREAPP_STARTUP_FUNCTION(init);

Log::Log(QObject *parent) : QObject(parent)
{

}

Log::~Log()
{

}

void Log::enabled()
{
    qSetMessagePattern("[%{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif} %{time yyyy.MM.dd h:mm:ss.zzz t}] | line: %{line} | func: %{function} | %{message}");
    qInstallMessageHandler(qtMessageHandlerCustomized); // Install the handler local
}

void Log::disabled()
{
    qInstallMessageHandler(qtMessageHandlerDefault); // Install the handler local
}

}
