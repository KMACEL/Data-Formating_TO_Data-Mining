//
// Created by mertacel on 02.12.2018.
//

#include "SystemCommand.hpp"

std::mutex mtxCommand;
SystemCommand *SystemCommand::INSTANCE = 0;

SystemCommand *SystemCommand::getInstance() {
    if (INSTANCE == 0) {
        mtxCommand.lock();
        if (INSTANCE == 0) {
            INSTANCE = new SystemCommand();
        }
        mtxCommand.unlock();
    }
    return INSTANCE;
}

void SystemCommand::setPath(std::string path) {
    this->path = path;
}

std::string SystemCommand::getPath() {
    return this->path;
}


void SystemCommand::executeCommand(std::string command) {
    system(command.c_str());
}

std::string SystemCommand::getCommandReturnValue(std::string cmd) {
    std::string data;
    FILE *stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, max_buffer, stream) != NULL) {
                data.append(buffer);
            }
        }
        pclose(stream);
    }
    return data;
}

std::vector<std::string> SystemCommand::getInFile() {
    return StringOp::getInstance()->splitString(getCommandReturnValue("ls " + this->path), "\n");
}

std::vector<std::string> SystemCommand::getInFile(std::string path) {
    return StringOp::getInstance()->splitString(getCommandReturnValue("ls " + path), "\n");
}

void SystemCommand::extractGunzip(std::string file) {
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Extracting... : " << file << std::endl;
    executeCommand("gunzip " + getPath() + file);
    std::cout << "Extracted... : " << file << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

void SystemCommand::extractGunzip(std::string filePath, std::string file) {
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Extracting... : " << file << std::endl;
    executeCommand("gunzip " + filePath + file);
    std::cout << "Extracted... : " << file << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

void SystemCommand::remove(std::string file) {
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Removing... : " << file << std::endl;
    executeCommand("rm -rf " + getPath() + file);
    std::cout << "Removed... : " << file << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}


void SystemCommand::remove(std::string filePath, std::string file) {
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Removing... : " << file << std::endl;
    executeCommand("rm -rf " + filePath + file);
    std::cout << "Removed... : " << file << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

