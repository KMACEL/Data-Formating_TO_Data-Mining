#include <iostream>
#include <string>
#include <fstream>
#include "db/MySQL.hpp"
#include "system/SystemCommand.hpp"
#include "stringOp/StringOp.hpp"


using namespace std;


int main() {

    MySQL::getInstance()->connectDb("tcp://127.0.0.1:3306", "root", "12345678");
    MySQL::getInstance()->selectDatabase("PingInfo");
    //MySQL::getInstance()->createTable("iPing", "id CHAR(20) , j INT, w INT, t DATETIME");
    // MySQL::getInstance()->insertData("iPing", "id,j,w,t","867377021037845,17278359,24603718,2018-10-28:00:59:34");
    // MySQL::getInstance()->selectData("pingDB","id");

    //system("gunzip /home/mert.acel/MA/TR-Cpp/20181020.gz");

    SystemCommand::getInstance()->setPath("/home/mertacel/MA/iTaksiPing/");
    vector<string> getFile = SystemCommand::getInstance()->getInFile();
    for (vector<string>::iterator it = getFile.begin(); it != getFile.end(); it++) {
        //SystemCommand::getInstance()->extractGunzip(*it);

        string getFileName = StringOp::getInstance()->splitString(*it, ".gz").at(0);

        cout << "File : " << getFileName << endl;

        string line;
        ifstream myfile(SystemCommand::getInstance()->getPath() + getFileName, ios::binary);
        if (myfile.is_open()) {
            while (!myfile.eof()) {
                getline(myfile, line);
                string splitPing = StringOp::getInstance()->splitString(line, " ").at(6);
                if ((splitPing.at(0) == '/') && (splitPing.at(1) == '?')) {
                    unordered_map<string, string> getParam = StringOp::getInstance()->parseUrlQuery(splitPing);

                    if ((getParam.find("id") != getParam.end()) && (getParam.find("J") != getParam.end()) &&
                        (getParam.find("W") != getParam.end()) && (getParam.find("T") != getParam.end())) {

                        if ((atoi(getParam.at("J").c_str()) > 0) && atoi(getParam.at("T").c_str()) > 0) {
                            cout << getParam.at("id")
                                 << " - " << getParam.at("J") << " - " << getParam.at("W")
                                 << " - " << getParam.at("T") << endl;
                            MySQL::getInstance()->insertData("pingDB", "id,j,w,t",
                                                             getParam.at("id") + "," + getParam.at("J") + "," +
                                                             getParam.at("W") + "," + getParam.at("T"));
                        }
                    }
                }
            }
            myfile.close();
        }

        // SystemCommand::getInstance()->remove(getFileName);
    }

    return 0;
}