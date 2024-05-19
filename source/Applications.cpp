#include "../include/Applications.h"

/* Constructor */
Applications::Applications(){
    _database = database();
}

/* Functionality */ 
bool Applications::create(clli& person_id, clli& scholarship_id, clli& status_id){
    const string query = "INSERT INTO " + _name + " (person_id, scholarship_id, status_id) VALUES (?, ?, ?);";
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _error = "Error preparing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, person_id);
    sqlite3_bind_int(stmt, 2, scholarship_id);
    sqlite3_bind_int(stmt, 3, status_id);

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

Application Applications::read(clli& id){
    sqlite3_stmt *stmt;
    string sql = "SELECT * FROM " + _name + " WHERE id = ?";
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int64(stmt, 1, id);    
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            ll int id = sqlite3_column_int64(stmt, 0);
            ll int person_id = sqlite3_column_int64(stmt, 1);
            ll int scholarship_id = sqlite3_column_int64(stmt, 2);
            ll int status_id = sqlite3_column_int64(stmt, 3);
            string createDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            sqlite3_finalize(stmt);
            return Application(id, person_id, scholarship_id, status_id, createDate);
        }
    }
    sqlite3_finalize(stmt);
    return Application(-1, -1, -1, -1, "-1");
}

bool Applications::update(clli& id, clli& newperson_id, clli& new_scholarship_id, clli& newstatus_id){
    const string sql = "UPDATE " + _name + " SET person_id = ?, scholarship_id = ?, status_id = ? WHERE ID = ?;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Error Preparing Statement" << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, newperson_id);
    sqlite3_bind_int(stmt, 2, new_scholarship_id);
    sqlite3_bind_int(stmt, 3, newstatus_id);
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

Applications::~Applications(){

}