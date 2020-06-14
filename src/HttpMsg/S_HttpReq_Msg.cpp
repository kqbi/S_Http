/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpReq_Msg
//!	Generated Date	: Tue, 10, Dec 2019  
	File Path	: ../../src/HttpMsg/S_HttpReq_Msg.cpp
*********************************************************************/

#include "S_HttpReq_Msg.h"
//## package HttpMsg
namespace S_Http {
//## class S_HttpReq_Msg
    S_HttpReq_Msg::S_HttpReq_Msg(std::string &connectionId, unsigned version, std::string &target, std::string &body,
                                 std::uint64_t &contentLength) : S_Http_Msg(connectionId, body), _path(""),
                                                                 _remoteIp(""), _remotePort(0) {
        //#[ operation S_HttpReq_Msg(std::string&,unsigned,std::string&,std::string&,std::uint64_t&)
        int pos = target.find('?', 0);
        _path = target.substr(0, pos);
        std::string paramItems = target.substr(pos + 1);

        int lastpos = 0;
        std::string temp = "";
        for (int i = 0; i < paramItems.size(); i++) {
            if (paramItems.data()[i] == '&') {
                temp = paramItems.substr(lastpos, i - lastpos);
                pos = temp.find('=', 0);
                if (pos >= 0)
                    _paramItems[temp.substr(0, pos)] = temp.substr(pos + 1);
                lastpos = i + 1;
            }
        }

        temp = paramItems.substr(lastpos);
        pos = temp.find('=', 0);
        if (pos >= 0)
            _paramItems[temp.substr(0, pos)] = temp.substr(pos + 1);

        _body = body;
        _header.contentLength = contentLength;
        _header.version = version;
        //#]
    }

    S_HttpReq_Msg::~S_HttpReq_Msg() {
    }
}
/*********************************************************************
	File Path	: ../../src/HttpMsg/S_HttpReq_Msg.cpp
*********************************************************************/
