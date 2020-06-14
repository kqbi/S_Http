/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_Http_Msg
//!	Generated Date	: Tue, 10, Dec 2019  
	File Path	: ../../src/HttpMsg/S_Http_Msg.cpp
*********************************************************************/

#include "S_Http_Msg.h"
//## package HttpMsg
namespace S_Http {
//## class S_Http_Msg
//## class S_Http_Msg::HEADER
    S_Http_Msg::HEADER::~HEADER() {
    }

    S_Http_Msg::S_Http_Msg(std::string &connectionId, std::string &body) : _body(body), _connectionId(connectionId) {
        //#[ operation S_Http_Msg(std::string&,std::string&)
        //#]
    }

    S_Http_Msg::~S_Http_Msg() {
        //#[ operation ~S_Http_Msg()
        //#]
    }
}
/*********************************************************************
	File Path	: ../../src/HttpMsg/S_Http_Msg.cpp
*********************************************************************/
