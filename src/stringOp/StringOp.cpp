//
// Created by mertacel on 02.12.2018.
//

#include "StringOp.hpp"

std::mutex mtxString;
StringOp *StringOp::INSTANCE = 0;


StringOp *StringOp::getInstance() {
    if (INSTANCE == 0) {
        mtxString.lock();
        if (INSTANCE == 0) {
            INSTANCE = new StringOp();
        }
        mtxString.unlock();
    }
    return INSTANCE;
}

std::vector<std::string> StringOp::splitString(std::string getString, std::string getRegex) {
    std::regex regex(getRegex);
    return {
            std::sregex_token_iterator(getString.begin(), getString.end(), regex, -1),
            std::sregex_token_iterator()};
}

std::unordered_map<std::string, std::string> StringOp::parseUrlQuery(std::string &url) {
    std::string decodedURL(urlDecode(url));
    decodedURL = decodedURL.substr(2);
    std::vector<std::string> getParsedVector = splitString(decodedURL, "&");
    std::unordered_map<std::string, std::string> queryParam;
    for (std::vector<std::string>::iterator it = getParsedVector.begin(); it != getParsedVector.end(); it++) {
        std::vector<std::string> getData(splitString(*it, "="));
        if (getData.size() >= 2) {
            queryParam.insert(make_pair(getData.at(0), getData.at(1)));
        }
    }
    return queryParam;
}

std::string StringOp::urlDecode(std::string &url) {
    std::string totalText, decodedCharacter;
    int encodedCharacterNumeric;
    for (size_t i = 0; i < url.length(); i++) {
        if (int(url[i]) == 37)
        {
            sscanf(url.substr(i + 1, 2).c_str(), "%x", &encodedCharacterNumeric);
            decodedCharacter = static_cast<char>(encodedCharacterNumeric);
            totalText += decodedCharacter;
            i = i + 2;
        }
        else
        {
            totalText += url[i];
        }
    }
    return (totalText);
}
