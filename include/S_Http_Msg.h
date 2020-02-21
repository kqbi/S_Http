/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_Http_Msg
//!	Generated Date	: Tue, 10, Dec 2019  
	File Path	: ../../src/HttpMsg/S_Http_Msg.h
*********************************************************************/

#ifndef HttpMsg_S_Http_Msg_H
#define HttpMsg_S_Http_Msg_H

#include <string>
//## package HttpMsg

//## class S_Http_Msg
class S_Http_Msg {
public :

    //## class S_Http_Msg::HEADER
    class HEADER {
        ////    Constructors and destructors    ////
        
    public :
    
        ~HEADER();
        
        ////    Attributes    ////
        
        unsigned long long contentLength;		//## attribute contentLength
        
        std::string contentType;		//## attribute contentType
        
        unsigned version;		//## attribute version
    };
    
    ////    Constructors and destructors    ////
    
    //## operation S_Http_Msg(std::string&,std::string&)
    S_Http_Msg(std::string& connectionId, std::string& body);
    
    //## operation ~S_Http_Msg()
    virtual ~S_Http_Msg();
    
    ////    Attributes    ////

    HEADER _header;		//## attribute _header
    
    std::string _body;		//## attribute _body
    
    std::string _connectionId;		//## attribute _connectionId
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpMsg/S_Http_Msg.h
*********************************************************************/
