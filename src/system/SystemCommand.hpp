//
// Created by mertacel on 02.12.2018.
//

#ifndef DATA_FORMATING_SYSTEMCOMMAND_HPP
#define DATA_FORMATING_SYSTEMCOMMAND_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <mutex>
#include <vector>
#include "../stringOp/StringOp.hpp"


class SystemCommand {
private :
    static SystemCommand *INSTANCE;
    std::string path;

protected:
    SystemCommand() {}

    SystemCommand(const SystemCommand &) = delete;

    SystemCommand &operator=(const SystemCommand &) = delete;

    ~SystemCommand();

public:
    static SystemCommand *getInstance();

    void setPath(std::string);

    std::string getPath();

    void executeCommand(std::string command);

    std::string getCommandReturnValue(std::string cmd);

    std::vector<std::string> getInFile();


    std::vector<std::string> getInFile(std::string path);


    void extractGunzip(std::string file);

    void extractGunzip(std::string filePath, std::string file);

    void remove(std::string file);

    void remove(std::string filePath, std::string file);

};


#endif //DATA_FORMATING_SYSTEMCOMMAND_HPP
