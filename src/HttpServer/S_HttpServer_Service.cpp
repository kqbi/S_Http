/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_Service
//!	Generated Date	: Fri, 20, Sep 2019  
	File Path	: ../../src/HttpServer/S_HttpServer_Service.cpp
*********************************************************************/

#include "S_HttpServer_Service.h"
#include "S_Http_Msg.h"
#include <iostream>
#include <S_HttpReq_Msg.h>
#include "Util.h"

namespace S_Http {
    S_HttpServer_Service::S_HttpServer_Service(boost::asio::io_context &ioc) : _ioc(ioc), _acceptor(ioc),
                                                                               _ipAddress(""),
                                                                               _port(0), _pUser(0) {
        //#[ operation S_HttpServer_Service(const std::string&,unsigned short&,const std::string&,std::size_t)
        //#]
    }

    S_HttpServer_Service::~S_HttpServer_Service() {
        //#[ operation ~S_HttpServer_Service()
        //#]
    }

    void S_HttpServer_Service::handleAccept(boost::beast::error_code e, boost::asio::ip::tcp::socket socket) {
        //#[ operation handleAccept(beast::error_code,tcp::socket)
        if (!_acceptor.is_open())
            return;

        if (!e) {
            boost::system::error_code ec;
            boost::asio::ip::tcp::endpoint endpoint = socket.remote_endpoint(ec);
            if (ec) {
                return;
            }
            std::string remoteIpAddress = endpoint.address().to_string();
            unsigned short port = endpoint.port();

            std::string connectId = getNewConnectionId();

            std::make_shared<S_HttpServer_Connection>(
                    connectId,
                    *this,
                    std::move(socket),
                    _connectionManager,
                    remoteIpAddress,
                    port)->start();
        }
        if (e != boost::asio::error::operation_aborted)
            startAccept();
        //#]
    }

    void S_HttpServer_Service::handleStop() {
        //#[ operation handleStop()
        boost::system::error_code ec;
        _acceptor.close(ec);
        _connectionManager.stopAll();
        //#]
    }

    bool S_HttpServer_Service::listen(std::string &ipAddress, unsigned short port) {
        //#[ operation listen()
        _ipAddress = ipAddress;
        _port = port;
        boost::asio::ip::tcp::endpoint endpoint;
        if (_ipAddress.empty()) {
            endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _port);
        } else {
            boost::asio::ip::address addr;
            addr = boost::asio::ip::make_address(_ipAddress);
            endpoint = boost::asio::ip::tcp::endpoint(addr, _port);
        }
        try {
            _acceptor.open(endpoint.protocol());
            boost::asio::socket_base::reuse_address option(true);
            _acceptor.set_option(option);
            _acceptor.bind(endpoint);
            _acceptor.listen();
        } catch (std::exception &e) {
            return false;
        }
        startAccept();
        return true;
        //#]
    }

    void
    S_HttpServer_Service::sendResMsg(std::string &connectionId, boost::beast::http::status status, unsigned version,
                                     std::string &body) {
        //#[ operation sendResMsg(std::string&,http::status,unsigned,std::string&)
        connection_ptr connection = 0;
        _connectionManager.getConntionById(connectionId, connection);
        if (connection)
            connection->sendResMsg(status, version, body);
        //#]
    }

    void S_HttpServer_Service::startAccept() {
        //#[ operation startAccept()
        _acceptor.async_accept(boost::asio::make_strand(_ioc),
                               boost::beast::bind_front_handler(
                                       &S_HttpServer_Service::handleAccept,
                                       this));
        //#]
    }

    void S_HttpServer_Service::addFilePath(const std::string &filePath) {
        if (!filePath.empty())
            _filePaths.insert(filePath);
    }

    void S_HttpServer_Service::addHandle(const std::string &url, ReqHandler req_handler) {
        if (_handlerMap.find(url) != _handlerMap.end())
            return;

        _handlerMap.insert(std::make_pair(url, req_handler));
    }

    bool S_HttpServer_Service::handleHttp(S_HttpReq_Msg *msg) {
        auto it = _handlerMap.find(msg->_path);
        if (it != _handlerMap.end()) {
            boost::asio::post(_ioc, [=]() {
                if (it->second)
                    it->second(msg);
            });
            return true;
        }
        return false;
    }
}
/*********************************************************************
	File Path	: ../../src/HttpServer/S_HttpServer_Service.cpp
*********************************************************************/
