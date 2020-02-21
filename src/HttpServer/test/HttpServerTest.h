/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: HttpServerTest
//!	Generated Date	: Tue, 24, Sep 2019  
	File Path	: ../../src/HttpServerTest/HttpServerTest.h
*********************************************************************/

#ifndef HttpServerTest_HttpServerTest_H
#define HttpServerTest_HttpServerTest_H

#include <oxf.h>
#include <event.h>
class S_HttpServer_MainSession;

class S_HttpServer_Session;

#define evDestroyConnectionService_HttpServerTest_id 19201

#define evRegiterSuccess_HttpServerTest_id 19202

#define evRestProcessiVMSProtocol_HttpServerTest_id 19203

//## package HttpServerTest



class evDestroyConnectionService : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    evDestroyConnectionService();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

class evRegiterSuccess : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    evRegiterSuccess();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

class evRestProcessiVMSProtocol : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    evRestProcessiVMSProtocol();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#endif
/*********************************************************************
	File Path	: ../../src/HttpServerTest/HttpServerTest.h
*********************************************************************/
