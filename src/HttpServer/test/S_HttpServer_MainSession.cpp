/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_MainSession
//!	Generated Date	: Tue, 24, Sep 2019  
	File Path	: ../../src/HttpServerTest/S_HttpServer_MainSession.cpp
*********************************************************************/

#include "S_HttpServer_MainSession.h"
#include "S_HttpServer_Session.h"
#include <boost/bind.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "S_HttpReq_Msg.h"
//## package HttpServerTest

//## class S_HttpServer_MainSession

void readFromServer(void *pUser, S_Http_Msg *msg) {
    printf("msg:::::::::::::::\n");
    S_HttpServer_MainSession *mainSession = (S_HttpServer_MainSession *) pUser;
    auto stronglf = mainSession->_processTp.lock();
    if (stronglf) {
        boost::asio::post(*stronglf,
                          boost::bind(&S_HttpServer_MainSession::execProcessMsg,
                                      mainSession,
                                      msg));
    } else {
        delete msg;
        msg = 0;
    }
}

S_HttpServer_MainSession::S_HttpServer_MainSession() {
    //#[ operation S_HttpServer_MainSession()
    //#]
}

S_HttpServer_MainSession::~S_HttpServer_MainSession() {
}

void S_HttpServer_MainSession::execProcessMsg(S_Http_Msg *msg) {
    //#[ operation execProcessMsg(S_HTTP_Msg*)
    S_HttpReq_Msg *req = (S_HttpReq_Msg *) msg;
    if (!req->_path.compare("/api/v1/login")) {
        printf("body:%s\n", msg->_body.c_str());
        std::string sessionId = getNewConnectionId();
        S_HttpServer_Session *session = new S_HttpServer_Session(sessionId);
        session->startBehavior();
        session->GEN(evRegiterSuccess);
        addSession(session);
        std::string body = "1234";
        sendResMsg(msg->_connectionId, boost::beast::http::status::ok, msg->_header.version, body);
    } else {
        std::string body = "The resource '" + req->_path + "' was not found.";
        sendResMsg(msg->_connectionId, boost::beast::http::status::not_found, msg->_header.version, body);
    }
    //#]
}

std::string S_HttpServer_MainSession::getNewConnectionId() {
    //#[ operation getNewConnectionId()
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    return boost::uuids::to_string(uuid);
    //#]
}

void S_HttpServer_MainSession::init() {
    //#[ operation init()
    S_HttpServer_InitMoudle();
    //#]
}

bool S_HttpServer_MainSession::listen(unsigned short port) {
    //#[ operation listen(unsigned short)
    std::string ipAddress = "";
    bool ret = S_HttpServer_Listen(ipAddress, port);
    if (ret) {
        S_HttpServer_GetIOContext(_processTp);
    }
    return ret;
    //#]
}

void
S_HttpServer_MainSession::sendResMsg(std::string &connectionId, boost::beast::http::status status, unsigned version,
                                     std::string &body) {
    //#[ operation sendResMsg(std::string&,http::status,unsigned,std::string&)
    S_HttpServer_SendResMsg(connectionId, (int) status, version, body);
    //#]
}

void S_HttpServer_MainSession::addSession(S_HttpServer_Session *p_S_HttpServer_Session) {
    std::lock_guard<std::mutex> lock(_mutex);
    _sessions[p_S_HttpServer_Session->_sessionId] = p_S_HttpServer_Session;
}

void S_HttpServer_MainSession::removeSession(std::string &sessionId) {
    std::lock_guard<std::mutex> lock(_mutex);
    _sessions.erase(sessionId);
}

void S_HttpServer_MainSession::clearSession() {
    std::lock_guard<std::mutex> lock(_mutex);
    auto iter = _sessions.begin();
    while (iter != _sessions.end()) {
        S_HttpServer_Session *session = iter->second;
        if (session) {
            session->destroy();
            _sessions.erase(iter++);
        } else {
            ++iter;
        }
    }
}

void S_HttpServer_MainSession::stop() {
    clearSession();
    S_HttpServer_StopMoudle();
}

/*********************************************************************
	File Path	: ../../src/HttpServerTest/S_HttpServer_MainSession.cpp
*********************************************************************/
