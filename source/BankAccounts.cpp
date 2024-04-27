#include "../include/BankAccounts.h"

// BankAccount.cpp
BankAccounts::BankAccounts(){
    _database = database();
}

bool BankAccounts::create(clli& personID, cld& balance){
    const string query = "INSERT INTO " + _name + " (person_id, balance) VALUES (?, ?);";
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _error = "Error preparing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, personID);
    sqlite3_bind_double(stmt, 2, balance);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        _error = "Error executing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool BankAccounts::remove(clli& id){
    char* messageError;
    const string sql = "DELETE FROM " + _name + " WHERE ID = " + to_string(id) + ";";

    int exit = sqlite3_exec(_database, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error Deleting Record" << endl;
        sqlite3_free(messageError);
        return false;
    } else {
        return true;
    }
}

bool BankAccounts::update(clli& id, cld& newBalance){
    const string sql = "UPDATE " + _name + " SET balance = ? WHERE ID = ?;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Error Preparing Statement" << endl;
        return false;
    }

    sqlite3_bind_double(stmt, 1, newBalance);
    sqlite3_bind_int64(stmt, 2, id);

    int exit = sqlite3_step(stmt);

    if (exit != SQLITE_DONE) {
        cerr << "Error Updating Record" << endl;
        sqlite3_finalize(stmt);
        return false;
    } else {
        sqlite3_finalize(stmt);
        return true;
    }
}

BankAccount BankAccounts::read(clli& id){
    sqlite3_stmt *stmt;
    string sql = "SELECT * FROM " + _name + " WHERE id = ?";
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int64(stmt, 1, id);    
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            clli id = sqlite3_column_int64(stmt, 0);
            clli personID = sqlite3_column_int64(stmt, 1);
            cld balance = sqlite3_column_double(stmt, 2);
            sqlite3_finalize(stmt);
            return BankAccount(id, personID, balance);
        }
    }
    sqlite3_finalize(stmt);
    return BankAccount(-1, -1, -1);
}