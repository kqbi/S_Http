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
#include "S_HttpServer.h"

static bool finished = false;

static void
signalHandler(int signo) {
    std::cerr << "Shutting down" << std::endl;
    finished = true;
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

    S_HttpServer *server = new S_HttpServer(io_context);
    std::string filePath = "";
    std::string ip = "";
    unsigned short port = 1111;
    server->init(filePath);
    if (!server->listen(ip, port)) {
        std::cerr << "listen port " << port << " is failed!" << std::endl;
        server->stop();
        delete server;
        ::exit(-1);
    }
    io_context.run();
    while (!finished) {
#ifdef WIN32
        Sleep(1000);
#else
        usleep(1000*1000);
#endif
    }
    server->stop();
    delete server;
    exit(status);
    status = 0;
    return status;
}

/*********************************************************************
    File Path	: ../../src/MainDefaultComponent.cpp
*********************************************************************/
