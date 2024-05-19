#include "../include/Scholarships.h"

/* Constructor */
Scholarships::Scholarships(){
    _database = database();
}


/* Functionality */
bool Scholarships::create(cs& description, clli& field_id, cld& budget, cs& degree){
    const string query = "INSERT INTO " + _name + " (description, field_id, budget, degree) VALUES (?, ?, ?, ?);";
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _error = "Error preparing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, field_id);
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

Scholarship Scholarships::read(clli& id){
    sqlite3_stmt *stmt;
    string sql = "SELECT * FROM " + _name + " WHERE id = ?";
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int64(stmt, 1, id);    
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            clli id = sqlite3_column_int64(stmt, 0);
            cs description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            clli field_id = sqlite3_column_int64(stmt, 2);
            cld budget = sqlite3_column_double(stmt, 3);
            cs degree = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            sqlite3_finalize(stmt);
            return Scholarship(id, description, field_id, budget, degree);
        }
    }
    sqlite3_finalize(stmt);
    return Scholarship(-1, "-1", -1, -1, "-1");
}

bool Scholarships::update(clli& id, cs& new_description, clli& new_field_id, cld& new_budget, cs& new_degree){
    const string sql = "UPDATE " + _name + " SET description = ?, field_id = ?, budget = ?, degree = ? WHERE ID = ?;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Error Preparing Statement" << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, new_description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, new_field_id);
    sqlite3_bind_double(stmt, 3, new_budget);
    sqlite3_bind_text(stmt, 4, new_degree.c_str(), -1, SQLITE_STATIC);
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


/* Destructor */
Scholarships::~Scholarships(){

}