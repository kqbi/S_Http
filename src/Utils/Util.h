//
// Created by kqbi on 2020/2/28.
//

#ifndef S_HTTP_UTIL_H
#define S_HTTP_UTIL_H

#include <string>
#include <boost/utility/string_view.hpp>

namespace S_Http {
    std::string getNewConnectionId();

    std::string FindField(const char *buf, const char *start, const char *end, int bufSize = 0);

    std::string base64Encode(std::uint8_t const *data, std::size_t len);

    std::string base64Encode(boost::string_view s);

    std::string base64Eecode(boost::string_view data);

    std::string urldecode(std::string &str_source);

    std::string urlencode(std::string &str_source);

    const char* Strskip(const char* s);
}
#endif //S_HTTP_UTIL_H
