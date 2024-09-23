#ifndef BASE64_H
#define BASE64_H

#include <string>

namespace b64 {
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                            "abcdefghijklmnopqrstuvwxyz"
                                            "0123456789+/";

    std::string encode(const std::string &);
    std::string decode(const std::string &);
}  // namespace b64

#endif