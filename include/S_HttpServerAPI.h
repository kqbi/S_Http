#ifndef SHTTPSERVICESDK_H
#define SHTTPSERVICESDK_H

#include "S_HttpReq_Msg.h"
#ifdef BOOST_IOCONTEXT
#include <boost/asio/io_context.hpp>
#include <boost/shared_ptr.hpp>
#include <memory>
#endif

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
#ifdef BOOST_IOCONTEXT
typedef std::shared_ptr<boost::asio::io_context> io_context_ptr;
typedef std::weak_ptr<boost::asio::io_context> io_context_weak_ptr;
#endif

using ReqHandler = std::function<void (S_HttpReq_Msg *msg)>;

S_HTTP_SERVER_EXPORT bool S_HTTP_SERVER_CALL S_HttpServer_InitMoudle();

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_StopMoudle();

S_HTTP_SERVER_EXPORT bool S_HTTP_SERVER_CALL S_HttpServer_Listen(std::string &ipAddress, unsigned short port);

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_AddFilePath(const std::string &filePath);

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_AddHandle(const std::string &url, ReqHandler req_handler);

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL
S_HttpServer_SendResMsg(std::string &connectionId, int status, std::string &body, unsigned version = 11);

#ifdef BOOST_IOCONTEXT
S_HTTP_SERVER_EXPORT void  S_HTTP_SERVER_CALL S_HttpServer_GetIOContext(io_context_weak_ptr  &ioContext);
#endif

#endif // SHTTPSERVICESDK_H

#ifdef __cplusplus
}
#endif
