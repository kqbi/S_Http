/********************************************************************
    Rhapsody	: 8.4
    Login		: Administrator
    Component	: DefaultComponent
    Configuration 	: S_HTTP_Config
    Model Element	: S_HTTP_Config
//!	Generated Date	: Fri, 14, Jun 2019  
    File Path	: ../../src/MainDefaultComponent.cpp
*********************************************************************/

#include <iostream>
#include <signal.h>
#include "S_HttpClient.h"
#include "S_HttpRes_Msg.h"

static bool finished = false;

static void
signalHandler(int signo) {
    std::cerr << "Shutting down" << std::endl;
    finished = true;
}

void readFromServer(void *pUser, S_Http::S_Http_Msg *msg) {
    std::cout << "mm:" << ((S_HttpRes_Msg *) msg)->_body << std::endl;
    S_HttpClient *client = (S_HttpClient *) pUser;
}

int main(int argc, char *argv[]) {
    int status = 0;

#ifndef _WIN32
    if ( signal( SIGPIPE, SIG_IGN) == SIG_ERR)
    {
        std::cerr << "Couldn't install signal handler for SIGPIPE" << std::endl;
        exit(-1);
    }
    //        if ( signal( SIGHUP,signalHandler ) == SIG_ERR )
    //        {
    //            std::cerr << "Couldn't install signal handler for SIGHUP" << std::endl;
    //            exit( -1 );
    //        }
#endif

    if (signal(SIGINT, signalHandler) == SIG_ERR) {
        std::cerr << "Couldn't install signal handler for SIGINT" << std::endl;
        exit(-1);
    }

    if (signal(SIGTERM, signalHandler) == SIG_ERR) {
        std::cerr << "Couldn't install signal handler for SIGTERM" << std::endl;
        exit(-1);
    }

    boost::asio::io_context io_context;

    S_HttpClient *client = new S_HttpClient(io_context);
    int method = 2;
    std::string target = "/onvif-http/snapshot?Profile_101";
    unsigned version = 11;
    bool keepAlive = true;
    std::string host = "127.0.0.1";
    std::string port = "10802";
    std::string contentType = "";
    std::string body = "";
    std::string authorization = "";
    printf("1111111111111111111\n");
    client->sendReqMsg([](S_Http_Msg *msg) {
                           S_HttpRes_Msg *res = (S_HttpRes_Msg *) msg;
                           std::string authStr = res->_res.find(boost::beast::http::field::www_authenticate)->value().to_string();
                           S_Http_Msg::http_header_www_authenticate_t auth;
                           memset(&auth, 0, sizeof(auth));
                           res->WWWAthenticate(authStr.c_str(), &auth);
                           printf("res====================\n");
                       }, method, target, host, port, contentType, body, false, version,
                       keepAlive, authorization);
    io_context.run();
    while (!finished) {
#ifdef WIN32
        Sleep(1000);
#else
        usleep(1000*1000);
#endif
    }
    delete client;
    ::exit(status);
    status = 0;
    return status;
}

/*********************************************************************
    File Path	: ../../src/MainDefaultComponent.cpp
*********************************************************************/
