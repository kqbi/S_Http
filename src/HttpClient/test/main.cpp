/********************************************************************
    Rhapsody	: 8.4
    Login		: Administrator
    Component	: DefaultComponent
    Configuration 	: S_HTTP_Config
    Model Element	: S_HTTP_Config
//!	Generated Date	: Fri, 14, Jun 2019  
    File Path	: ../../src/MainDefaultComponent.cpp
*********************************************************************/

#include <oxf.h>
#include <iostream>
#include <signal.h>
#include "S_HttpClient_MainSession.h"
#include "S_HttpRes_Msg.h"

static bool finished = false;
static void
signalHandler(int signo)
{
    std::cerr << "Shutting down" << std::endl;
    finished = true;
}
void readFromServer(void* pUser, S_Http_Msg* msg) {
 std::cout <<"mm:" <<  ((S_HttpRes_Msg*)msg)->_body << std::endl;
    printf("msg:::::::::::::::\n");
    S_HttpClient_MainSession *mainSession = (S_HttpClient_MainSession *) pUser;
    auto stronglf = mainSession->_processTp.lock();
    if (stronglf) {
        boost::asio::post(*stronglf,[&](){
            mainSession->execProcessMsg(msg);
        });
    } else {
        delete msg;
        msg = 0;
    }
}

int main(int argc, char* argv[]) {
    int status = 0;
    if(OXF::initialize(0))
    {
        OXF::frmThreadAffinities = {15,15,15,15,15,15};
        OXF::start(true);
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

        if ( signal( SIGINT, signalHandler  ) == SIG_ERR )
        {
            std::cerr << "Couldn't install signal handler for SIGINT" << std::endl;
            exit( -1 );
        }

        if ( signal( SIGTERM, signalHandler  ) == SIG_ERR )
        {
            std::cerr << "Couldn't install signal handler for SIGTERM" << std::endl;
            exit( -1 );
        }

        S_HttpClient_MainSession* mainSession = new S_HttpClient_MainSession();
        mainSession->init();
        int method = 2;
        std::string target = "/onvif-http/snapshot?Profile_1";
        unsigned version = 11;
        bool keepAlive = true;
        std::string host = "192.168.1.165";
        std::string port = "";
        std::string contentType = "";
        std::string body = "";
        std::string basicAuth = "admin:admin123";
        mainSession->sendReqMsg(mainSession, readFromServer, method, target, host, port, contentType, body, version, keepAlive, basicAuth);
        while (!finished)
        {
#ifdef WIN32
            Sleep(1000);
#else
            usleep(1000*1000);
#endif
        }
        delete mainSession;
        OMOS::endApplication(status);
        status = 0;
    }
    else
    {
        status = 1;
    }
    return status;
}

/*********************************************************************
    File Path	: ../../src/MainDefaultComponent.cpp
*********************************************************************/
