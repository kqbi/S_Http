/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpClient_MainSession
//!	Generated Date	: Fri, 27, Sep 2019  
	File Path	: ../../src/HttpClientTest/S_HttpClient_MainSession.cpp
*********************************************************************/

#include "S_HttpClient.h"
#include "OXFWorkPoller.h"
//## package HttpClientTest

//## class S_HttpClient_MainSession
S_HttpClient::S_HttpClient() : _httpClient(0) {
    _httpClient = S_HttpClient_Create(OXFWorkPollerPool::Instance()._ioc);
}

S_HttpClient::~S_HttpClient() {
    //#[ operation ~S_HttpClient_MainSession()
    S_HttpClient_Release(_httpClient);
    //#]
}

void S_HttpClient::sendReqMsg(void *pUser, READFROMSERVER readFromServer, int &method, std::string &target,
                              std::string &host, std::string &port, std::string contentType, std::string body, bool ssl,
                              unsigned version, bool keepAlive, std::string basicAuth) {
    //#[ operation sendReqMsg(void*,READFROMSERVER,int&,std::string&,std::string&,std::string&,std::string,std::string,unsigned,bool,std::string)
    S_HttpClient_SendReqMsg(_httpClient, pUser, readFromServer, method, target, host, port, contentType, body, ssl, version, keepAlive, basicAuth);
    //#]
}

/*********************************************************************
	File Path	: ../../src/HttpClientTest/S_HttpClient_MainSession.cpp
*********************************************************************/
