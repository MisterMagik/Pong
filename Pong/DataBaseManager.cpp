#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager() {
    this->driver = nullptr;
    this->con = nullptr;
}

DatabaseManager::~DatabaseManager() {
    this->disconnect();
}

bool DatabaseManager::connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database) {
    try {
        this->driver = sql::mysql::get_mysql_driver_instance();
        this->con = this->driver->connect(host, user, password);
        this->con->setSchema(database);
        std::cout << "Polaczono z baza danych MySQL pomyslnie!" << std::endl;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Blad polaczenia z MySQL: " << e.what() << std::endl;
        return false;
    }
}

void DatabaseManager::saveScore(int player1Score, int player2Score) {
    if (!this->con) return;
    try {
        sql::PreparedStatement* pstmt;
        pstmt = this->con->prepareStatement("INSERT INTO match_history (player1_score, player2_score, match_date) VALUES (?, ?, NOW())");
        pstmt->setInt(1, player1Score);
        pstmt->setInt(2, player2Score);
        pstmt->execute();
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Blad podczas zapisu wyniku: " << e.what() << std::endl;
    }
}

bool DatabaseManager::registerUser(const std::string& username, const std::string& password) {
    if (!this->con) return false;
    try {
        sql::PreparedStatement* pstmt = this->con->prepareStatement(
            "INSERT INTO users (username, password) VALUES (?, ?)"
        );
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        pstmt->execute();
        delete pstmt;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Rejestracja nieudana (Login zajety): " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::loginUser(const std::string& username, const std::string& password) {
    if (!this->con) return false;
    try {
        sql::PreparedStatement* pstmt = this->con->prepareStatement(
            "SELECT id FROM users WHERE username = ? AND password = ?"
        );
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        sql::ResultSet* res = pstmt->executeQuery();

        bool success = res->next();

        delete res;
        delete pstmt;
        return success;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Blad logowania: " << e.what() << std::endl;
        return false;
    }
}

void DatabaseManager::disconnect() {
    if (this->con) {
        delete this->con;
        this->con = nullptr;
    }
}