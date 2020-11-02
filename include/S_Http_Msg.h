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
#include <boost/beast/http/string_body.hpp>
//## package HttpMsg
namespace S_Http {
//## class S_Http_Msg
    class S_Http_Msg {
    public :

        //## class S_Http_Msg::HEADER
        class HEADER {
            ////    Constructors and destructors    ////

        public :

            ~HEADER();

            ////    Attributes    ////

            unsigned long long contentLength;        //## attribute contentLength

            std::string contentType;        //## attribute contentType

            unsigned version;        //## attribute version
        };

        enum
        {
            HTTP_AUTHENTICATION_NONE = 0,
            HTTP_AUTHENTICATION_BASIC,
            HTTP_AUTHENTICATION_DIGEST,
        };

        struct http_header_www_authenticate_t
        {
            int scheme; // HTTP_AUTHENTICATION_BASIC, HTTP_AUTHENTICATION_DIGEST
            char realm[128]; // case-sensitive
            char domain[128];
            char nonce[128];
            char opaque[128];
            int stale; // 0-false, 1-true
            char algorithm[64];
            char qop[64];
            int charset; // UTF-8
            int userhash; // username hashing, 0-false(default), 1-true
            int session_variant;

            // Authorization/Proxy-Authorization only
            char cnonce[128];
            char username[128];
            char uri[256];
            char response[256];
            int nc; //char nc[9]; // 8LHEX nonce count
        };

        ////    Constructors and destructors    ////

        //## operation S_Http_Msg(std::string&,std::string&)
        S_Http_Msg(std::string &connectionId, std::string &body);

        //## operation ~S_Http_Msg()
        virtual ~S_Http_Msg();

        int AuthorizationScheme(const char* scheme, size_t bytes);

        int AuthorizationParam(struct http_header_www_authenticate_t* auth, const char* name, size_t bytes, const char* value, size_t bytes2);

        int WWWAthenticate(const char* field, struct http_header_www_authenticate_t* auth);
        ////    Attributes    ////

        HEADER _header;        //## attribute _header

        std::string _body;        //## attribute _body

        std::string _connectionId;        //## attribute _connectionId

        boost::beast::http::request<boost::beast::http::string_body> _req;

        boost::beast::http::response<boost::beast::http::string_body> _res;
    };
}
#endif
/*********************************************************************
	File Path	: ../../src/HttpMsg/S_Http_Msg.h
*********************************************************************/
