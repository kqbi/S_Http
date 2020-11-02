#include "S_HttpClientAPI.h"
#include "S_HttpClient_Service.h"

#ifdef __cplusplus
extern "C" {
#endif

http_client S_HTTP_CLIENT_CALL S_HttpClient_Create(boost::asio::io_context &ioc) {
    S_HttpClient_Service* service = new S_HttpClient_Service(ioc);
    return (http_client)service;
}

void S_HTTP_CLIENT_CALL S_HttpClient_Release(http_client ctx) {
    assert(ctx);
    ((S_HttpClient_Service*)ctx)->handleStop();
    delete (S_HttpClient_Service*)ctx;
}

void S_HTTP_CLIENT_CALL S_HttpClient_SendReqMsg(http_client ctx, std::function<void(S_Http_Msg *msg)> readFromServer, int method, std::string &target,
                                      std::string &host, std::string &port, std::string contentType, std::string body, bool ssl,
                                      unsigned version, bool keepAlive, std::string authorization) {
    assert(ctx);
    ((S_HttpClient_Service*)ctx)->sendReqMsg(readFromServer, method, target, version, keepAlive, host, port,
                                                 contentType, body, authorization, ssl);
}

#ifdef __cplusplus
}
#endif