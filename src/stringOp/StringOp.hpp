//
// Created by mertacel on 02.12.2018.
//

#ifndef DATA_FORMATING_STRINGOP_HPP
#define DATA_FORMATING_STRINGOP_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <mutex>
#include <memory>


class StringOp {
private:
    static StringOp *INSTANCE;

protected:
    StringOp() {}

    StringOp(const StringOp &) = delete;

    StringOp &operator=(const StringOp &) = delete;

    ~StringOp();

public:
    static StringOp *getInstance();

    std::vector<std::string> splitString(std::string getString, std::string getRegex);

    std::unordered_map<std::string, std::string> parseUrlQuery(std::string &url);

    std::string urlDecode(std::string &url);
};


#endif //DATA_FORMATING_STRINGOP_HPP
