/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_ConnectionManager
//!	Generated Date	: Fri, 20, Sep 2019  
	File Path	: ../../src/HttpServer/S_HttpServer_ConnectionManager.h
*********************************************************************/

#ifndef HttpServer_S_HttpServer_ConnectionManager_H
#define HttpServer_S_HttpServer_ConnectionManager_H

#include <unordered_map>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <mutex>
namespace S_Http {
    class S_HttpServer_Connection;

//## package HttpServer

//## class S_HttpServer_ConnectionManager
    class S_HttpServer_ConnectionManager : private boost::noncopyable {
    public :

        typedef std::shared_ptr<S_HttpServer_Connection> connection_ptr;
        ////    Constructors and destructors    ////

        S_HttpServer_ConnectionManager();

        ~S_HttpServer_ConnectionManager();

        ////    Operations    ////

        //## operation getConntionById(std::string&,connection_ptr&)
        void getConntionById(std::string &connectionId, connection_ptr &connection);

        //## operation join(connection_ptr)
        void join(connection_ptr connection);

        //## operation stop(connection_ptr)
        void stop(connection_ptr connection);

        //## operation stopAll()
        void stopAll();

        ////    Attributes    ////

        std::unordered_map<std::string, connection_ptr> _connections;        //## attribute _connections

        std::mutex _mutex;        //## attribute _mutex
    };
}
#endif
/*********************************************************************
	File Path	: ../../src/HttpServer/S_HttpServer_ConnectionManager.h
*********************************************************************/
