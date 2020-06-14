#ifndef SHTTPSERVICESDK_H
#define SHTTPSERVICESDK_H

#include "S_HttpReq_Msg.h"
#include <boost/asio/io_context.hpp>
#include <memory>
using namespace S_Http;
#if defined( _WIN32 ) || defined( __MINGW32__ )
#   if defined( S_HTTP_SERVER_EXPORTS )
#       define S_HTTP_SERVER_EXPORT __declspec(dllexport)
#       define S_HTTP_SERVER_CALL __stdcall
#   elif defined( S_HTTP_SERVER_USE_DLL_IMPORT ) || !defined( S_HTTP_SERVER_USE_STATIC_LIB )
#       define S_HTTP_SERVER_EXPORT __declspec(dllimport)
#       define S_HTTP_SERVER_CALL __stdcall
#   else
#       define S_HTTP_SERVER_EXPORT
#       define S_HTTP_SERVER_CALL
#   endif
#elif defined(__linux__) || defined(__APPLE__) //linux
#   define S_HTTP_SERVER_EXPORT
#   define S_HTTP_SERVER_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif
typedef void *http_server;

using ReqHandler = std::function<void (S_HttpReq_Msg *msg)>;

S_HTTP_SERVER_EXPORT http_server S_HTTP_SERVER_CALL S_HttpServer_Create(boost::asio::io_context &ioc);

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_Release(http_server ctx);

S_HTTP_SERVER_EXPORT bool S_HTTP_SERVER_CALL S_HttpServer_Listen(http_server ctx, std::string &ipAddress, unsigned short port);

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_AddFilePath(http_server ctx, const std::string &filePath);

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_AddHandle(http_server ctx, const std::string &url, ReqHandler req_handler);

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL
S_HttpServer_SendResMsg(http_server ctx, std::string &connectionId, int status, std::string &body, unsigned version = 11);

#ifdef __cplusplus
}
#endif

#endif // SHTTPSERVICESDK_H