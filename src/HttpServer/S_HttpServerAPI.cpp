#include "S_HttpServerAPI.h"
#include "S_HttpServer_Service.h"

using namespace S_Http;
S_HTTP_SERVER_EXPORT http_server S_HTTP_SERVER_CALL S_HttpServer_Create(boost::asio::io_context &ioc) {
    S_HttpServer_Service::Ptr *service(new S_HttpServer_Service::Ptr(new S_HttpServer_Service(ioc)));
    return (http_server) service;
}

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_Release(http_server ctx) {
    assert(ctx);
    S_HttpServer_Service::Ptr * c = (S_HttpServer_Service::Ptr *)ctx;
    (*c)->handleStop();
    delete (S_HttpServer_Service::Ptr *) ctx;
}

S_HTTP_SERVER_EXPORT bool S_HTTP_SERVER_CALL
S_HttpServer_Listen(http_server ctx, std::string &ipAddress, unsigned short port) {
    assert(ctx);
    S_HttpServer_Service::Ptr * c = (S_HttpServer_Service::Ptr *)ctx;
    return (*c)->listen(ipAddress, port);
}

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL S_HttpServer_AddFilePath(http_server ctx, const std::string &filePath) {
    assert(ctx);
    S_HttpServer_Service::Ptr * c = (S_HttpServer_Service::Ptr *)ctx;
    (*c)->addFilePath(filePath);
}
//using ReqHandler = std::function<void(S_HttpReq_Msg *msg)>;
S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL
S_HttpServer_AddHandle(http_server ctx, const std::string &url, ReqHandler req_handler) {
    assert(ctx);
    S_HttpServer_Service::Ptr * c = (S_HttpServer_Service::Ptr *)ctx;
    (*c)->addHandle(url, req_handler);
}

S_HTTP_SERVER_EXPORT void S_HTTP_SERVER_CALL
S_HttpServer_SendResMsg(http_server ctx, std::string &connectionId, int status, std::string &body, unsigned version) {
    assert(ctx);
    S_HttpServer_Service::Ptr * c = (S_HttpServer_Service::Ptr *)ctx;
    (*c)->sendResMsg(connectionId, (boost::beast::http::status) status, version, body);
}