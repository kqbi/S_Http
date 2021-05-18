/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_MainSession
//!	Generated Date	: Tue, 24, Sep 2019  
	File Path	: ../../src/HttpServerTest/S_HttpServer_MainSession.h
*********************************************************************/

#ifndef HttpServerTest_S_HttpServer_MainSession_H
#define HttpServerTest_S_HttpServer_MainSession_H

#include "S_HttpServerAPI.h"
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <unordered_map>
#include <mutex>

//## package HttpServerTest

//## class S_HttpServer_MainSession
class S_HttpServer {
    ////    Constructors and destructors    ////

public :

    //## operation S_HttpServer_MainSession()
    S_HttpServer(boost::asio::io_context &ioc);

    ~S_HttpServer();

    ////    Operations    ////

    //## operation init()
    void init(std::string &filePath);

    //## operation listen(unsigned short)
    bool listen(std::string ip, unsigned short port);

    ////    Additional operations    ////

    void stop();

public :

    ////    Relations and components    ////

    http_server _httpServer;
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpServerTest/S_HttpServer_MainSession.h
*********************************************************************/
