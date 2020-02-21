/********************************************************************
	Rhapsody	: 8.4 
	Login		: kqbi
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_HttpServer_Session
//!	Generated Date	: Fri, 17, Jan 2020  
	File Path	: ../../src/HttpServer/test/S_HttpServer_Session.cpp
*********************************************************************/

#include <omthread.h>
#include "S_HttpServer_Session.h"
#include <S_HttpServer_MainSession.h>
//## package HttpServerTest

//## class S_HttpServer_Session
S_HttpServer_Session::S_HttpServer_Session(std::string& sessionId, IOxfActive* theActiveContext) : _keepAlivePollTime(60), _keepAliveTimeoutTimes(0), _mainSession(0), _sessionId(sessionId) {
    setActiveContext(theActiveContext, false);
    initStatechart();
    //#[ operation S_HttpServer_Session(std::string&)
    //#]
}

S_HttpServer_Session::~S_HttpServer_Session() {
    //#[ operation ~S_HttpServer_Session()
    //#]
    cancelTimeouts();
}

void S_HttpServer_Session::checkKeepAliveTimeout() {
    //#[ operation checkKeepAliveTimeout()
    if (++_keepAliveTimeoutTimes >= 3) {
        _mainSession->removeSession(_sessionId);
        destroy();
    }
    //#]
}

void S_HttpServer_Session::destroyWait() {
    //#[ operation destroyWait()
    //#]
}

void S_HttpServer_Session::execProcessiVMSProtocol() {
    //#[ operation execProcessiVMSProtocol()
    #if 0
    switch (protocol->GetMsgType()) {
    case iVMS_Msg_Type_RegisterReq: {
        LOG_DEBUG("execProcessiVMSProtocol iVMS_Msg_Type_RegisterReq.");
        _keepAlivePollTime = iVMSUtil::String2Int(((iVMSRegisterReq*)protocol)->GetBodyValue(IVMS_TAG_KeepAlive));
        _connection->_terminalType = (iVMSTerminalType)iVMSUtil::String2Int(((iVMSRegisterReq*)protocol)->
                                                                           GetBodyValue(IVMS_TAG_TerminalType));
        if(_connection->_terminalType == iVMS_Terminal_Type_StreamMedia) {
            _connection->_remoteIpAddress = ((iVMSRegisterReq*)protocol)->GetBodyValue(IVMS_TAG_IP);
            _connection->_port = iVMSUtil::String2Int(((iVMSRegisterReq*)protocol)->GetBodyValue(IVMS_TAG_Port));
        }
        GEN(evRegiterSuccess);
        sendRegisterRes();
        if (_connection->_terminalType != iVMS_Terminal_Type_StreamMedia) {
            sendLocalDomainInfoNotify();
            sendExteriorDomainInfoNotify();
        }
        delete protocol;
    }
        break;
    case iVMS_Msg_Type_KeepAliveReq:
        LOG_DEBUG("Rest_ConnectionService iVMS_Msg_Type_KeepAliveReq.");
        _keepAliveTimeoutTimes = 0;
        sendKeepAliveRes();
        delete protocol;
        break;
    case iVMS_Msg_Type_UpdateLocalDomainInfoReq: {
        LOG_DEBUG("Rest_ConnectionService iVMS_Msg_Type_UpdateLocalDomainInfoReq.");
        int errorCode = 200;
        if (!_connection->_server.setLocalDomainInfo(protocol)) {
            errorCode = IVMS_ERROR_DEVICE_ADD_FAILED;
            LOG_ERROR("IVMS_ERROR_DEVICE_ADD_FAILED.");
        }
        sendUpdateLocalDomainInfoRes(errorCode);
        if (errorCode == 200)
            _connection->_server.GEN(evRestartServer);
        delete protocol;
    }
        break;
    case iVMS_Msg_Type_AddExteriorDomainReq: {
        LOG_DEBUG("Rest_ConnectionService iVMS_Msg_Type_AddUserReq.");
        int errorCode = 200;
        if (!_connection->_server._config->addExteriorDomain(
                    ((iVMSAddExteriorDomainReq*)protocol)->exteriorDomainInfo)) {
            errorCode = IVMS_ERROR_DEVICE_ADD_FAILED;
            LOG_ERROR("IVMS_ERROR_DEVICE_ADD_FAILED.");
        } else
            sendExteriorDomainInfoNotify();
        sendAddExteriorDomainRes(errorCode);
        delete protocol;
    }
        break;
    case iVMS_Msg_Type_RemoveExteriorDomainReq: {
        LOG_DEBUG("Rest_ConnectionService iVMS_Msg_Type_RemoveUserReq.");
        int errorCode = 200;
        if (!_connection->_server._config->eraseExteriorDomain(
                    ((iVMSRemoveExteriorDomainReq*)protocol)->m_strDeviceId,
                    ((iVMSRemoveExteriorDomainReq*)protocol)->m_eUserType)) {
            errorCode = IVMS_ERROR_DEVICE_REMOVE_FAILED;
            LOG_ERROR("IVMS_ERROR_DEVICE_REMOVE_FAILED.");
        }
        sendRemoveExteriorDomainRes(errorCode);
        sendExteriorDomainInfoNotify();
        delete protocol;
    }
        break;
    case iVMS_Msg_Type_UpdateExteriorDomaineq:{
    	LOG_DEBUG("Rest_ConnectionService iVMS_Msg_Type_RemoveUserReq.");
    	string strDeviceId = protocol->GetSerial();
    	_connection->_server._abstractDb->eraseChannel(strDeviceId.c_str());
    	_connection->_server._abstractDb->eraseOrganization(strDeviceId.c_str());
    	_connection->_server.catalogQueryOnce(strDeviceId);
    	delete protocol;
    }
    	break;
    default:
        _connection->_server._restConnectionServer->_smmMessageCallback(_connection->_connectionId, protocol);
        break;
    }
    #endif
    //#]
}

void S_HttpServer_Session::setMainSession(S_HttpServer_MainSession* mainSession) {
    //#[ operation setMainSession(S_HttpServer_MainSession*)
    _mainSession = mainSession;
    _mainSession->addSession(this);
    //#]
}

bool S_HttpServer_Session::startBehavior() {
    bool done = false;
    done = OMReactive::startBehavior();
    return done;
}

void S_HttpServer_Session::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    Run_subState = OMNonState;
    state_8_subState = OMNonState;
    state_8_active = OMNonState;
    state_8_timeout = NULL;
    state_7_subState = OMNonState;
    state_7_active = OMNonState;
}

void S_HttpServer_Session::cancelTimeouts() {
    cancel(state_8_timeout);
}

bool S_HttpServer_Session::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(state_8_timeout == arg)
        {
            state_8_timeout = NULL;
            res = true;
        }
    return res;
}

void S_HttpServer_Session::rootState_entDef() {
    {
        Run_entDef();
    }
}

IOxfReactive::TakeEventStatus S_HttpServer_Session::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Idle
        case Idle:
        {
            if(IS_EVENT_TYPE_OF(evRegiterSuccess_HttpServerTest_id))
                {
                    Registed_entDef();
                    res = eventConsumed;
                }
            
            if(res == eventNotConsumed)
                {
                    res = Run_handleEvent();
                }
        }
        break;
        // State Registed
        case Registed:
        {
            res = Registed_processEvent();
        }
        break;
        
        default:
            break;
    }
    return res;
}

void S_HttpServer_Session::Run_entDef() {
    rootState_subState = Run;
    Run_subState = Idle;
    rootState_active = Idle;
}

IOxfReactive::TakeEventStatus S_HttpServer_Session::Run_handleEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    if(IS_EVENT_TYPE_OF(evDestroyConnectionService_HttpServerTest_id))
        {
            switch (Run_subState) {
                // State Registed
                case Registed:
                {
                    Registed_exit();
                }
                break;
                default:
                    break;
            }
            Run_subState = OMNonState;
            rootState_subState = terminationstate_5;
            rootState_active = terminationstate_5;
            //#[ state terminationstate_5.(Entry) 
            destroy();
            //#]
            res = eventConsumed;
        }
    
    return res;
}

void S_HttpServer_Session::Registed_entDef() {
    Run_subState = Registed;
    rootState_active = Registed;
    state_8_entDef();
}

void S_HttpServer_Session::Registed_exit() {
    state_7_subState = OMNonState;
    // State CheckStatus
    if(state_8_subState == CheckStatus)
        {
            cancel(state_8_timeout);
        }
    state_8_subState = OMNonState;
    
}

IOxfReactive::TakeEventStatus S_HttpServer_Session::Registed_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State state_8
    if(state_8_processEvent() != eventNotConsumed)
        {
            res = eventConsumed;
            if(!IS_IN(Registed))
                {
                    return res;
                }
        }
    if(res == eventNotConsumed)
        {
            res = Registed_handleEvent();
        }
    return res;
}

IOxfReactive::TakeEventStatus S_HttpServer_Session::Registed_handleEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    res = Run_handleEvent();
    return res;
}

void S_HttpServer_Session::state_8_entDef() {
    
    state_8_subState = CheckStatus;
    state_8_active = CheckStatus;
    //#[ state Run.Registed.state_8.CheckStatus.(Entry) 
    checkKeepAliveTimeout();
    //#]
    state_8_timeout = scheduleTimeout(_keepAlivePollTime*1000, NULL);
}

IOxfReactive::TakeEventStatus S_HttpServer_Session::state_8_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State CheckStatus
    if(state_8_active == CheckStatus)
        {
            if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
                {
                    if(getCurrentEvent() == state_8_timeout)
                        {
                            cancel(state_8_timeout);
                            state_8_subState = CheckStatus;
                            state_8_active = CheckStatus;
                            //#[ state Run.Registed.state_8.CheckStatus.(Entry) 
                            checkKeepAliveTimeout();
                            //#]
                            state_8_timeout = scheduleTimeout(_keepAlivePollTime*1000, NULL);
                            res = eventConsumed;
                        }
                }
            
            
        }
    return res;
}

IOxfReactive::TakeEventStatus S_HttpServer_Session::state_7_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    return res;
}

/*********************************************************************
	File Path	: ../../src/HttpServer/test/S_HttpServer_Session.cpp
*********************************************************************/
