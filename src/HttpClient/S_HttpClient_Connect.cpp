/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpClient_Connect
//!	Generated Date	: Fri, 27, Sep 2019  
	File Path	: ../../src/HttpClient/S_HttpClient_Connect.cpp
*********************************************************************/

#include "S_HttpClient_Connect.h"
#include "S_HttpClient_Service.h"
#include "S_HttpRes_Msg.h"
#include "oxf/OXFWorkPoller.h"

//## package HttpClient
namespace S_Http {
    void S_HttpClient_Connect::fail(boost::beast::error_code ec, char const *what) {
        //#[ operation fail(beast::error_code,char const*)
        //std::cerr << what << ": " << ec.message() << "\n";
        if (ec != boost::asio::error::operation_aborted)
            _connectionManager.stop(std::dynamic_pointer_cast<S_HttpClient_ConnectBase>(shared_from_this()));
        //#]
    }

    void S_HttpClient_Connect::onConnect(boost::beast::error_code ec,
                                         boost::asio::ip::tcp::resolver::results_type::endpoint_type endpointType) {
        //#[ operation onConnect(beast::error_code,tcp::resolver::results_type::endpoint_type)
        if (ec)
            return fail(ec, "connect");

        // Set a timeout on the operation
        _stream.expires_after(std::chrono::seconds(3));

        // Send the HTTP request to the remote host
        boost::beast::http::async_write(_stream, _req,
                                        boost::beast::bind_front_handler(
                                                &S_HttpClient_Connect::onWrite,
                                                std::dynamic_pointer_cast<S_HttpClient_Connect>(shared_from_this())));
        //#]
    }

    void S_HttpClient_Connect::onRead(boost::beast::error_code ec, std::size_t bytesTransferred) {
        //#[ operation onRead(beast::error_code,std::size_t)
        boost::ignore_unused(bytesTransferred);

        if (ec)
            return fail(ec, "read");

        std::string body = "";
        std::uint64_t contentLength = 0;
        if (_res.has_content_length()) {
            boost::optional<std::uint64_t> size = _res.payload_size();
            if (size)
                contentLength = *size;
            body.append((char *) _res.body().data(), *_res.payload_size());
        }
        //std::cout << body << std::endl;
        std::string content_type = _res.find(boost::beast::http::field::content_type)->value().to_string();
        std::string connectionId = "";
        S_HttpRes_Msg *msg = new S_HttpRes_Msg(connectionId, (unsigned) _res.result(),
                                               _res.version(),
                                               _res.keep_alive(),
                                               body,
                                               content_type,
                                               contentLength);
        msg->_res = _res;
        _readFromServer(msg);

        // Gracefully close the socket
        _stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        //std::cout << ec.message() << std::endl;
        // not_connected happens sometimes so don't bother reporting it.
        if (ec && ec != boost::beast::errc::not_connected)
            return fail(ec, "shutdown");
        _connectionManager.stop(std::dynamic_pointer_cast<S_HttpClient_ConnectBase>(shared_from_this()));
        // If we get here then the connection is closed gracefully
        //#]
    }

    void S_HttpClient_Connect::stop() {
        //#[ operation stop()
        boost::beast::error_code ec;
        _stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        //#]
    }

    void S_HttpClient_Connect::close() {
        //#[ operation stop()
        boost::system::error_code ec;
        _stream.socket().close(ec);
        //#]
    }

    void
    S_HttpClient_Connect::onResolve(boost::beast::error_code ec, boost::asio::ip::tcp::resolver::results_type results) {
        //#[ operation onResolve(beast::error_code,boost::asio::ip::tcp::resolver::results_type)
        if (ec)
            return fail(ec, "resolve");

        // Set a timeout on the operation
        _stream.expires_after(std::chrono::seconds(3));

        // Make the connection on the IP address we get from a lookup
        _stream.async_connect(
                results,
                boost::beast::bind_front_handler(
                        &S_HttpClient_Connect::onConnect,
                        std::dynamic_pointer_cast<S_HttpClient_Connect>(shared_from_this())));
        //#]
    }

    void S_HttpClient_Connect::onWrite(boost::beast::error_code ec, std::size_t bytesTransferred) {
        //#[ operation onWrite(beast::error_code,std::size_t)
        boost::ignore_unused(bytesTransferred);

        if (ec)
            return fail(ec, "write");

        // Receive the HTTP response
        boost::beast::http::async_read(_stream, _buffer, _res,
                                       boost::beast::bind_front_handler(
                                               &S_HttpClient_Connect::onRead,
                                               std::dynamic_pointer_cast<S_HttpClient_Connect>(shared_from_this())));
        //#]
    }

    void S_HttpClient_Connect::resolve(std::string &host, std::string &port) {
        //#[ operation resolve(std::string&,std::string&)
        _resolver.async_resolve(
                host,
                port,
                boost::beast::bind_front_handler(
                        &S_HttpClient_Connect::onResolve,
                        std::dynamic_pointer_cast<S_HttpClient_Connect>(shared_from_this())));
        //#]
    }

    void S_HttpClient_Connect::sendReqMsg() {
        //#[ operation sendReqMsg()
        //#]
    }
}
/*********************************************************************
	File Path	: ../../src/HttpClient/S_HttpClient_Connect.cpp
*********************************************************************/
