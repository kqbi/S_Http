//
// Created by kqbi on 2020/3/18.
//

#ifndef S_HTTP_S_HTTPCLIENT_CONNECTBASE_H
#define S_HTTP_S_HTTPCLIENT_CONNECTBASE_H

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

class S_HttpClient_ConnectBase {
public:
    S_HttpClient_ConnectBase(boost::asio::io_context &ioc):_resolver(boost::asio::make_strand(ioc)){};

    virtual ~S_HttpClient_ConnectBase(){};

    virtual void resolve(std::string &host, std::string &port) = 0;

    boost::asio::ip::tcp::resolver _resolver;
    boost::beast::flat_buffer _buffer; // (Must persist between reads)
    boost::beast::http::request<boost::beast::http::string_body> _req;
    boost::beast::http::response<boost::beast::http::string_body> _res;
};


#endif //S_HTTP_S_HTTPCLIENT_CONNECTBASE_H
