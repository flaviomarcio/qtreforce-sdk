set(qapr_SRCS
    # cmake-format: sortable
    mvc/qapr_controller_backoffice.cpp
    mvc/qapr_controller.cpp
    services/qapr_agent_base.cpp
    services/qapr_agent.cpp
    services/qapr_notify_base.cpp
    services/qapr_notify_dispatch.cpp
    services/qapr_notify.cpp
    services/qapr_server.cpp
    interfaces/qapr_interface_backoffice.cpp
    interfaces/qapr_interface_base.cpp
    interfaces/qapr_interface.cpp
    interfaces/qapr_menu_object.cpp
    interfaces/qapr_interface_database.cpp
    application/qapr_mainservice.cpp
    application/qapr_global.h
    application/qapr_runnable.h
    application/qapr_circuit_breaker.h
    application/qapr_consts.h
    application/qapr_application.cpp
    application/qapr_log.cpp
    application/private/p_qapr_log.cpp
    application/private/p_qapr_circuit_breaker.cpp
    application/private/p_qapr_log_telegram.h
    application/private/p_qapr_log_elk.h
    application/private/p_qapr_application.h
    sessions/qapr_session.cpp
    sessions/qapr_session_credential.cpp
    util/qapr_util_message.cpp

)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/application)
include_directories(${CMAKE_SOURCE_DIR}/src/interfaces)
include_directories(${CMAKE_SOURCE_DIR}/src/mvc)
include_directories(${CMAKE_SOURCE_DIR}/src/services)
include_directories(${CMAKE_SOURCE_DIR}/src/sessions)
include_directories(${CMAKE_SOURCE_DIR}/src/util)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    add_library(qapr STATIC ${qapr_SRCS})
else()
    add_library(qapr SHARED ${qapr_SRCS})
endif()

target_link_libraries(
    qapr # cmake-format: sortable
)



install(TARGETS qapr
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt/plugins/qapr
)
