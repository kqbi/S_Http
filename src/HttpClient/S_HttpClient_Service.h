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
class S_HttpClient_Connect;

class S_Http_Msg;

//## package HttpClient

//## class S_HttpClient_Service
class S_HttpClient_Service {
public :

    typedef std::shared_ptr<boost::asio::io_context> io_context_ptr;

    typedef boost::asio::executor_work_guard<boost::asio::io_context::executor_type> io_context_work;

    typedef std::shared_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> io_context_work_ptr;

    typedef void (*READFROMSERVER)(void *pUser, S_Http_Msg *msg);
    ////    Constructors and destructors    ////

    //## operation S_HttpClient_Service(std::size_t)
    S_HttpClient_Service();

    ~S_HttpClient_Service();

    ////    Operations    ////

    static S_HttpClient_Service *Instance();

    //## operation execProcessMsg(S_Http_Msg*)
    void execProcessMsg(S_Http_Msg *msg);

    //## operation handleStop()
    void handleStop();

    //## operation join()
    void join();

    //## operation readFromServer(void*,READFROMSERVER)
    void readFromServer(void *pUser, READFROMSERVER readFromServer);

    //## operation run()
    void run();

    //## operation sendReqMsg(void*,READFROMSERVER,int&,std::string&,unsigned,bool,std::string&,std::string&,std::string&,std::string&,std::string&)
    void sendReqMsg(void *pUser, READFROMSERVER readFromServer, int &method, std::string &target, unsigned version,
                    bool keepAlive, std::string &host, std::string &port, std::string &contentType, std::string &body,
                    std::string &basicAuth, bool ssl);

    std::string base64_encode(std::uint8_t const *data, std::size_t len);

    std::string base64_encode(boost::string_view s);

    std::string base64_decode(boost::string_view data);

    ////    Attributes    ////

    io_context_ptr _ioContext;        //## attribute _ioContext

    std::size_t _ioContextPoolSize;        //## attribute _ioContextPoolSize

    void *_pUser;        //## attribute _pUser

    READFROMSERVER _readFromServer;        //## attribute _readFromServer

    boost::beast::http::response<boost::beast::http::string_body> _res;        //## attribute _res

    boost::thread_group _threads;        //## attribute _threads

    io_context_work_ptr _work;        //## attribute _work
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpClient/S_HttpClient_Service.h
*********************************************************************/
