INCLUDE_DIRECTORIES("../include")
INCLUDE_DIRECTORIES("../src/HttpMsg")
INCLUDE_DIRECTORIES("../src/HttpServer")
INCLUDE_DIRECTORIES("../src/Utils")

aux_source_directory(../src/HttpMsg MSG_DIR)
aux_source_directory(../src/HttpServer SERVER_DIR)
aux_source_directory(../src/Utils UTILS_DIR)

if (WIN32)
    ADD_DEFINITIONS("-DS_HTTP_SERVER_USE_STATIC_LIB")
endif (WIN32)

#静态库
add_library(${CMAKE_PROJECT_NAME}Server_static STATIC ${MSG_DIR} ${SERVER_DIR} ${UTILS_DIR})

set_target_properties(${CMAKE_PROJECT_NAME}Server_static PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}Server")
#安装静态库至系统目录
install(TARGETS ${CMAKE_PROJECT_NAME}Server_static ARCHIVE DESTINATION ${INSTALL_PATH_LIB})

add_subdirectory(test)


