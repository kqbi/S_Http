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

#include <oxf.h>
#include "HttpServerTest.h"
#include <omcollec.h>
#include "S_HttpServerAPI.h"
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <unordered_map>
#include <mutex>

class S_HttpServer_Session;

//## package HttpServerTest

//## class S_HttpServer_MainSession
class S_HttpServer_MainSession {
    ////    Constructors and destructors    ////

public :

    //## operation S_HttpServer_MainSession()
    S_HttpServer_MainSession();

    ~S_HttpServer_MainSession();

    ////    Operations    ////

    //## operation execProcessMsg(S_HTTP_Msg*)
    void execProcessMsg(S_Http_Msg *msg);

    //## operation getNewConnectionId()
    std::string getNewConnectionId();

    //## operation init()
    void init();

    //## operation listen(unsigned short)
    bool listen(unsigned short port);

    //## operation sendResMsg(std::string&,http::status,unsigned,std::string&)
    void sendResMsg(std::string &connectionId, boost::beast::http::status status, unsigned version, std::string &body);

    ////    Additional operations    ////

    void addSession(S_HttpServer_Session *p_S_HttpServer_Session);

    void removeSession(std::string &sessionId);

    void clearSession();

    void stop();

public :

    ////    Relations and components    ////

protected :

    std::unordered_map<std::string, S_HttpServer_Session *> _sessions;

    std::mutex _mutex;

    http_server _httpServer;
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpServerTest/S_HttpServer_MainSession.h
*********************************************************************/
