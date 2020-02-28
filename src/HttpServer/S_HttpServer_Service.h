/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_Service
//!	Generated Date	: Fri, 20, Sep 2019  
	File Path	: ../../src/HttpServer/S_HttpServer_Service.h
*********************************************************************/

#ifndef HttpServer_S_HttpServer_Service_H
#define HttpServer_S_HttpServer_Service_H

#include "S_HttpServer_Connection.h"
#include "S_HttpServer_ConnectionManager.h"
#include "boost/thread.hpp"
#include "boost/asio.hpp"
#include <unordered_set>
#include <memory>
class S_Http_Msg;

//## package HttpServer

//## class S_HttpServer_Service
class S_HttpServer_Service {
public :
    typedef std::shared_ptr<boost::asio::io_context> io_context_ptr;

    typedef std::shared_ptr<S_HttpServer_Connection> connection_ptr;

    typedef boost::asio::executor_work_guard<boost::asio::io_context::executor_type> io_context_work;

    typedef std::shared_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> io_context_work_ptr;

    typedef std::shared_ptr<boost::asio::ip::tcp::acceptor> io_accept_ptr;

    using ReqHandler = std::function<void (S_HttpReq_Msg *msg)>;

public :

    ////    Constructors and destructors    ////
    
    //## operation S_HttpServer_Service(const std::string&,unsigned short&,const std::string&,std::size_t)
    S_HttpServer_Service();
    
    //## operation ~S_HttpServer_Service()
    ~S_HttpServer_Service();
    
    ////    Operations    ////

    static S_HttpServer_Service* Instance();

    //## operation execProcessMsg(S_Http_Msg*)
    void execProcessMsg(S_Http_Msg* msg);
    
    //## operation getConnectionInfo(std::string&,std::string&,unsigned short&)
    void getConnectionInfo(std::string& connectionId, std::string& ipAddress, unsigned short& port);
    
    //## operation getNewConnectionId()
    std::string getNewConnectionId();
    
    //## operation handleAccept(beast::error_code,tcp::socket)
    void handleAccept(boost::beast::error_code e, boost::asio::ip::tcp::socket socket);
    
    //## operation handleStop()
    void handleStop();
    
    //## operation listen()
    bool listen(std::string &ipAddress, unsigned short port);
    
    //## operation run()
    void run();
    
    //## operation sendResMsg(std::string&,http::status,unsigned,std::string&)
    void sendResMsg(std::string& connectionId, boost::beast::http::status status, unsigned version, std::string& body);
    
    //## operation startAccept()
    void startAccept();

    void addFilePath(const std::string &filePath);

    void addHandle(const std::string &url, ReqHandler req_handler);

    bool handleHttp(S_HttpReq_Msg *msg);

    ////    Attributes    ////

    io_context_ptr _ioContext;		//## attribute _ioContext

    io_context_work_ptr _work;		//## attribute _work

    io_accept_ptr _acceptor;		//## attribute _acceptor
    
    std::string _ipAddress;		//## attribute _ipAddress
    
    unsigned short _port;		//## attribute _port
    
    S_HttpServer_ConnectionManager _connectionManager;		//## attribute _connectionManager
    
    boost::thread_group _threads;		//## attribute _threads
    
    std::size_t _ioContextPoolSize;		//## attribute _ioContextPoolSize
    
    void* _pUser;		//## attribute _pUser

    std::unordered_map<std::string, ReqHandler> _handlerMap;

    std::unordered_set<std::string> _filePaths;
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpServer/S_HttpServer_Service.h
*********************************************************************/
