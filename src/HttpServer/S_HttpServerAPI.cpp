#include "S_HttpServerAPI.h"
#include "S_HttpServer_Service.h"

S_HTTP_SERVER_EXPORT bool S_HTTP_SERVER_CALL S_HttpServer_InitMoudle() {
    return true;
}

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_StopMoudle() {
    S_HttpServer_Service::Instance()->handleStop();
}

S_HTTP_SERVER_EXPORT bool S_HTTP_SERVER_CALL S_HttpServer_Listen(std::string &ipAddress, unsigned short port) {
    return S_HttpServer_Service::Instance()->listen(ipAddress, port);
}

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_AddFilePath(const std::string &filePath) {
    S_HttpServer_Service::Instance()->addFilePath(filePath);
}

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_AddHandle(const std::string &url, ReqHandler req_handler) {
    S_HttpServer_Service::Instance()->addHandle(url, req_handler);
}

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_SendResMsg(std::string &connectionId, int status, std::string &body, unsigned version) {
    S_HttpServer_Service::Instance()->sendResMsg(connectionId, (boost::beast::http::status) status, version, body);
}

#ifdef BOOST_IOCONTEXT
S_HTTP_SERVER_EXPORT void  S_HTTP_SERVER_CALL S_HttpServer_GetIOContext(io_context_weak_ptr  &ioContext) {
        ioContext = S_HttpServer_Service::Instance()->_ioContext;
}
#endif