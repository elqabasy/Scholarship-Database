#include "../include/Payments.h"

/* Constructor */
Payments::Payments(){
    _database = database();
}

bool Payments::create(clli& scholarship_id, clli& bank_account_id, cld& amount){
    const string query = "INSERT INTO " + _name + " (scholarship_id, bankAccount_id, amount) VALUES (?, ?, ?);";
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _error = "Error preparing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, scholarship_id);
    sqlite3_bind_int(stmt, 2, bank_account_id);
    sqlite3_bind_double(stmt, 3, amount);

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

Payment Payments::read(clli& id){
    sqlite3_stmt *stmt;
    string sql = "SELECT * FROM " + _name + " WHERE id = ?";
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int64(stmt, 1, id);    
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            ll int id = sqlite3_column_int64(stmt, 0);
            ll int scholarship_id = sqlite3_column_int64(stmt, 1);
            ll int bank_account_id = sqlite3_column_int64(stmt, 2);
            double amount = sqlite3_column_double(stmt, 3);
            string create_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            sqlite3_finalize(stmt);
            return Payment(id, scholarship_id, bank_account_id, amount, create_date);
        }
    }
    sqlite3_finalize(stmt);
    return Payment(-1, -1, -1, -1, "");
}

bool Payments::update(clli& id, cld& new_amount){
    const string sql = "UPDATE " + _name + " SET amount = ? WHERE ID = ?;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Error Preparing Statement" << endl;
        return false;
    }

    sqlite3_bind_double(stmt, 1, new_amount);
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

bool Payments::remove(clli& id){
    const string sql = "DELETE FROM " + _name + " WHERE ID = ?;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Error Preparing Statement" << endl;
        return false;
    }

    sqlite3_bind_int64(stmt, 1, id);

    int exit = sqlite3_step(stmt);

    if (exit != SQLITE_DONE) {
        cerr << "Error Deleting Record" << endl;
        sqlite3_finalize(stmt);
        return false;
    } else {
        sqlite3_finalize(stmt);
        return true;
    }
}

// Destructor
Payments::~Payments(){

}