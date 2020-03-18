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
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/beast/core/detail/base64.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <root_certificates.hpp>
//## package HttpClient

//## class S_HttpClient_Service
S_HttpClient_Service::S_HttpClient_Service() : _pUser(0), _readFromServer(0) {
    //#[ operation S_HttpClient_Service(std::size_t)
    _ioContext = std::make_shared<boost::asio::io_context>();
    _work = std::make_shared<io_context_work>(boost::asio::make_work_guard(*_ioContext));
    _ioContextPoolSize = 2 * boost::thread::hardware_concurrency();
    //#]
}

S_HttpClient_Service::~S_HttpClient_Service() {
}

S_HttpClient_Service *S_HttpClient_Service::Instance() {
    static S_HttpClient_Service service;
    return &service;
}

void S_HttpClient_Service::execProcessMsg(S_Http_Msg *msg) {
    //#[ operation execProcessMsg(S_Http_Msg*)
    if (_pUser && _readFromServer)
        _readFromServer(_pUser, msg);
    else
        delete msg;
    //#]
}

void S_HttpClient_Service::handleStop() {
    //#[ operation handleStop()
    //#]
}

void S_HttpClient_Service::readFromServer(void *pUser, READFROMSERVER readFromServer) {
    //#[ operation readFromServer(void*,READFROMSERVER)
    _pUser = pUser;
    _readFromServer = readFromServer;
    //#]
}

void S_HttpClient_Service::run() {
    //#[ operation run()
    for (std::size_t i = 0; i < _ioContextPoolSize; ++i) {
        _threads.create_thread(boost::bind(&boost::asio::io_context::run, _ioContext));
    }
    //#]
}

void S_HttpClient_Service::sendReqMsg(void *pUser, READFROMSERVER readFromServer, int &method, std::string &target,
                                      unsigned version, bool keepAlive, std::string &host, std::string &port,
                                      std::string &contentType, std::string &body, std::string &basicAuth, bool ssl) {
    //#[ operation sendReqMsg(void*,READFROMSERVER,int&,std::string&,unsigned,bool,std::string&,std::string&,std::string&,std::string&,std::string&)

    //S_HttpClient_Connect *connect = new S_HttpClient_Connect(pUser, readFromServer, *_ioContext, *this);

    boost::asio::ssl::context ctx{boost::asio::ssl::context::tlsv12_client};

    // This holds the root certificate used for verification
    load_root_certificates(ctx);

    // Verify the remote server's certificate
    ctx.set_verify_mode(boost::asio::ssl::verify_peer);
    S_HttpsClient_Connect *connect = new S_HttpsClient_Connect(*_ioContext,ctx);

#if 1
    connect->_req.version(version);
    connect->_req.method((boost::beast::http::verb) method);
    connect->_req.target(target);
    connect->_req.set(boost::beast::http::field::host, host);
    connect->_req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    if (!contentType.empty())
        connect->_req.set(boost::beast::http::field::content_type, contentType);

    std::string base64string = base64_encode(basicAuth);

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

    if (port.empty())
        port = "80";

    connect->resolve(host, port);
#endif
    //#]
}

std::string S_HttpClient_Service::base64_encode(std::uint8_t const *data, std::size_t len) {
    std::string dest;
    dest.resize(boost::beast::detail::base64::encoded_size(len));
    dest.resize(boost::beast::detail::base64::encode(&dest[0], data, len));
    return dest;
}

std::string S_HttpClient_Service::base64_encode(boost::string_view s) {
    return base64_encode(reinterpret_cast <
                                 std::uint8_t const *> (s.data()), s.size());
}

std::string S_HttpClient_Service::base64_decode(boost::string_view data) {
    std::string dest;
    dest.resize(boost::beast::detail::base64::decoded_size(data.size()));
    auto const result = boost::beast::detail::base64::decode(
            &dest[0], data.data(), data.size());
    dest.resize(result.first);
    return dest;
}

/*********************************************************************
	File Path	: ../../src/HttpClient/S_HttpClient_Service.cpp
*********************************************************************/
