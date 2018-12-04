//
// Created by mertacel on 01.12.2018.
//

#include "MySQL.hpp"


std::mutex mtxMysql;
MySQL *MySQL::INSTANCE = 0;


MySQL *MySQL::getInstance() {
    if (INSTANCE == 0) {
        mtxMysql.lock();
        if (INSTANCE == 0) {
            INSTANCE = new MySQL();
        }
        mtxMysql.unlock();
    }
    return INSTANCE;
}

void MySQL::connectDb(std::string host, std::string userName, std::string password) {
    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect(host, userName, password);

    if (!con->isClosed()) {
        std::cout << "Connected..." << std::endl;

    }
}


void MySQL::selectDatabase(std::string dbName) {
    /* Connect to the MySQL database */
    con->setSchema(dbName);
    std::cout << "Selected Database : " << con->getSchema() << std::endl;
}

std::string MySQL::getSelectedDatabase() {
    return con->getSchema();
}

void MySQL::createTable(std::string tableName, std::string column) {
    sql::Statement *stmt = con->createStatement();
    stmt->execute("CREATE TABLE " + tableName + "(" + column + ")");
    std::cout << "Created " << std::endl;
    delete stmt;
}

void MySQL::insertData(std::string tableName, std::string columnName, std::string value) {

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Insert Data ..." << std::endl;
    sql::PreparedStatement *pstmt;

    unsigned int columnSize = StringOp::getInstance()->splitString(columnName, ",").size();
    std::vector<std::string> columnValue = StringOp::getInstance()->splitString(columnName, ",");
    std::vector<std::string> valueVector = StringOp::getInstance()->splitString(value, ",");

    std::string valuesParam;
    for (size_t i = 0; i < columnSize; i++) {
        valuesParam += ",?";
    }
    valuesParam.erase(valuesParam.begin());


    pstmt = con->prepareStatement("INSERT INTO " + tableName + "(" + columnName + ") VALUES (" + valuesParam + ")");

    for (size_t i = 0; i < columnSize; i++) {
        std::cout << columnValue.at(i) << " : " << valueVector.at(i) << std::endl;
        pstmt->setString(i + 1, valueVector.at(i));
    }

    pstmt->executeUpdate();
    delete pstmt;
    std::cout << "--------------------------------------------" << std::endl;


    /*sql::Connection *con;
sql::PreparedStatement  *prep_stmt
// ...

prep_stmt = con->prepareStatement("INSERT INTO test(id, label) VALUES (?, ?)");

prep_stmt->setInt(1, 1);
prep_stmt->setString(2, "a");
prep_stmt->execute();

prep_stmt->setInt(1, 2);
prep_stmt->setString(2, "b");
prep_stmt->execute();

delete prep_stmt;
delete con;
     */
}

void MySQL::selectData(std::string tableName, std::string selectParam) {
    sql::PreparedStatement *pstmt;

    /* Select in ascending order */
    pstmt = con->prepareStatement("SELECT * FROM " + tableName + " ORDER BY " + selectParam + " ASC");
    res = pstmt->executeQuery();

    /* Fetch in reverse = descending order! */
    res->afterLast();
    while (res->previous()) {
        std::cout << "\t... MySQL counts: " << res->getInt(selectParam) << std::endl;
    }

    delete res;
    delete pstmt;
}

