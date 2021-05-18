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

#include "S_HttpClientAPI.h"

//## package HttpClientTest

//## class S_HttpClient_MainSession
class S_HttpClient {
    ////    Constructors and destructors    ////

public :

    S_HttpClient(boost::asio::io_context &ioc);

    //## operation ~S_HttpClient_MainSession()
    ~S_HttpClient();

    ////    Operations    ////

    //## operation sendReqMsg(void*,READFROMSERVER,int&,std::string&,std::string&,std::string&,std::string,std::string,unsigned,bool,std::string)
    void
    sendReqMsg(std::function<void(S_Http_Msg *msg)> readFromServer, int &method, std::string &target, std::string &host,
               std::string &port, std::string contentType = "", std::string body = "", bool ssl = false,
               unsigned version = 11, bool keepAlive = true, std::string basicAuth = "");

    ////    Attributes    ////

    http_client _httpClient;
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpClientTest/S_HttpClient_MainSession.h
*********************************************************************/
