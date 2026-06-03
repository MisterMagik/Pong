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

        // Wybór bazy danych
        this->con->setSchema(database);
        std::cout << "Polaczono z baza danych MySQL pomyœlnie!" << std::endl;
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
        // Przyk³ad zapisu wyniku meczu przy u¿yciu Prepared Statement (ochrona przed SQL Injection)
        sql::PreparedStatement* pstmt;
        pstmt = this->con->prepareStatement("INSERT INTO match_history (player1_score, player2_score, match_date) VALUES (?, ?, NOW())");

        pstmt->setInt(1, player1Score);
        pstmt->setInt(2, player2Score);

        pstmt->execute();
        delete pstmt;
        std::cout << "Wynik meczu zapisany w bazie." << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Blad podczas zapisu do bazy: " << e.what() << std::endl;
    }
}

void DatabaseManager::disconnect() {
    if (this->con) {
        delete this->con;
        this->con = nullptr;
    }
}