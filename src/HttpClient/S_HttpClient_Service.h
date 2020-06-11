/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpClient_Service
//!	Generated Date	: Fri, 27, Sep 2019  
	File Path	: ../../src/HttpClient/S_HttpClient_Service.h
*********************************************************************/

#ifndef HttpClient_S_HttpClient_Service_H
#define HttpClient_S_HttpClient_Service_H

#include <boost/beast.hpp>
#include <boost/thread.hpp>
#include <S_HttpClient_ConnectionManager.h>
class S_HttpClient_Connect;

class S_Http_Msg;

class S_HttpClient_ConnectBase;

//## package HttpClient

//## class S_HttpClient_Service
class S_HttpClient_Service {
public :

    typedef void (*READFROMSERVER)(void *pUser, S_Http_Msg *msg);
    ////    Constructors and destructors    ////

    //## operation S_HttpClient_Service(std::size_t)
    S_HttpClient_Service(boost::asio::io_context &ioc);

    ~S_HttpClient_Service();

    ////    Operations    ////

    //## operation execProcessMsg(S_Http_Msg*)
    void execProcessMsg(S_Http_Msg *msg);

    //## operation handleStop()
    void handleStop();

    //## operation readFromServer(void*,READFROMSERVER)
    void readFromServer(void *pUser, READFROMSERVER readFromServer);

    //## operation sendReqMsg(void*,READFROMSERVER,int&,std::string&,unsigned,bool,std::string&,std::string&,std::string&,std::string&,std::string&)
    void sendReqMsg(void *pUser, READFROMSERVER readFromServer, int &method, std::string &target, unsigned version,
                    bool keepAlive, std::string &host, std::string &port, std::string &contentType, std::string &body,
                    std::string &basicAuth, bool ssl);

    std::string base64Encode(std::uint8_t const *data, std::size_t len);

    std::string base64Encode(boost::string_view s);

    std::string base64Decode(boost::string_view data);

    ////    Attributes    ////

    boost::asio::io_context &_ioc;        //## attribute _ioContext

    void *_pUser;        //## attribute _pUser

    READFROMSERVER _readFromServer;        //## attribute _readFromServer

    boost::beast::http::response<boost::beast::http::string_body> _res;        //## attribute _res

    S_HttpClient_ConnectionManager _connectionManager;
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpClient/S_HttpClient_Service.h
*********************************************************************/
