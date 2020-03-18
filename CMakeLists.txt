project(S_Http)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")
set(BUILD_USE_64BITS on)
set(platform x64)

set(LINK_LIB_LIST)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(THIRDPARTY "/home/vmns/thirdparty/Linux")
    set(BOOST_DATE_TIME_LIB libboost_date_time.a)
    set(BOOST_THREAD_LIB libboost_thread.a)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(THIRDPARTY "D:/work/projects/Thirdparty")
    set(BOOST_DATE_TIME_LIB libboost_date_time-vc141-mt-s-x64-1_72.lib)
    set(BOOST_THREAD_LIB libboost_thread-vc141-mt-s-x64-1_72.lib)
    set(SSL_LIB libssl64MT.lib)
    set(CRYPTO_LIB libcrypto64MT.lib)
endif ()

#加载自定义模块
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#设置库文件路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#设置可执行程序路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#设置子目录

#安装目录
set(INSTALL_PATH_LIB ${THIRDPARTY}/${CMAKE_PROJECT_NAME}/lib/${platform})
set(INSTALL_PATH_INCLUDE ${THIRDPARTY}/${CMAKE_PROJECT_NAME}/include)

#安装头文件至系统目录
install(DIRECTORY src DESTINATION ${INSTALL_PATH_INCLUDE} FILES_MATCHING PATTERN "*.h")

#boost
set(BOOST_ROOT_PATH ${THIRDPARTY}/boost)
set(BOOST_INCLUDE_PATH ${BOOST_ROOT_PATH}/include)
set(BOOST_LIB_PATH ${BOOST_ROOT_PATH}/lib/${platform})
INCLUDE_DIRECTORIES(${BOOST_INCLUDE_PATH})
link_directories(${BOOST_LIB_PATH})
list(APPEND LINK_LIB_LIST ${BOOST_DATE_TIME_LIB} ${BOOST_THREAD_LIB})

#ssl
if (WIN32)
set(SSL_ROOT_PATH ${THIRDPARTY}/openssl)
set(SSL_INCLUDE_PATH ${SSL_ROOT_PATH}/include)
set(SSL_LIB_PATH ${SSL_ROOT_PATH}/lib/${platform}/VC/static)
INCLUDE_DIRECTORIES(${SSL_INCLUDE_PATH})
link_directories(${SSL_LIB_PATH})
list(APPEND LINK_LIB_LIST ${SSL_LIB} ${CRYPTO_LIB})
endif (WIN32)

##log4cplus
#set(LOG_ROOT_PATH "${THIRDPARTY}/log4cplus")
#set(LOG_INCLUDE_PATH "${LOG_ROOT_PATH}/include")
#set(LOG_LIB_PATH "${LOG_ROOT_PATH}/lib")
#if (WIN32)
#set(LOG_LIB_PATH "${LOG_ROOT_PATH}/lib/x64")
#endif (WIN32)
#set(LOG_LIB "${LOG_LIB_PATH}/${LOG_LIB}")
#INCLUDE_DIRECTORIES("${LOG_INCLUDE_PATH}")

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} /MTd /Od /ZI")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} /MT /O2")
else (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fpermissive")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")
endif (WIN32)

if (WIN32)
    #DLL
    #ADD_DEFINITIONS("-DS_HTTP_SERVICE_DLL")
    #ADD_DEFINITIONS("-DS_HTTP_SERVICE_API_IMPORTS")
    ADD_DEFINITIONS("-DWIN32_LEAN_AND_MEAN")
endif (WIN32)

add_subdirectory(httpClient)
add_subdirectory(httpServer)
