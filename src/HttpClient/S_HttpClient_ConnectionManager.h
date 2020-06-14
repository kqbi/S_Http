//
// Created by kqbi on 2020/5/28.
//

#ifndef S_HTTP_S_HTTPCLIENT_CONNECTIONMANAGER_H
#define S_HTTP_S_HTTPCLIENT_CONNECTIONMANAGER_H

#include <unordered_set>
#include <memory>
#include <mutex>
namespace S_Http {
    class S_HttpClient_ConnectBase;

    class S_HttpClient_ConnectionManager {
    public:
        typedef std::shared_ptr<S_HttpClient_ConnectBase> connection_ptr;

        //## operation join(connection_ptr)
        void join(connection_ptr &connection);

        //## operation stop(connection_ptr)
        void stop(connection_ptr connection);

        //## operation stopAll()
        void stopAll();

        std::unordered_set<connection_ptr> _connections;        //## attribute _connections

        std::recursive_mutex _mutex;        //## attribute _mutex
    };

}
#endif //S_HTTP_S_HTTPCLIENT_CONNECTIONMANAGER_H