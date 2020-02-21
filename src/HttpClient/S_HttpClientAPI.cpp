#include "S_HttpClientAPI.h"
#include "S_HttpClient_Service.h"

#ifdef __cplusplus
extern "C" {
#endif

bool S_HTTP_CLIENT_CALL S_HttpClient_InitMoudle(LogFnCallback callback) {
    return true;
}

void S_HTTP_CLIENT_CALL S_HttpClient_StopMoudle() {
    S_HttpClient_Service::Instance()->handleStop();
}

void S_HTTP_CLIENT_CALL S_HttpClient_Run() {
    S_HttpClient_Service::Instance()->run();
}

void S_HTTP_CLIENT_CALL S_HttpClient_SendReqMsg(void *pUser, READFROMSERVER readFromServer, int &method, std::string &target,
                                      std::string &host, std::string &port, std::string contentType, std::string body,
                                      unsigned version, bool keepAlive, std::string basicAuth) {
    S_HttpClient_Service::Instance()->sendReqMsg(pUser, readFromServer, method, target, version, keepAlive, host, port,
                                                 contentType, body, basicAuth);
}

#ifdef BOOST_IOCONTEXT
void  S_HTTP_CLIENT_CALL S_HttpClient_GetIOContext(io_context_weak_ptr  &ioContext) {
        ioContext = S_HttpClient_Service::Instance()->_ioContext;
}
#endif

#ifdef __cplusplus
}
#endif