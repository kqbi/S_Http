/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_MainSession
//!	Generated Date	: Tue, 24, Sep 2019  
	File Path	: ../../src/HttpServerTest/S_HttpServer_MainSession.cpp
*********************************************************************/

#include "S_HttpServer.h"
#include "S_HttpReq_Msg.h"
//## package HttpServerTest

//## class S_HttpServer_MainSession

S_HttpServer::S_HttpServer(boost::asio::io_context &ioc) : _httpServer(0) {
    //#[ operation S_HttpServer_MainSession()
    _httpServer = S_HttpServer_Create(ioc);
    //#]
}

S_HttpServer::~S_HttpServer() {
}


void S_HttpServer::init(std::string &filePath) {
    //#[ operation init()
    S_HttpServer_AddFilePath(_httpServer, filePath);
    S_HttpServer_AddHandle(_httpServer, "/hello", [&](S_HttpReq_Msg *req) {
        std::string body = "hello s_http";
        S_HttpServer_SendResMsg(_httpServer, req->_connectionId, 200, body);
        delete req;
    });
    //#]
}

bool S_HttpServer::listen(std::string ip, unsigned short port) {
    //#[ operation listen(unsigned short)
    return S_HttpServer_Listen(_httpServer, ip, port);
    //#]
}

void S_HttpServer::stop() {
    S_HttpServer_Release(_httpServer);
}

/*********************************************************************
	File Path	: ../../src/HttpServerTest/S_HttpServer_MainSession.cpp
*********************************************************************/
