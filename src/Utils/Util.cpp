//
// Created by kqbi on 2020/2/28.
//

#include "Util.h"
#include <boost/beast/core/detail/base64.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#if defined(__linux__)
#include <uuid/uuid.h>
#endif
namespace S_Http {
    std::string getNewConnectionId() {
        //#[ operation getNewConnectionId()
#ifdef __linux__
        uuid_t uuid;
        char str[36];
        uuid_generate(uuid);
        uuid_unparse(uuid, str);
        return str;
#elif _WIN32
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        return boost::uuids::to_string(uuid);
#endif
        //#]
    }

    std::string FindField(const char *buf, const char *start, const char *end, int bufSize) {
        if (bufSize <= 0) {
            bufSize = strlen(buf);
        }
        const char *msg_start = buf, *msg_end = buf + bufSize;
        int len = 0;
        if (start != NULL) {
            len = strlen(start);
            msg_start = strstr(buf, start);
        }
        if (msg_start == NULL) {
            return "";
        }
        msg_start += len;
        if (end != NULL) {
            msg_end = strstr(msg_start, end);
            if (msg_end == NULL) {
                return "";
            }
        }
        return std::string(msg_start, msg_end);
    }

    std::string base64Encode(std::uint8_t const *data, std::size_t len) {
        std::string dest;
        dest.resize(boost::beast::detail::base64::encoded_size(len));
        dest.resize(boost::beast::detail::base64::encode(&dest[0], data, len));
        return dest;
    }

    std::string base64Encode(boost::string_view s) {
        return base64Encode(reinterpret_cast <
                                    std::uint8_t const *> (s.data()), s.size());
    }

    std::string base64Decode(boost::string_view data) {
        std::string dest;
        dest.resize(boost::beast::detail::base64::decoded_size(data.size()));
        auto const result = boost::beast::detail::base64::decode(
                &dest[0], data.data(), data.size());
        dest.resize(result.first);
        return dest;
    }

    static int php_htoi(char *s) {
        int value;
        int c;

        c = ((unsigned char *) s)[0];
        if (isupper(c))
            c = tolower(c);
        value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

        c = ((unsigned char *) s)[1];
        if (isupper(c))
            c = tolower(c);
        value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

        return (value);
    }

    std::string urldecode(std::string &str_source) {
        char const *in_str = str_source.c_str();
        int in_str_len = strlen(in_str);
        int out_str_len = 0;
        std::string out_str = "";
        char *str;

        str = strdup(in_str);
        char *dest = str;
        char *data = str;

        while (in_str_len--) {
            if (*data == '+') {
                *dest = ' ';
            } else if (*data == '%' && in_str_len >= 2 && isxdigit((int) *(data + 1))
                       && isxdigit((int) *(data + 2))) {
                *dest = (char) php_htoi(data + 1);
                data += 2;
                in_str_len -= 2;
            } else {
                *dest = *data;
            }
            data++;
            dest++;
        }
        *dest = '\0';
        out_str_len = dest - str;
        out_str = str;
        free(str);
        return out_str;
    }

    std::string urlencode(std::string &str_source) {
        char const *in_str = str_source.c_str();
        int in_str_len = strlen(in_str);
        int out_str_len = 0;
        std::string out_str;
        register unsigned char c;
        unsigned char *to, *start;
        unsigned char const *from, *end;
        unsigned char hexchars[] = "0123456789ABCDEF";

        from = (unsigned char *) in_str;
        end = (unsigned char *) in_str + in_str_len;
        start = to = (unsigned char *) malloc(3 * in_str_len + 1);

        while (from < end) {
            c = *from++;

            if (c == ' ') {
                *to++ = '+';
            } else if ((c < '0' && c != '-' && c != '.') ||
                       (c < 'A' && c > '9') ||
                       (c > 'Z' && c < 'a' && c != '_') ||
                       (c > 'z')) {
                to[0] = '%';
                to[1] = hexchars[c >> 4];
                to[2] = hexchars[c & 15];
                to += 3;
            } else {
                *to++ = c;
            }
        }
        *to = 0;

        out_str_len = to - start;
        out_str = (char *) start;
        free(start);
        return out_str;
    }

    const char* Strskip(const char* s) {
        assert(s);
        while (' ' == *s || '\t' == *s) ++s;
        return s;
    }
}