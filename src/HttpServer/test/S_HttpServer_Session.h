/*********************************************************************
	Rhapsody	: 8.4 
	Login		: kqbi
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_Session
//!	Generated Date	: Fri, 17, Jan 2020  
	File Path	: ../../src/HttpServer/test/S_HttpServer_Session.h
*********************************************************************/

#ifndef S_HttpServer_Session_H
#define S_HttpServer_Session_H

#include <oxf.h>
#include "HttpServerTest.h"
#include <omreactive.h>
#include <state.h>
#include <event.h>
#include <string>
class S_HttpServer_MainSession;

//## package HttpServerTest

//## class S_HttpServer_Session
class S_HttpServer_Session : public OMReactive {
    ////    Constructors and destructors    ////
    
public :

    //## operation S_HttpServer_Session(std::string&)
    S_HttpServer_Session(std::string& sessionId, IOxfActive* theActiveContext = 0);
    
    //## operation ~S_HttpServer_Session()
    ~S_HttpServer_Session();
    
    ////    Operations    ////
    
    //## operation checkKeepAliveTimeout()
    void checkKeepAliveTimeout();
    
    //## operation destroyWait()
    void destroyWait();
    
    //## operation execProcessiVMSProtocol()
    void execProcessiVMSProtocol();
    
    //## operation setMainSession(S_HttpServer_MainSession*)
    void setMainSession(S_HttpServer_MainSession* mainSession);
    
    ////    Additional operations    ////
    
    virtual bool startBehavior();

protected :

    void initStatechart();
    
    void cancelTimeouts();
    
    bool cancelTimeout(const IOxfTimeout* arg);
    
    ////    Attributes    ////

public :

    int _keepAlivePollTime;		//## attribute _keepAlivePollTime
    
    int _keepAliveTimeoutTimes;		//## attribute _keepAliveTimeoutTimes
    
    S_HttpServer_MainSession* _mainSession;		//## attribute _mainSession
    
    std::string _sessionId;		//## attribute _sessionId
    
    ////    Framework operations    ////
    
    // rootState:
    inline bool rootState_IN() const;
    
    inline bool rootState_isCompleted();
    
    virtual void rootState_entDef();
    
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // terminationstate_5:
    inline bool terminationstate_5_IN() const;
    
    // Run:
    inline bool Run_IN() const;
    
    void Run_entDef();
    
    IOxfReactive::TakeEventStatus Run_handleEvent();
    
    // Registed:
    inline bool Registed_IN() const;
    
    void Registed_entDef();
    
    void Registed_exit();
    
    IOxfReactive::TakeEventStatus Registed_processEvent();
    
    IOxfReactive::TakeEventStatus Registed_handleEvent();
    
    // state_8:
    inline bool state_8_IN() const;
    
    void state_8_entDef();
    
    IOxfReactive::TakeEventStatus state_8_processEvent();
    
    // CheckStatus:
    inline bool CheckStatus_IN() const;
    
    // state_7:
    inline bool state_7_IN() const;
    
    IOxfReactive::TakeEventStatus state_7_processEvent();
    
    // Idle:
    inline bool Idle_IN() const;
    
    ////    Framework    ////

protected :

    enum S_HttpServer_Session_Enum {
        OMNonState = 0,
        terminationstate_5 = 1,
        Run = 2,
        Registed = 3,
        state_8 = 4,
        CheckStatus = 5,
        state_7 = 6,
        Idle = 7
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    int Run_subState;
    
    int state_8_subState;
    
    int state_8_active;
    
    IOxfTimeout* state_8_timeout;
    
    int state_7_subState;
    
    int state_7_active;
};

inline bool S_HttpServer_Session::rootState_IN() const {
    return true;
}

inline bool S_HttpServer_Session::rootState_isCompleted() {
    return ( IS_IN(terminationstate_5) );
}

inline bool S_HttpServer_Session::terminationstate_5_IN() const {
    return rootState_subState == terminationstate_5;
}

inline bool S_HttpServer_Session::Run_IN() const {
    return rootState_subState == Run;
}

inline bool S_HttpServer_Session::Registed_IN() const {
    return Run_subState == Registed;
}

inline bool S_HttpServer_Session::state_8_IN() const {
    return Registed_IN();
}

inline bool S_HttpServer_Session::CheckStatus_IN() const {
    return state_8_subState == CheckStatus;
}

inline bool S_HttpServer_Session::state_7_IN() const {
    return Registed_IN();
}

inline bool S_HttpServer_Session::Idle_IN() const {
    return Run_subState == Idle;
}

#endif
/*********************************************************************
	File Path	: ../../src/HttpServer/test/S_HttpServer_Session.h
*********************************************************************/
