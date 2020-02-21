/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpRes_Msg
//!	Generated Date	: Tue, 10, Dec 2019  
	File Path	: ../../src/HttpMsg/S_HttpRes_Msg.h
*********************************************************************/

#ifndef HttpMsg_S_HttpRes_Msg_H
#define HttpMsg_S_HttpRes_Msg_H

#include "S_Http_Msg.h"
//## package HttpMsg

//## class S_HttpRes_Msg
class S_HttpRes_Msg : public S_Http_Msg {
    ////    Constructors and destructors    ////
    
public :

    //## operation S_HttpRes_Msg(std::string&,unsigned,unsigned,bool,std::string&,std::string&,std::uint64_t)
    S_HttpRes_Msg(std::string& connectionId, unsigned status, unsigned version, bool keepAlive, std::string& body, std::string& contentType, std::uint64_t contentLen);
    
    ~S_HttpRes_Msg();
    
    ////    Attributes    ////
    
    bool _keepAlive;		//## attribute _keepAlive
    
    unsigned _status;		//## attribute _status
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpMsg/S_HttpRes_Msg.h
*********************************************************************/
