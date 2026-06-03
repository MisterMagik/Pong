-- 1. Tworzenie bazy danych (jeśli jeszcze nie istnieje)
CREATE DATABASE IF NOT EXISTS pong_db;
USE pong_db;

-- 2. Tworzenie tabeli użytkowników (Logowanie i Rejestracja)
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE, -- UNIQUE blokuje rejestrację dwóch takich samych nicków
    password VARCHAR(255) NOT NULL,       -- Miejsce na hasło
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- 3. Tworzenie tabeli historii meczów (Zapisywanie wyników)
CREATE TABLE IF NOT EXISTS match_history (
    id INT AUTO_INCREMENT PRIMARY KEY,
    player1_score INT NOT NULL,
    player2_score INT NOT NULL,
    match_date DATETIME NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;