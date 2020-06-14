#ifndef SHTTPCLIENTSERVICESDK_H
#define SHTTPCLIENTSERVICESDK_H

#include "S_Http_Msg.h"
#include <boost/asio/io_context.hpp>
using namespace S_Http;
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
typedef void *http_client;

S_HTTP_CLIENT_EXPORT http_client S_HTTP_CLIENT_CALL S_HttpClient_Create(boost::asio::io_context &ioc);

S_HTTP_CLIENT_EXPORT void S_HTTP_CLIENT_CALL S_HttpClient_Release(http_client ctx);

typedef void (*READFROMSERVER)(void *pUser, S_Http_Msg *msg);
S_HTTP_CLIENT_EXPORT void S_HTTP_CLIENT_CALL
S_HttpClient_SendReqMsg(http_client ctx, void *pUser, READFROMSERVER readFromServer, int &method, std::string &target, std::string &host,
                        std::string &port, std::string contentType = "", std::string body = "", bool ssl = false, unsigned version = 11,
                        bool keepAlive = true, std::string basicAuth = "");

#ifdef __cplusplus
}
#endif

#endif // SHTTPCLIENTSERVICESDK_H
