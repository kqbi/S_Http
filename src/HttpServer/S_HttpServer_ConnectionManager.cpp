/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_ConnectionManager
//!	Generated Date	: Fri, 20, Sep 2019  
	File Path	: ../../src/HttpServer/S_HttpServer_ConnectionManager.cpp
*********************************************************************/

#include "S_HttpServer_ConnectionManager.h"
#include "S_HttpServer_Connection.h"
//## package HttpServer
namespace S_Http {
//## class S_HttpServer_ConnectionManager
    S_HttpServer_ConnectionManager::S_HttpServer_ConnectionManager() {
    }

    S_HttpServer_ConnectionManager::~S_HttpServer_ConnectionManager() {
    }

    void S_HttpServer_ConnectionManager::getConntionById(std::string &connectionId, connection_ptr &connection) {
        //#[ operation getConntionById(std::string&,connection_ptr&)
        std::lock_guard<std::mutex> lock(_mutex);
        connection = _connections[connectionId];
        //#]
    }

    void S_HttpServer_ConnectionManager::join(connection_ptr connection) {
        //#[ operation join(connection_ptr)
        std::lock_guard<std::mutex> lock(_mutex);
        _connections[connection->_connectionId] = connection;
        //#]
    }

    void S_HttpServer_ConnectionManager::stop(connection_ptr connection) {
        //#[ operation stop(connection_ptr)
        std::lock_guard<std::mutex> lock(_mutex);
        _connections.erase(connection->_connectionId);
        connection->closeSocket();
        //#]
    }

    void S_HttpServer_ConnectionManager::stopAll() {
        //#[ operation stopAll()
        std::lock_guard<std::mutex> lock(_mutex);
        for (auto c : _connections) {
            if (c.second)
                c.second->closeSocket();
        }
        _connections.clear();
        //#]
    }
}
/*********************************************************************
	File Path	: ../../src/HttpServer/S_HttpServer_ConnectionManager.cpp
*********************************************************************/
