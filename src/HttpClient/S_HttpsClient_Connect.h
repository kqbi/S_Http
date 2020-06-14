//
// Created by kqbi on 2020/3/18.
//

#ifndef S_HTTP_S_HTTPSCLIENT_CONNECT_H
#define S_HTTP_S_HTTPSCLIENT_CONNECT_H

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include "S_HttpClient_ConnectBase.h"
namespace S_Http {
    class S_HttpsClient_Connect : public S_HttpClient_ConnectBase {
    public:
        explicit
        S_HttpsClient_Connect(boost::asio::io_context &ioc, boost::asio::ssl::context &ctx,
                              S_HttpClient_ConnectionManager &connectionManager)
                : S_HttpClient_ConnectBase(ioc, connectionManager), _stream(boost::asio::make_strand(ioc), ctx) {
        }

        void resolve(std::string &host, std::string &port);

        void on_resolve(boost::beast::error_code ec, boost::asio::ip::tcp::resolver::results_type results);

        void on_connect(boost::beast::error_code ec, boost::asio::ip::tcp::resolver::results_type::endpoint_type);

        void on_handshake(boost::beast::error_code ec);

        void on_write(boost::beast::error_code ec, std::size_t bytes_transferred);

        void on_read(boost::beast::error_code ec, std::size_t bytes_transferred);

        void on_shutdown(boost::beast::error_code ec);

        void fail(boost::beast::error_code ec, char const *what);

        void close();

        boost::beast::ssl_stream<boost::beast::tcp_stream> _stream;
    };

}
#endif //S_HTTP_S_HTTPSCLIENT_CONNECT_H
