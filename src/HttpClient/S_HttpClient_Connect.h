/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpClient_Connect
//!	Generated Date	: Fri, 27, Sep 2019  
	File Path	: ../../src/HttpClient/S_HttpClient_Connect.h
*********************************************************************/

#ifndef HttpClient_S_HttpClient_Connect_H
#define HttpClient_S_HttpClient_Connect_H

#include "S_HttpRes_Msg.h"
#include "S_HttpClient_ConnectBase.h"

class S_HttpClient_Service;

//## package HttpClient

//## class S_HttpClient_Connect
class S_HttpClient_Connect : public S_HttpClient_ConnectBase {
public :

    typedef void (*READFROMSERVER)(void *pUser, S_Http_Msg *msg);
    ////    Constructors and destructors    ////

    //## operation S_HttpClient_Connect(void*,READFROMSERVER,boost::asio::io_context&,S_HttpClient_Service&)
    S_HttpClient_Connect(void *pUser, READFROMSERVER readFromServer, boost::asio::io_context &ioc,
                         S_HttpClient_Service &service) : S_HttpClient_ConnectBase(ioc), _pUser(
            pUser), _readFromServer(readFromServer), _service(service), _stream(boost::asio::make_strand(ioc)) {};

    ~S_HttpClient_Connect() {};

    ////    Operations    ////

    //## operation fail(beast::error_code,char const*)
    void fail(boost::beast::error_code ec, char const *what);

    //## operation onConnect(beast::error_code,tcp::resolver::results_type::endpoint_type)
    void
    onConnect(boost::beast::error_code ec, boost::asio::ip::tcp::resolver::results_type::endpoint_type endpointType);

    //## operation onRead(beast::error_code,std::size_t)
    void onRead(boost::beast::error_code ec, std::size_t bytesTransferred);

    //## operation onResolve(beast::error_code,boost::asio::ip::tcp::resolver::results_type)
    void onResolve(boost::beast::error_code ec, boost::asio::ip::tcp::resolver::results_type results);

    //## operation onWrite(beast::error_code,std::size_t)
    void onWrite(boost::beast::error_code ec, std::size_t bytesTransferred);

    //## operation resolve(std::string&,std::string&)
    void resolve(std::string &host, std::string &port);

    //## operation sendReqMsg()
    void sendReqMsg();

    ////    Attributes    ////

    void *_pUser;        //## attribute _pUser

    READFROMSERVER _readFromServer;        //## attribute _readFromServer

    S_HttpClient_Service &_service;        //## attribute _service

    boost::beast::tcp_stream _stream;        //## attribute _stream
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpClient/S_HttpClient_Connect.h
*********************************************************************/
