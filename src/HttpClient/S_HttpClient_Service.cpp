/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpClient_Service
//!	Generated Date	: Fri, 27, Sep 2019  
	File Path	: ../../src/HttpClient/S_HttpClient_Service.cpp
*********************************************************************/

#include "S_HttpClient_Service.h"
#include "S_Http_Msg.h"
#include "S_HttpClient_Connect.h"
#include "S_HttpsClient_Connect.h"
#include <root_certificates.hpp>
#include "Util.h"
//## package HttpClient
namespace S_Http {
//## class S_HttpClient_Service
    S_HttpClient_Service::S_HttpClient_Service(boost::asio::io_context &ioc) : _ioc(ioc) {
        //#[ operation S_HttpClient_Service(std::size_t)
        //#]
    }

    S_HttpClient_Service::~S_HttpClient_Service() {
    }

    void S_HttpClient_Service::handleStop() {
        //#[ operation handleStop()
        _connectionManager.stopAll();
        //#]
    }

    void S_HttpClient_Service::sendReqMsg(std::function<void(S_Http_Msg *msg)> readFromServer, int &method, std::string &target,
                                          unsigned version, bool keepAlive, std::string &host, std::string &port,
                                          std::string &contentType, std::string &body, std::string &basicAuth,
                                          bool ssl) {
        //#[ operation sendReqMsg(void*,READFROMSERVER,int&,std::string&,unsigned,bool,std::string&,std::string&,std::string&,std::string&,std::string&)
        std::shared_ptr<S_HttpClient_ConnectBase> connect = 0;
        if (ssl) {
            boost::asio::ssl::context ctx{boost::asio::ssl::context::tlsv12_client};
            // This holds the root certificate used for verification
            load_root_certificates(ctx);
            // Verify the remote server's certificate
            // ctx.set_verify_mode(boost::asio::ssl::verify_peer);
            ctx.set_verify_mode(boost::asio::ssl::verify_none);
            connect = std::dynamic_pointer_cast<S_HttpClient_ConnectBase>(
                    std::make_shared<S_HttpsClient_Connect>(_ioc, ctx, _connectionManager));
        } else {
            connect = std::dynamic_pointer_cast<S_HttpClient_ConnectBase>(
                    std::make_shared<S_HttpClient_Connect>(readFromServer, _ioc, _connectionManager));
        }
        _connectionManager.join(connect);
        connect->_req.version(version);
        connect->_req.method((boost::beast::http::verb) method);
        connect->_req.target(target);
        connect->_req.set(boost::beast::http::field::host, host);
        connect->_req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        if (!contentType.empty())
            connect->_req.set(boost::beast::http::field::content_type, contentType);

        std::string base64string = base64Encode(basicAuth);

        std::string authorization = "Basic " + base64string;
        if (!basicAuth.empty())
            connect->_req.set(boost::beast::http::field::authorization, authorization);

        connect->_req.keep_alive(keepAlive);

        if (keepAlive)
            connect->_req.set(boost::beast::http::field::connection, "keep-alive");
        else
            connect->_req.set(boost::beast::http::field::connection, "close");

        connect->_req.body() = body;
        connect->_req.prepare_payload();

        if (port.empty()) {
            if (ssl)
                port = "443";
            else
                port = "80";
        }

        connect->resolve(host, port);
        //#]
    }
}
/*********************************************************************
	File Path	: ../../src/HttpClient/S_HttpClient_Service.cpp
*********************************************************************/
