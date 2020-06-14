/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpReq_Msg
//!	Generated Date	: Tue, 10, Dec 2019  
	File Path	: ../../src/HttpMsg/S_HttpReq_Msg.h
*********************************************************************/

#ifndef HttpMsg_S_HttpReq_Msg_H
#define HttpMsg_S_HttpReq_Msg_H

#include "S_Http_Msg.h"
#include <unordered_map>
#include <string>
//## package HttpMsg
namespace S_Http {
//## class S_HttpReq_Msg
    class S_HttpReq_Msg : public S_Http_Msg {
        ////    Constructors and destructors    ////

    public :

        //## operation S_HttpReq_Msg(std::string&,unsigned,std::string&,std::string&,std::uint64_t&)
        S_HttpReq_Msg(std::string &connectionId, unsigned version, std::string &target, std::string &body,
                      std::uint64_t &contentLength);

        ~S_HttpReq_Msg();

        ////    Attributes    ////

        std::unordered_map<std::string, std::string> _paramItems;        //## attribute _paramItems

        std::string _path;        //## attribute _path

        std::string _remoteIp;

        uint16_t _remotePort;
    };
}
#endif
/*********************************************************************
	File Path	: ../../src/HttpMsg/S_HttpReq_Msg.h
*********************************************************************/
