# QtReforceSDK

**SDK made in Qt/C++ to support backend and mobile app development.**


## Working architecture

>## Back-end and Services support
```mermaid
sequenceDiagram  
participant  QtSDK
participant  QCrossCache
participant  QJsonWebToken
participant  QStm
participant  QOrm  
participant  QRpc
participant  QApr
participant  QtReforceSDK
QtSDK->>QCrossCache: Using pure Qt class
QtSDK->>QJsonWebToken: Using pure Qt class
QtSDK->>QStm: Using pure Qt class
QStm->>QOrm: Using basic class
QStm->>QRpc: Using basic class
QStm->>QApr: Using basic class
QCrossCache->>QOrm: Using cache strategy
QCrossCache->>QRpc: Using cache strategy
QJsonWebToken->>QApr: Using cache strategy
QRpc->>QApr: Using server/request/controllers
QOrm->>QApr: Using MVC strategy

QStm->>QtReforceSDK: Using basic class
QOrm->>QtReforceSDK: Using MVC strategy
QRpc->>QtReforceSDK: Using server/request/controllers
QApr->>QtReforceSDK: Using security
QApr->>QtReforceSDK: Using web controllers
QApr->>QtReforceSDK: Using mvc controllers
```
>## Mobile support
```mermaid
sequenceDiagram  
participant  QtSDK
participant  QStm 
participant  QRpc
participant  QMetaUi
participant  QtReforceSDK
QtSDK->>QStm: Using pure Qt class
QtSDK->>QRpc: Using pure Qt class
QtSDK->>QMetaUi: Using pure Qt class
QStm->>QRpc: Using basic class
QStm->>QMetaUi: Using basic class
QStm->>QtReforceSDK: Using basic class
QRpc->>QtReforceSDK: Using request class
QMetaUi->>QtReforceSDK: Using QML Controls
QMetaUi->>QtReforceSDK: Using security
QMetaUi->>QtReforceSDK: Using request
```

## Prerequisits
>```bash
> mkdir -p myproject/3rdparty;
> cd myproject/3rdparty;
> 
> git clone git@github.com:flaviomarcio/qtreforce-sdk.git
> //or
> git submodule add git@github.com:flaviomarcio/qtreforce-sdk.git
> 
> cd myproject/3rdparty/qtreforce-sdk;
> ./initrepository
>```


## CMake Build information

>```
>## initial CMake parameters 
>
>-GNinja
>-DCMAKE_BUILD_TYPE:STRING=Debug
>-DCMAKE_PROJECT_INCLUDE_BEFORE:PATH=%{IDE:ResourcePath}/package-manager/auto-setup.cmake
>-DQT_QMAKE_EXECUTABLE:STRING=%{Qt:qmakeExecutable}
>-DCMAKE_PREFIX_PATH:STRING=%{Qt:QT_INSTALL_PREFIX}
>-DCMAKE_C_COMPILER:STRING=%{Compiler:Executable:C}
>-DCMAKE_CXX_COMPILER:STRING=%{Compiler:Executable:Cxx}
>-DCMAKE_INSTALL_PREFIX=~/build/myproject/install/Debug
>```

>```bash
> cd qtreforce-sdk
> mkdir build;
> cd build;
> cmake ..;
> make;
> make install;
>```

## QMake Build information

>```bash
> cd qapr
> qmake qtreforce-sdk.pro
> make;
> make install;
> ls -l;
>```

## Configure QMake project

>```c++
>CONFIG += c++17
>CONFIG += console
>CONFIG += silent
>QT += gui core
>
>TEMPLATE = app
>TARGET = demo
>
>include($$PWD/3rdparty/qtreforce-sdk/qtreforce-sdk.pri)
>
>HEADERS += \
>    $$PWD/controllerMethods.h \
>    $$PWD/personModel.h \
>    $$PWD/personController.h
>
>SOURCES += \
>     $$PWD/controllerMethods.cpp \
>    $$PWD/personController.cpp \
>    $$PWD/main.cpp
>
>RESOURCES += \
>    $$PWD/settings.qrc
>```

## Resource settings for QtReforce QRpc/QOrm
>Settings for webservers and connection database server saved in setting.json and included in settings.qrc
>```json
>{
>   "arguments":["ws"],
>   "protocol":{
>      "default":{
>         "minThreads":1,
>         "maxThreads":2000,
>         "cleanupInterval":1000,
>         "readTimeout":60000,
>         "maxRequestSize":104857600,
>         "maxMultiPartSize":1048576000,
>         "enabled":false,
>         "sslKeyFile":"",
>         "sslCertFile":""
>      },
>      "http":{
>        "enabled":true,"port":[8888]
>      }
>   },
>   "connection":{
>       "secret": "YzUxNDFhMDA5",
>       "enviroment" : "debug",
>       "paramaters" : {
>           "debug":{
>               "driver":"QPSQL",
>               "hostName":"localhost",
>               "userName":"localuser",
>               "password":"localuser",
>               "port":5432,
>               "dataBaseName":"postgres",
>               "schemaNames":"public"
>           }
>       }
>   }
>}
>```


## Using QtReforce

>## Implementation main.cpp
>Check example in QApr/example/application
>```c++
>//main implementation
>
>#include <QtReforce/QApr>
>
>QAPR_MAIN_DECLARE()
>```

## Guide

>## Basic utilities class, SettingManager, MetaObjectUtil, VariantUtil, FormattingUtil, DoubleUtil, DateUtil, 
>Check documentation and examples
>https://github.com/flaviomarcio/qstm
>
>## Using web-servers controls
>Check documentation and examples
>https://github.com/flaviomarcio/qrpc
>
>## Using MVC controls
>Check documentation and examples
>https://github.com/flaviomarcio/qorm
>
>## Using back-end and services using web-server's and MVC
>Check documentation and examples
>https://github.com/flaviomarcio/qapr
>
>## Using cache strategy's
>Check documentation and examples
>https://github.com/flaviomarcio/qcrosscache
>
>## Using QML/class to create mobile application
>Check documentation and examples
>https://github.com/flaviomarcio/qmetaui