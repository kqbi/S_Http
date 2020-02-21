/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpRes_Msg
//!	Generated Date	: Tue, 10, Dec 2019  
	File Path	: ../../src/HttpMsg/S_HttpRes_Msg.cpp
*********************************************************************/

#include "S_HttpRes_Msg.h"
//## package HttpMsg

//## class S_HttpRes_Msg
S_HttpRes_Msg::S_HttpRes_Msg(std::string& connectionId, unsigned status, unsigned version, bool keepAlive, std::string& body, std::string& contentType, std::uint64_t contentLen) : S_Http_Msg(connectionId, body), _keepAlive(keepAlive), _status(status) {
    //#[ operation S_HttpRes_Msg(std::string&,unsigned,unsigned,bool,std::string&,std::string&,std::uint64_t)
    _header.version = version;
    _header.contentType = contentType;
    _header.contentLength = contentLen;
    //#]
}

S_HttpRes_Msg::~S_HttpRes_Msg() {
}

/*********************************************************************
	File Path	: ../../src/HttpMsg/S_HttpRes_Msg.cpp
*********************************************************************/
