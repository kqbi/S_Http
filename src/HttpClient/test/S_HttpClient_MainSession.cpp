/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpClient_MainSession
//!	Generated Date	: Fri, 27, Sep 2019  
	File Path	: ../../src/HttpClientTest/S_HttpClient_MainSession.cpp
*********************************************************************/

#include "S_HttpClient_MainSession.h"
#include "S_Http_Msg.h"
#include <iostream>
#include "S_HttpRes_Msg.h"
//## package HttpClientTest

//## class S_HttpClient_MainSession
S_HttpClient_MainSession::S_HttpClient_MainSession() {
}

S_HttpClient_MainSession::~S_HttpClient_MainSession() {
    //#[ operation ~S_HttpClient_MainSession()
   // S_HttpClient_StopMoudle();
    //#]
}

void S_HttpClient_MainSession::execProcessMsg(S_Http_Msg* msg) {
    //#[ operation execProcessMsg(S_Http_Msg*)
    std::cout << "execProcessMsg-----------------" << std::endl;
    S_HttpRes_Msg *res = (S_HttpRes_Msg*)msg;
    #if 0
    std::fstream _h264SendFile("sendH264File.jpeg",std::fstream::out | std::fstream::binary);
    
    
    
    tjhandle handle = NULL;
       int width, height, subsample, colorspace;
       int flags = 0;
       int padding = 1; // 1或4均可，但不能是0
       int ret = 0;
    
       handle = tjInitDecompress();
       tjDecompressHeader3(handle, (const unsigned char *)res->_body.data(), (unsigned long)res->_body.size(), &width, &height, &subsample, &colorspace);
    
       printf("w: %d h: %d subsample: %d color: %d\n", width, height, subsample, colorspace);
    
    
    _h264SendFile.write(res->_body.data(), res->_body.size());
    _h264SendFile.close();
    #endif
    //#]
}

void S_HttpClient_MainSession::init() {
    //#[ operation init()
   // S_HttpClient_InitMoudle();
    //S_HttpClient_Run();
  //  S_HttpClient_GetIOContext(_processTp);
    //#]
}

void S_HttpClient_MainSession::sendReqMsg(void* pUser, READFROMSERVER readFromServer, int& method, std::string& target, std::string& host, std::string& port, std::string contentType, std::string body, bool ssl, unsigned version, bool keepAlive, std::string basicAuth) {
    //#[ operation sendReqMsg(void*,READFROMSERVER,int&,std::string&,std::string&,std::string&,std::string,std::string,unsigned,bool,std::string)
    //S_HttpClient_SendReqMsg(pUser, readFromServer, method, target, host, port, contentType, body, ssl, version, keepAlive, basicAuth);
    //#]
}

/*********************************************************************
	File Path	: ../../src/HttpClientTest/S_HttpClient_MainSession.cpp
*********************************************************************/
