//
// Created by mertacel on 01.12.2018.
//

#ifndef DATA_FORMATING_MYSQL_HPP
#define DATA_FORMATING_MYSQL_HPP

#include <string>
#include <mutex>
#include <vector>


#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "../stringOp/StringOp.hpp"


class MySQL {
private:
    static MySQL *INSTANCE;
    sql::Driver *driver;
    sql::Connection *con;
    sql::ResultSet *res;

protected:
    MySQL() {}

    MySQL(const MySQL &) = delete;

    MySQL &operator=(const MySQL &) = delete;

    ~MySQL();

public:
    static MySQL *getInstance();

    void connectDb(std::string host, std::string userName, std::string password);

    void selectDatabase(std::string dbName);

    std::string getSelectedDatabase();

    void createTable(std::string dbName, std::string column);

    void insertData(std::string tableName, std::string columnName, std::string value);


    void selectData(std::string tableName, std::string selectParam);


};

#endif //DATA_FORMATING_MYSQL_HPP
