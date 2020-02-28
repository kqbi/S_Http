#include "S_HttpServerAPI.h"
#include "S_HttpServer_Service.h"

#ifdef __cplusplus
extern "C" {
#endif

bool S_HTTP_SERVER_CALL S_HttpServer_InitMoudle() {
    return true;
}

void S_HTTP_SERVER_CALL S_HttpServer_StopMoudle() {
    S_HttpServer_Service::Instance()->handleStop();
}

bool S_HTTP_SERVER_CALL S_HttpServer_Listen(std::string &ipAddress, unsigned short port) {
    return S_HttpServer_Service::Instance()->listen(ipAddress, port);
}

void S_HTTP_SERVER_CALL S_HttpServer_AddFilePath(const std::string &filePath) {
    S_HttpServer_Service::Instance()->addFilePath(filePath);
}

void S_HTTP_SERVER_CALL S_HttpServer_AddHandle(const std::string &url, ReqHandler req_handler) {
    S_HttpServer_Service::Instance()->addHandle(url, req_handler);
}

void S_HTTP_SERVER_CALL S_HttpServer_SendResMsg(std::string &connectionId, int status, std::string &body, unsigned version) {
    S_HttpServer_Service::Instance()->sendResMsg(connectionId, (boost::beast::http::status) status, version, body);
}

#ifdef BOOST_IOCONTEXT
void  S_HTTP_SERVER_CALL S_HttpServer_GetIOContext(io_context_weak_ptr  &ioContext) {
        ioContext = S_HttpServer_Service::Instance()->_ioContext;
}
#endif

#ifdef __cplusplus
}
#endif