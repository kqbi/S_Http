/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_Connection
//!	Generated Date	: Tue, 10, Dec 2019  
	File Path	: ../../src/HttpServer/S_HttpServer_Connection.h
*********************************************************************/

#ifndef HttpServer_S_HttpServer_Connection_H
#define HttpServer_S_HttpServer_Connection_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio/spawn.hpp>
#include "S_HttpServer_ConnectionManager.h"

namespace S_Http {
    class S_HttpReq_Msg;

    class S_HttpServer_ConnectionManager;

    class S_HttpServer_Service;

//## package HttpServer

//## class S_HttpServer_Connection
    class S_HttpServer_Connection
            : public std::enable_shared_from_this<S_HttpServer_Connection>, private boost::noncopyable {
    public :

        typedef std::shared_ptr<S_HttpServer_Connection> connection_ptr;

        struct send_lambda {
            std::weak_ptr<S_HttpServer_Connection> _self;

            explicit
            send_lambda(std::weak_ptr<S_HttpServer_Connection> self)
                    : _self(self) {
            }

            template<bool isRequest, class Body, class Fields>
            void
            operator()(boost::beast::http::message<isRequest, Body, Fields> &&msg) const {
                // The lifetime of the message has to extend
                // for the duration of the async operation so
                // we use a shared_ptr to manage it.
                auto sp = std::make_shared<
                        boost::beast::http::message<isRequest, Body, Fields>>(std::move(msg));

                auto self = _self.lock();
                if (self)
                    boost::asio::post(self->_strand, [this, sp, self]() {
                        boost::asio::spawn(self->_strand,
                                           [this, sp, self](boost::asio::yield_context yield) {
                                               if (self->_stream.socket().is_open()) {
                                                   boost::system::error_code err;
                                                   boost::beast::http::async_write(
                                                           self->_stream,
                                                           *sp,
                                                           yield[err]);

                                                   if (err)
                                                       return self->stop();

                                                   if (sp->need_eof()) {
                                                       // This means we should close the connection, usually because
                                                       // the response indicated the "Connection: close" semantic.
                                                       return self->_connectManager.stop(self);
                                                   }

                                                   // Read another request
                                                   self->doRead();
                                               }
                                           });
                    });
            }
        };

        ////    Constructors and destructors    ////

        //## operation S_HttpServer_Connection(std::string&,S_HttpServer_Service&,tcp::socket&&,S_HttpServer_ConnectionManager&,std::string&,unsigned short&)
        S_HttpServer_Connection(std::string &connectionId, std::shared_ptr<S_HttpServer_Service> service,
                                boost::asio::ip::tcp::socket &&socket, boost::asio::io_context &ioc,
                                S_HttpServer_ConnectionManager &connectionManager, std::string &remoteIpAddress,
                                unsigned short &port);

        //## operation ~S_HttpServer_Connection()
        ~S_HttpServer_Connection();

        ////    Operations    ////

        //## operation closeSocket()
        void closeSocket();

        //## operation doRead()
        void doRead();

        //## operation handleRequest(beast::string_view,http::request<Body, http::basic_fields<Allocator>>&&,Send&&)
        template<class Body, class Allocator, class Send>
        void handleRequest(boost::beast::string_view docRoot,
                           boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>> &&req,
                           Send &&send);

        //## operation mime_type(beast::string_view)
        boost::beast::string_view mime_type(boost::beast::string_view path);

        //## operation path_cat(beast::string_view,beast::string_view)
        std::string path_cat(boost::beast::string_view base, boost::beast::string_view path);

        //## operation sendResMsg(http::status,unsigned,std::string&)
        void sendResMsg(boost::beast::http::status status, unsigned version, std::string &body);

        //## operation shutdown()
        void shutdown();

        //## operation start()
        void start();

        //## operation stop()
        void stop();

    private :

        ////    Attributes    ////

    public :

        boost::beast::tcp_stream _stream;        //## attribute _stream

        boost::beast::flat_buffer _buffer;        //## attribute _buffer

        S_HttpServer_ConnectionManager &_connectManager;        //## attribute _connectManager

        std::string _connectionId;        //## attribute _connectionId

        std::string _remoteIpAddress;        //## attribute _remoteIpAddress

        unsigned short _port;        //## attribute _port

        boost::beast::http::request<boost::beast::http::string_body> _req;        //## attribute _req

        std::shared_ptr<S_HttpServer_Service> _service;        //## attribute _service

        bool _keepAlive;        //## attribute _keepAlive

        boost::asio::strand<boost::asio::io_context::executor_type> _strand;
    };
}
#endif
/*********************************************************************
	File Path	: ../../src/HttpServer/S_HttpServer_Connection.h
*********************************************************************/
