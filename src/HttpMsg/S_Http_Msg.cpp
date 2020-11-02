/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: DefaultComponent 
	Configuration 	: S_HTTP_Config
	Model Element	: S_Http_Msg
//!	Generated Date	: Tue, 10, Dec 2019  
	File Path	: ../../src/HttpMsg/S_Http_Msg.cpp
*********************************************************************/

#include <Util.h>
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

    int S_Http_Msg::AuthorizationScheme(const char* scheme, size_t bytes)
    {
        if (0 == strncmp(scheme, "Basic", bytes))
        {
            return HTTP_AUTHENTICATION_BASIC;
        }
        else if (0 == strncmp(scheme, "Digest", bytes))
        {
            return HTTP_AUTHENTICATION_DIGEST;
        }
        else
        {
            assert(0);
            return HTTP_AUTHENTICATION_NONE; // unknown
        }
    }

    int S_Http_Msg::AuthorizationParam(struct http_header_www_authenticate_t* auth, const char* name, size_t bytes, const char* value, size_t bytes2)
    {
        int r;

        if (0 == strncmp(name, "realm", bytes))
        {
            r = snprintf(auth->realm, sizeof(auth->realm), "%.*s", (int)bytes2, value);
            return r < 0 || r >= sizeof(auth->realm) ? (r < 0 ? r : -E2BIG) : 0;
        }
        else if (0 == strncmp(name, "domain", bytes))
        {
            r = snprintf(auth->domain, sizeof(auth->domain), "%.*s", (int)bytes2, value);
            return r < 0 || r >= sizeof(auth->domain) ? (r < 0 ? r : -E2BIG) : 0;
        }
        else if (0 == strncmp(name, "nonce", bytes))
        {
            r = snprintf(auth->nonce, sizeof(auth->nonce), "%.*s", (int)bytes2, value);
            return r < 0 || r >= sizeof(auth->nonce) ? (r < 0 ? r : -E2BIG) : 0;
        }
        else if (0 == strncmp(name, "opaque", bytes))
        {
            r = snprintf(auth->opaque, sizeof(auth->opaque), "%.*s", (int)bytes2, value);
            return r < 0 || r >= sizeof(auth->opaque) ? (r < 0 ? r : -E2BIG) : 0;
        }
        else if (0 == strncmp(name, "stale", bytes))
        {
            if (0 == strncmp(value, "true", bytes2))
            {
                auth->stale = 1;
            }
            else if ((0 == strncmp(value, "false", bytes2)) || (0 == strncmp(value, "FALSE", bytes2)))
            {
                auth->stale = 0;
            }
            else
            {
                assert(0);
                auth->stale = -1; // invalid value;
            }
        }
        else if (0 == strncmp(name, "algorithm", bytes))
        {
            r = snprintf(auth->algorithm, sizeof(auth->algorithm), "%.*s", (int)bytes2, value);
            return r < 0 || r >= sizeof(auth->algorithm) ? (r < 0 ? r : -E2BIG) : 0;
        }
        else if (0 == strncmp(name, "qop", bytes))
        {
            // TODO: split qop-options
            r = snprintf(auth->qop, sizeof(auth->qop), "%.*s", (int)bytes2, value);
            return r < 0 || r >= sizeof(auth->qop) ? (r < 0 ? r : -E2BIG) : 0;
        }
        else
        {
            // ignore
        }

        return 0;
    }

    int S_Http_Msg::WWWAthenticate(const char* field, struct http_header_www_authenticate_t* auth)
    {
        const char* name;
        const char* value;
        size_t bytes, bytes2;

        // auth-scheme
        //field = Strskip(field);
        bytes = strcspn(field, " \t\r\n"); // get scheme length
        auth->scheme = AuthorizationScheme(field, bytes);

        // auth-param
        for (field += bytes; *field; field = value + bytes2)
        {
            name = field + strspn(field, ", \t");
            bytes = strcspn(name, " \t=\r\n");

            field = Strskip(name + bytes);
            if ('=' != *field)
                break;

            value = Strskip(field + 1);
            if ('"' == *value)
            {
                value += 1; // skip \"
                bytes2 = strcspn(value, "\"");
                AuthorizationParam(auth, name, bytes, value, bytes2);

                assert('"' == value[bytes2]);
                if ('"' == value[bytes2])
                    bytes2 += 1; // skip \"
            }
            else
            {
                bytes2 = strcspn(value, ", \t\r\n");
                AuthorizationParam(auth, name, bytes, value, bytes2);
            }
        }

        return 0;
    }
}
/*********************************************************************
	File Path	: ../../src/HttpMsg/S_Http_Msg.cpp
*********************************************************************/
