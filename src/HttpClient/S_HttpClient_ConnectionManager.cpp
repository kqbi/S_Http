//
// Created by kqbi on 2020/5/28.
//

#include "S_HttpClient_ConnectionManager.h"
#include "S_HttpClient_ConnectBase.h"
namespace S_Http {
    void S_HttpClient_ConnectionManager::join(connection_ptr &connection) {
        //#[ operation join(connection_ptr)
        std::lock_guard<std::recursive_mutex> lock(_mutex);
        _connections.insert(connection);
        //#]
    }

    void S_HttpClient_ConnectionManager::stop(connection_ptr connection) {
        //#[ operation stop(connection_ptr)
        std::lock_guard<std::recursive_mutex> lock(_mutex);
        connection->close();
        _connections.erase(connection);
        //#]
    }

    void S_HttpClient_ConnectionManager::stopAll() {
        //#[ operation stopAll()
        printf("stopAll\n");
        std::lock_guard<std::recursive_mutex> lock(_mutex);
        for (auto c : _connections) {
            if (c)
                c->close();
        }
        _connections.clear();
        //#]
    }
}