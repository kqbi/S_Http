/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_Connection
//!	Generated Date	: Fri, 20, Sep 2019  
	File Path	: ../../src/HttpServer/S_HttpServer_Connection.cpp
*********************************************************************/

#include "S_HttpServer_Connection.h"
#include "S_HttpReq_Msg.h"
#include "S_HttpServer_ConnectionManager.h"
#include "S_HttpServer_Service.h"
#include <iostream>
//## package HttpServer

//## class S_HttpServer_Connection
S_HttpServer_Connection::S_HttpServer_Connection(std::string &connectionId, S_HttpServer_Service &service,
                                                 boost::asio::ip::tcp::socket &&socket,
                                                 S_HttpServer_ConnectionManager &connectionManager,
                                                 std::string &remoteIpAddress, unsigned short &port) : _stream(
        std::move(socket)), _lambda(*this), _connectManager(connectionManager), _connectionId(connectionId),
                                                                                                       _remoteIpAddress(
                                                                                                               remoteIpAddress),
                                                                                                       _port(port),
                                                                                                       _service(
                                                                                                               service),
                                                                                                       _keepAlive(
                                                                                                               true) {
    //#[ operation S_HttpServer_Connection(std::string&,S_HttpServer_Service&,tcp::socket&&,S_HttpServer_ConnectionManager&,std::string&,unsigned short&)
    //#]
}

S_HttpServer_Connection::~S_HttpServer_Connection() {
    //#[ operation ~S_HttpServer_Connection()
    closeSocket();
    //#]
}

void S_HttpServer_Connection::closeSocket() {
    //#[ operation closeSocket()
    if (_stream.socket().is_open()) {
        beast_close_socket(_stream);
    }
    //#]
}

void S_HttpServer_Connection::doRead() {
    //#[ operation doRead()
    _req = {};
    _stream.expires_after(std::chrono::seconds(120));
    boost::beast::http::async_read(_stream,
                                   _buffer,
                                   _req,
                                   boost::beast::bind_front_handler(&S_HttpServer_Connection::handleRead,
                                                                    shared_from_this()));
    //#]
}

template<class Body, class Allocator, class Send>
void S_HttpServer_Connection::handleRequest(boost::beast::string_view docRoot,
                                            boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>> &&req,
                                            Send &&send) {
    //#[ operation handleRequest(beast::string_view,http::request<Body, http::basic_fields<Allocator>>&&,Send&&)
    // Returns a bad request response
    auto const bad_request =
            [&req](boost::beast::string_view why) {
                boost::beast::http::response<boost::beast::http::string_body> res{
                        boost::beast::http::status::bad_request, req.version()};
                res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
                res.set(boost::beast::http::field::content_type, "text/html");
                res.set(boost::beast::http::field::access_control_allow_origin, "*");
                res.set(boost::beast::http::field::access_control_allow_headers,
                        "Content-Type,Content-Length,Authorization,Accept,X-Requested-With");
                res.set(boost::beast::http::field::access_control_allow_methods, "PUT,POST,GET,DELETE,OPTIONS");
                res.keep_alive(req.keep_alive());
                res.body() = std::string(why);
                res.prepare_payload();
                return res;
            };

    // Returns a not found response
    auto const not_found =
            [&req](boost::beast::string_view target) {
                boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::not_found,
                                                                                  req.version()};
                res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
                res.set(boost::beast::http::field::content_type, "text/html");
                res.set(boost::beast::http::field::access_control_allow_origin, "*");
                res.set(boost::beast::http::field::access_control_allow_headers,
                        "Content-Type,Content-Length,Authorization,Accept,X-Requested-With");
                res.set(boost::beast::http::field::access_control_allow_methods, "PUT,POST,GET,DELETE,OPTIONS");
                res.keep_alive(req.keep_alive());
                res.body() = "The resource '" + std::string(target) + "' was not found.";
                res.prepare_payload();
                return res;
            };

    // Returns a server error response
    auto const server_error =
            [&req](boost::beast::string_view what) {
                boost::beast::http::response<boost::beast::http::string_body> res{
                        boost::beast::http::status::internal_server_error, req.version()};
                res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
                res.set(boost::beast::http::field::content_type, "text/html");
                res.set(boost::beast::http::field::access_control_allow_origin, "*");
                res.set(boost::beast::http::field::access_control_allow_headers,
                        "Content-Type,Content-Length,Authorization,Accept,X-Requested-With");
                res.set(boost::beast::http::field::access_control_allow_methods, "PUT,POST,GET,DELETE,OPTIONS");
                res.keep_alive(req.keep_alive());
                res.body() = "An error occurred: '" + std::string(what) + "'";
                res.prepare_payload();
                return res;
            };

    // Make sure we can handle the method
    if (req.method() != boost::beast::http::verb::get &&
        req.method() != boost::beast::http::verb::post &&
        req.method() != boost::beast::http::verb::options &&
        req.method() != boost::beast::http::verb::head)
        return send(bad_request("Unknown HTTP-method"));
    // Request path must be absolute and not contain "..".
    if (req.target().empty() ||
        req.target()[0] != '/' ||
        req.target().find("..") != boost::beast::string_view::npos)
        return send(bad_request("Illegal request-target"));

    // Build the path to the requested file
    std::string url = path_cat(docRoot, req.target());
    if (req.target().back() == '/')
        url.append("index.html");
    if (req.target().find(".") != boost::beast::string_view::npos) {
        // Attempt to open the file
        boost::beast::error_code ec;
        boost::beast::http::file_body::value_type body;
        for (auto it : _service._filePaths) {
            body.open((it + url).c_str(), boost::beast::file_mode::scan, ec);
            if (!ec)
                break;
        }

        // Handle the case where the file doesn't exist
        if (ec == boost::beast::errc::no_such_file_or_directory)
            return send(not_found(req.target()));

        // Handle an unknown error
        if (ec)
            return send(server_error(ec.message()));

        auto const size = body.size();
        // Respond to HEAD request
        if (req.method() == boost::beast::http::verb::head) {
            boost::beast::http::response<boost::beast::http::empty_body> res{boost::beast::http::status::ok,
                                                                             req.version()};
            res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(boost::beast::http::field::content_type, mime_type(url));
            res.content_length(size);
            res.keep_alive(req.keep_alive());
            return send(std::move(res));
        }

#if 1
        auto &strRange = req["Range"];
        int64_t iRangeStart = 0;
        int64_t iRangeEnd = 0;
        int64_t fileSize = size;

        const char *pcHttpResult = NULL;

        boost::beast::http::response<boost::beast::http::file_body> res{
                std::piecewise_construct,
                std::make_tuple(std::move(body))};

        if (strRange.size() == 0) {
            res.set(boost::beast::http::field::status_uri, "200 OK");
            iRangeEnd = fileSize - 1;
        } else {
            pcHttpResult = "206 Partial Content";
            res.set(boost::beast::http::field::status_uri, "206 Partial Content");
            iRangeStart = atoll(FindField(strRange.data(), "bytes=", "-").data());
            iRangeEnd = atoll(FindField(strRange.data(), "-", "\r\n").data());
            if (iRangeEnd == 0) {
                iRangeEnd = fileSize - 1;
            }
            std::stringstream b;
            b << "bytes " << iRangeStart << "-" << iRangeEnd << "/" << fileSize;
            res.set(boost::beast::http::field::content_range, b.str());
        }
#endif

        res.set(boost::beast::http::field::version, req.version());
        res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(boost::beast::http::field::content_type, mime_type(url));
        res.content_length(iRangeEnd - iRangeStart + 1);
        res.keep_alive(req.keep_alive());

        return send(std::move(res));

    } else {
        if (req.method() == boost::beast::http::verb::head) {
            boost::beast::http::response<boost::beast::http::empty_body> res{boost::beast::http::status::ok,
                                                                             req.version()};
            res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(boost::beast::http::field::content_type, mime_type(url));
            res.set(boost::beast::http::field::access_control_allow_origin, "*");
            res.set(boost::beast::http::field::access_control_allow_headers,
                    "Content-Type,Content-Length,Authorization,Accept,X-Requested-With");
            res.set(boost::beast::http::field::access_control_allow_methods, "PUT,POST,GET,DELETE,OPTIONS");
            res.keep_alive(req.keep_alive());
            return send(std::move(res));
        }
        if (req.method() == boost::beast::http::verb::options) {
            boost::beast::http::response<boost::beast::http::empty_body> res{boost::beast::http::status::ok,
                                                                             req.version()};
            res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(boost::beast::http::field::content_type, mime_type(url));
            res.set(boost::beast::http::field::access_control_allow_origin, "*");
            res.set(boost::beast::http::field::access_control_allow_headers,
                    "Content-Type,Content-Length,Authorization,Accept,X-Requested-With");
            res.set(boost::beast::http::field::access_control_allow_methods, "PUT,POST,GET,DELETE,OPTIONS");
            res.keep_alive(req.keep_alive());
            return send(std::move(res));
        }

        std::string body = "";
        std::uint64_t contentLength = 0;
        if (req.has_content_length()) {
            boost::optional<std::uint64_t> size = req.payload_size();
            if (size)
                contentLength = *size;
            body = req.body();
        }

        S_HttpReq_Msg *msg = new S_HttpReq_Msg(_connectionId, req.version(), url, body, contentLength);

        _keepAlive = req.keep_alive();

        if (!_service.handleHttp(msg)) {
            send(not_found(req.target()));
        }
    }
#if 0
    {
        std::string body = "Hello, world!";
    
        // Respond to HEAD request
        if(req.method() == http::verb::head)
        {
            http::response<http::empty_body> res{http::status::ok, req.version()};
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, mime_type(msg->_path));
            //res.content_length(size);
            res.keep_alive(req.keep_alive());
            return send(std::move(res));
        }
    
        // Respond to GET request
        http::response<http::string_body> res{std::piecewise_construct,
                    std::make_tuple(std::move(body)),
                    std::make_tuple(http::status::ok, req.version())};
        res.keep_alive(req.keep_alive());
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, mime_type(msg->_path));
        res.content_length(body.size());
        //req.prepare_payload();
    
    
        printf("aaaaaaa\n");
    
    }
    
    {
        std::string body = "Hello, world!";
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = std::string(body);
        res.prepare_payload();
        return send(std::move(res));
    }
#endif
    //#]
}

std::string S_HttpServer_Connection::FindField(const char *buf, const char *start, const char *end, int bufSize) {
    if (bufSize <= 0) {
        bufSize = strlen(buf);
    }
    const char *msg_start = buf, *msg_end = buf + bufSize;
    int len = 0;
    if (start != NULL) {
        len = strlen(start);
        msg_start = strstr(buf, start);
    }
    if (msg_start == NULL) {
        return "";
    }
    msg_start += len;
    if (end != NULL) {
        msg_end = strstr(msg_start, end);
        if (msg_end == NULL) {
            return "";
        }
    }
    return std::string(msg_start, msg_end);
}

boost::beast::string_view S_HttpServer_Connection::mime_type(boost::beast::string_view path) {
    //#[ operation mime_type(beast::string_view)
    using boost::beast::iequals;
    auto const ext = [&path] {
        auto const pos = path.rfind(".");
        if (pos == boost::beast::string_view::npos)
            return boost::beast::string_view{};
        return path.substr(pos);
    }();
    if (iequals(ext, ".htm")) return "text/html";
    if (iequals(ext, ".html")) return "text/html";
    if (iequals(ext, ".php")) return "text/html";
    if (iequals(ext, ".css")) return "text/css";
    if (iequals(ext, ".txt")) return "text/plain";
    if (iequals(ext, ".js")) return "application/javascript";
    if (iequals(ext, ".json")) return "application/json";
    if (iequals(ext, ".xml")) return "application/xml";
    if (iequals(ext, ".swf")) return "application/x-shockwave-flash";
    if (iequals(ext, ".flv")) return "video/x-flv";
    if (iequals(ext, ".png")) return "image/png";
    if (iequals(ext, ".jpe")) return "image/jpeg";
    if (iequals(ext, ".jpeg")) return "image/jpeg";
    if (iequals(ext, ".jpg")) return "image/jpeg";
    if (iequals(ext, ".gif")) return "image/gif";
    if (iequals(ext, ".bmp")) return "image/bmp";
    if (iequals(ext, ".ico")) return "image/vnd.microsoft.icon";
    if (iequals(ext, ".tiff")) return "image/tiff";
    if (iequals(ext, ".tif")) return "image/tiff";
    if (iequals(ext, ".svg")) return "image/svg+xml";
    if (iequals(ext, ".svgz")) return "image/svg+xml";
    return "application/text";
    //#]
}

std::string S_HttpServer_Connection::path_cat(boost::beast::string_view base, boost::beast::string_view path) {
    //#[ operation path_cat(beast::string_view,beast::string_view)
    if (base.empty())
        return std::string(path);
    std::string result(base);
#ifdef BOOST_MSVC
    char constexpr path_separator = '\\';
    if (result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
    for (auto &c : result)
        if (c == '/')
            c = path_separator;
#else
    char constexpr path_separator = '/';
    if(result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
#endif
    return result;
    //#]
}

void S_HttpServer_Connection::sendResMsg(boost::beast::http::status status, unsigned version, std::string &body) {
    //#[ operation sendResMsg(http::status,unsigned,std::string&)
    boost::beast::http::response<boost::beast::http::string_body> res{status, version};
    res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(boost::beast::http::field::content_type, "application/json");
    res.set(boost::beast::http::field::access_control_allow_origin, "*");
    res.set(boost::beast::http::field::access_control_allow_headers,
            "Content-Type,Content-Length,Authorization,Accept,X-Requested-With");
    res.set(boost::beast::http::field::access_control_allow_methods, "PUT,POST,GET,DELETE,OPTIONS");
    res.keep_alive(_keepAlive);

    if (_keepAlive)
        res.set(boost::beast::http::field::connection, "keep-alive");
    else
        res.set(boost::beast::http::field::connection, "close");

    res.body() = body;
    res.prepare_payload();
    _lambda(std::move(res));
    //#]
}

void S_HttpServer_Connection::shutdown() {
    //#[ operation shutdown()
    stop();
    _connectManager.stop(shared_from_this());
    //#]
}

void S_HttpServer_Connection::start() {
    //#[ operation start()
    _connectManager.join(shared_from_this());
    boost::asio::dispatch(_stream.get_executor(),
                          boost::beast::bind_front_handler(
                                  &S_HttpServer_Connection::doRead,
                                  shared_from_this()));
    //#]
}

void S_HttpServer_Connection::stop() {
    //#[ operation stop()
    if (_stream.socket().is_open()) {
        boost::beast::error_code ec;
        _stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    }
    //#]
}

void S_HttpServer_Connection::handleRead(boost::beast::error_code e, size_t bytesTransferred) {
    //#[ operation handleRead(beast::error_code,size_t)
    if (!e) {
        //handleRequest("", std::move(_req), send_lambda(*this));
        boost::asio::post(*_service._ioContext, [&] {
            handleRequest("", std::move(_req), send_lambda(*this));
        });
    } else if (e == boost::beast::http::error::end_of_stream) {
        //std::cout<<_connectionId << " read:" << e.message() << ":" << e << std::endl;
        shutdown();
    }
    //#]
}

void S_HttpServer_Connection::handleWrite(boost::beast::error_code e, std::size_t bytes_transferred, bool close) {
    //#[ operation handleWrite(beast::error_code,std::size_t,bool)
    if (e)
        return shutdown();

    if (close) {
        // This means we should close the connection, usually because
        // the response indicated the "Connection: close" semantic.
        return shutdown();
    }

    // Read another request
    doRead();
    //#]
}

/*********************************************************************
	File Path	: ../../src/HttpServer/S_HttpServer_Connection.cpp
*********************************************************************/
