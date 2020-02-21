/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpClient_Session
//!	Generated Date	: Tue, 24, Sep 2019  
	File Path	: ../../src/HttpClientTest/S_HttpClient_Session.h
*********************************************************************/

#ifndef HttpClientTest_S_HttpClient_Session_H
#define HttpClientTest_S_HttpClient_Session_H

#include <oxf.h>
#include <string>
//## package HttpClientTest

//## class S_HttpClient_Session
class S_HttpClient_Session {
    ////    Constructors and destructors    ////
    
public :

    S_HttpClient_Session();
    
    ~S_HttpClient_Session();
    
    ////    Operations    ////
    
    //## operation sendReqMsg(int&,std::string&,unsigned,bool,std::string&,std::string&,std::string,std::string)
    void sendReqMsg(int& method, std::string& target, unsigned version, bool keepAlive, std::string& host, std::string& port, std::string contentType = "", std::string basicAuth = "");
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpClientTest/S_HttpClient_Session.h
*********************************************************************/
