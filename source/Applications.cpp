#include "../include/Applications.h"

Applications::Applications(){
    _database = database();
}

bool Applications::create(clli& personID, clli& scholarshipID, clli& statusID){
    const string query = "INSERT INTO " + _name + " (person_id, scholarship_id, status_id) VALUES (?, ?, ?);";
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _error = "Error preparing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, personID);
    sqlite3_bind_int(stmt, 2, scholarshipID);
    sqlite3_bind_int(stmt, 3, statusID);

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

bool Applications::remove(clli& id){
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

bool Applications::update(clli& id, clli& newPersonID, clli& newScholarshipID, clli& newStatusID){
    const string sql = "UPDATE " + _name + " SET person_id = ?, scholarship_id = ?, status_id = ? WHERE ID = ?;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Error Preparing Statement" << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, newPersonID);
    sqlite3_bind_int(stmt, 2, newScholarshipID);
    sqlite3_bind_int(stmt, 3, newStatusID);
    sqlite3_bind_int64(stmt, 4, id);

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

Application Applications::read(clli& id){
    sqlite3_stmt *stmt;
    string sql = "SELECT * FROM " + _name + " WHERE id = ?";
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int64(stmt, 1, id);    
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            ll int id = sqlite3_column_int64(stmt, 0);
            ll int personID = sqlite3_column_int64(stmt, 1);
            ll int scholarshipID = sqlite3_column_int64(stmt, 2);
            ll int statusID = sqlite3_column_int64(stmt, 3);
            string createDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            sqlite3_finalize(stmt);
            return Application(id, personID, scholarshipID, statusID, createDate);
        }
    }
    sqlite3_finalize(stmt);
    return Application(-1, -1, -1, -1, "-1");
}
