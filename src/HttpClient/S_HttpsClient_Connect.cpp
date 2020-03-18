//
// Created by kqbi on 2020/3/18.
//

#include "S_HttpsClient_Connect.h"

void fail(boost::beast::error_code ec, char const *what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

void S_HttpsClient_Connect::resolve(std::string &host, std::string &port) {
    // Set SNI Hostname (many hosts need this to handshake successfully)
    if (!SSL_set_tlsext_host_name(_stream.native_handle(), host.data())) {
        boost::beast::error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
        std::cerr << ec.message() << "\n";
        return;
    }
    // Look up the domain name
    _resolver.async_resolve(host,
                            port,
                            boost::beast::bind_front_handler(
                                    &S_HttpsClient_Connect::on_resolve,
                                    this));
}

void
S_HttpsClient_Connect::on_resolve(boost::beast::error_code ec, boost::asio::ip::tcp::resolver::results_type results) {
    if (ec)
        return fail(ec, "resolve");

    // Set a timeout on the operation
    boost::beast::get_lowest_layer(_stream).expires_after(std::chrono::seconds(30));

    // Make the connection on the IP address we get from a lookup
    boost::beast::get_lowest_layer(_stream).async_connect(
            results,
            boost::beast::bind_front_handler(
                    &S_HttpsClient_Connect::on_connect,
                    this));
}

void S_HttpsClient_Connect::on_connect(boost::beast::error_code ec,
                                       boost::asio::ip::tcp::resolver::results_type::endpoint_type) {
    if (ec)
        return fail(ec, "connect");

    // Perform the SSL handshake
    _stream.async_handshake(
            boost::asio::ssl::stream_base::client,
            boost::beast::bind_front_handler(
                    &S_HttpsClient_Connect::on_handshake,
                    this));
}

void S_HttpsClient_Connect::on_handshake(boost::beast::error_code ec) {
    if (ec)
        return fail(ec, "handshake");

    // Set a timeout on the operation
    boost::beast::get_lowest_layer(_stream).expires_after(std::chrono::seconds(30));

    // Send the HTTP request to the remote host
    boost::beast::http::async_write(_stream, _req,
                                    boost::beast::bind_front_handler(
                                            &S_HttpsClient_Connect::on_write,
                                            this));
}

void S_HttpsClient_Connect::on_write(boost::beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "write");

    // Receive the HTTP response
    boost::beast::http::async_read(_stream, _buffer, _res,
                                   boost::beast::bind_front_handler(
                                           &S_HttpsClient_Connect::on_read,
                                           this));
}

void S_HttpsClient_Connect::on_read(boost::beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "read");

    // Write the message to standard out
    std::cout << _res << std::endl;

    // Set a timeout on the operation
    boost::beast::get_lowest_layer(_stream).expires_after(std::chrono::seconds(30));

    // Gracefully close the stream
    _stream.async_shutdown(
            boost::beast::bind_front_handler(
                    &S_HttpsClient_Connect::on_shutdown,
                    this));
}

void S_HttpsClient_Connect::on_shutdown(boost::beast::error_code ec) {
    if (ec == boost::asio::error::eof) {
        // Rationale:
        // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
        ec = {};
    }
    if (ec)
        return fail(ec, "shutdown");

    // If we get here then the connection is closed gracefully
}