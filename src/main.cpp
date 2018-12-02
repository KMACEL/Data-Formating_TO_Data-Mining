#include <iostream>
#include <string>
#include <fstream>
#include "db/MySQL.hpp"
#include "system/SystemCommand.hpp"
#include "stringOp/StringOp.hpp"

using namespace std;


int main() {
    /*MySQL::getInstance()->connectDb("tcp://127.0.0.1:3306", "root", "12345678");
    MySQL::getInstance()->selectDatabase("PingInfo");
   //MySQL::getInstance()->createTable("t1", "id INT");
    MySQL::getInstance()->insertData("t1", "id", "5");
    MySQL::getInstance()->insertData("t1", "id", "12");
    MySQL::getInstance()->selectData("t1","id");*/

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
                    cout << StringOp::getInstance()->parseUrlQuery(splitPing).at("id") << endl;
                }
            }
            myfile.close();
        }

        // SystemCommand::getInstance()->remove(getFileName);
    }

    return 0;
}