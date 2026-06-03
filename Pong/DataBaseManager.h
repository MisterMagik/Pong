#pragma once
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>

class DatabaseManager {
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

public:
    DatabaseManager();
    ~DatabaseManager();

    bool connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database);
    void saveScore(int player1Score, int player2Score);
    void disconnect();
};