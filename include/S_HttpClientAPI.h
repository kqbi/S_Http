#ifndef SHTTPCLIENTSERVICESDK_H
#define SHTTPCLIENTSERVICESDK_H

#include "S_Http_Msg.h"

#ifdef BOOST_IOCONTEXT
#include <boost/asio/io_context.hpp>
#include <boost/shared_ptr.hpp>
#include <memory>
#endif

#if defined( _WIN32 ) || defined( __MINGW32__ )
#   if defined( S_HTTP_CLIENT_EXPORTS )
#       define S_HTTP_CLIENT_EXPORT __declspec(dllexport)
#       define S_HTTP_CLIENT_CALL __stdcall
#   elif defined( S_HTTP_CLIENT_USE_DLL_IMPORT ) || !defined( S_HTTP_CLIENT_USE_STATIC_LIB )
#       define S_HTTP_CLIENT_EXPORT __declspec(dllimport)
#       define S_HTTP_CLIENT_CALL __stdcall
#   else
#       define S_HTTP_CLIENT_EXPORT
#       define S_HTTP_CLIENT_CALL
#   endif
#elif defined(__linux__) || defined(__APPLE__) //linux
#   define S_HTTP_CLIENT_EXPORT
#   define S_HTTP_CLIENT_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BOOST_IOCONTEXT
typedef std::shared_ptr<boost::asio::io_context> io_context_ptr;
typedef std::weak_ptr<boost::asio::io_context> io_context_weak_ptr;
#endif

typedef void (*LogFnCallback)(std::string &msg);

S_HTTP_CLIENT_EXPORT bool S_HTTP_CLIENT_CALL S_HttpClient_InitMoudle(LogFnCallback callback = 0);

S_HTTP_CLIENT_EXPORT void S_HTTP_CLIENT_CALL S_HttpClient_StopMoudle();

S_HTTP_CLIENT_EXPORT void S_HTTP_CLIENT_CALL S_HttpClient_Run();

typedef void (*READFROMSERVER)(void *pUser, S_Http_Msg *msg);
S_HTTP_CLIENT_EXPORT void S_HTTP_CLIENT_CALL
S_HttpClient_SendReqMsg(void *pUser, READFROMSERVER readFromServer, int &method, std::string &target, std::string &host,
                        std::string &port, std::string contentType = "", std::string body = "", bool ssl = false, unsigned version = 11,
                        bool keepAlive = true, std::string basicAuth = "");

#ifdef BOOST_IOCONTEXT
S_HTTP_CLIENT_EXPORT void  S_HTTP_CLIENT_CALL S_HttpClient_GetIOContext(io_context_weak_ptr  &ioContext);
#endif

#ifdef __cplusplus
}
#endif

#endif // SHTTPCLIENTSERVICESDK_H
