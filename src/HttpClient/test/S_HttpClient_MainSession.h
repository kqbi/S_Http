/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpClient_MainSession
//!	Generated Date	: Fri, 27, Sep 2019  
	File Path	: ../../src/HttpClientTest/S_HttpClient_MainSession.h
*********************************************************************/

#ifndef HttpClientTest_S_HttpClient_MainSession_H
#define HttpClientTest_S_HttpClient_MainSession_H

#include <oxf.h>
#include "S_HttpClientAPI.h"
#include <boost/asio.hpp>
class S_Http_Msg;

//## package HttpClientTest

//## class S_HttpClient_MainSession
class S_HttpClient_MainSession {
    ////    Constructors and destructors    ////
    
public :

    S_HttpClient_MainSession();
    
    //## operation ~S_HttpClient_MainSession()
    ~S_HttpClient_MainSession();
    
    ////    Operations    ////
    
    //## operation execProcessMsg(S_Http_Msg*)
    void execProcessMsg(S_Http_Msg* msg);
    
    //## operation init()
    void init();
    
    //## operation sendReqMsg(void*,READFROMSERVER,int&,std::string&,std::string&,std::string&,std::string,std::string,unsigned,bool,std::string)
    void sendReqMsg(void* pUser, READFROMSERVER readFromServer, int& method, std::string& target, std::string& host, std::string& port, std::string contentType = "", std::string body = "", unsigned version = 11, bool keepAlive = true, std::string basicAuth = "");
    
    ////    Attributes    ////

    io_context_weak_ptr _processTp;;		//## attribute _processTp
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpClientTest/S_HttpClient_MainSession.h
*********************************************************************/
