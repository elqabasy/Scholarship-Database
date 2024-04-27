#include "../include/Scholarships.h"

Scholarships::Scholarships(){
    _database = database();
}

bool Scholarships::create(cs& description, clli& fieldID, cld& budget, cs& degree){
    const string query = "INSERT INTO " + _name + " (description, field_id, budget, degree) VALUES (?, ?, ?, ?);";
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _error = "Error preparing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, fieldID);
    sqlite3_bind_double(stmt, 3, budget);
    sqlite3_bind_text(stmt, 4, degree.c_str(), -1, SQLITE_STATIC);

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

bool Scholarships::remove(clli& id){
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

bool Scholarships::update(clli& id, cs& newDescription, clli& newFieldID, cld& newBudget, cs& newDegree){
    const string sql = "UPDATE " + _name + " SET description = ?, field_id = ?, budget = ?, degree = ? WHERE ID = ?;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Error Preparing Statement" << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, newDescription.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, newFieldID);
    sqlite3_bind_double(stmt, 3, newBudget);
    sqlite3_bind_text(stmt, 4, newDegree.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 5, id);

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

Scholarship Scholarships::read(clli& id){
    sqlite3_stmt *stmt;
    string sql = "SELECT * FROM " + _name + " WHERE id = ?";
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int64(stmt, 1, id);    
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            clli id = sqlite3_column_int64(stmt, 0);
            cs description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            clli fieldID = sqlite3_column_int64(stmt, 2);
            cld budget = sqlite3_column_double(stmt, 3);
            cs degree = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            sqlite3_finalize(stmt);
            return Scholarship(id, description, fieldID, budget, degree);
        }
    }
    sqlite3_finalize(stmt);
    return Scholarship(-1, "-1", -1, -1, "-1");
}

