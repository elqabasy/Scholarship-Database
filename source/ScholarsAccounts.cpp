#include "../include/ScholarsAccounts.h"


/* Constructor */
Scholars::Scholars(){
    _database = database();
}


/* Functionality */
bool Scholars::create(clli& personID, cs& username, cs& password){
    const string query = "INSERT INTO " + _name + " (person_id, username, password) VALUES (?, ?, ?);";
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _error = "Error preparing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, personID);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC);

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

Scholar Scholars::read(clli& id){
    // get data by id
    sqlite3_stmt *stmt;
    string sql = "SELECT * FROM " + _name + " WHERE id = ?";
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int64(stmt, 1, id);    
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            ll int id = sqlite3_column_int64(stmt, 0);
            ll int personID = sqlite3_column_int64(stmt, 1);
            string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            sqlite3_finalize(stmt);
            return Scholar(id, personID, username, password);
        }
    }
    sqlite3_finalize(stmt);
    return Scholar(-1, -1, "", "");
}
Scholar Scholars::read(cs& name){
    // get data by id
    sqlite3_stmt *stmt;
    string sql = "SELECT * FROM " + _name + " WHERE name = ?";
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);    
        cout << "after" << endl;
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            ll int id = sqlite3_column_int64(stmt, 0);
            ll int personID = sqlite3_column_int64(stmt, 1);
            string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            sqlite3_finalize(stmt);
            return Scholar(id, personID, username, password);
        }
    }
    sqlite3_finalize(stmt);
    return Scholar(-1, -1, "", "");
}

bool Scholars::update(clli& id, cs& newUsername = "-1", cs& newPassword = "-1"){
    const string sql = "UPDATE " + _name + " SET name = ?, username = ?, password = ? WHERE ID = ?;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Error Preparing Statement" << endl;
        return false;
    }

    if(newUsername != "-1"){
        sqlite3_bind_text(stmt, 1, newUsername.c_str(), -1, SQLITE_STATIC);
    }
    if(newPassword != "-1"){
        sqlite3_bind_text(stmt, 2, newPassword.c_str(), -1, SQLITE_STATIC);
    }

    sqlite3_bind_int64(stmt, 6, id);

    int exit = sqlite3_step(stmt);

    if (exit != SQLITE_DONE) {
        cerr << "Error Updating Record" << endl;
        sqlite3_finalize(stmt);
        return false;
    } else {
        // cout << "Record Updated Successfully!" << endl;
        sqlite3_finalize(stmt);
        return true;
    }
}

bool Scholars::remove(cs& name){
    char* messageError;
    const string sql = "DELETE FROM " + _name + " WHERE name = " + name + ";";

    int exit = sqlite3_exec(_database, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error Deleting Record" << endl;
        sqlite3_free(messageError);
        return false;
    } else {
        return true;
    }
}
bool Scholars::remove(clli& id){
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

// Destructor
Scholars::~Scholars(){
    
}