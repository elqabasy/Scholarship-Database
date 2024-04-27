#include "../include/Nationalityies.h"

Nationalities::Nationalities(){
    _database = database();
}

bool Nationalities::create(const string& name) {
    const string query = "INSERT INTO " + _name + " (name) VALUES (?);";
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _error = "Error preparing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

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

bool Nationalities::remove(const string& name){
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
bool Nationalities::remove(const ll int& id){
    char* messageError;
    const string sql = "DELETE FROM" + _name + "WHERE ID = " + to_string(id) + ";";

    int exit = sqlite3_exec(_database, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error Deleting Record" << endl;
        sqlite3_free(messageError);
        return false;
    } else {
        return true;
    }
}

bool Nationalities::update(const ll int& id, const string& name){
    char* messageError;
    const string sql = "UPDATE " + _name + " SET name = '" + name + "' WHERE ID = " + to_string(id) + ";";

    int exit = sqlite3_exec(_database, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error Updating Record" << endl;
        sqlite3_free(messageError);
        return false;
    } else {
        // cout << "Record Updated Successfully!" << endl;
        return true;
    }
}

string Nationalities::read(const ll int& id){
    sqlite3_stmt *stmt;
    const string sql = "SELECT name FROM " + _name + " WHERE ID = " + to_string(id) + ";";
    string result;

    int exit = sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, NULL);
    if (exit != SQLITE_OK) {
        cerr << "Error Reading Record" << endl;
        return "";
    } else {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        }
        sqlite3_finalize(stmt);
        return result;
    }
}
ll int Nationalities::read(const string& name){
    sqlite3_stmt *stmt;
    string sql("SELECT ID FROM " + _name + " WHERE NAME = '" + name + "';");

    ll int id = -1;
    int exit = sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, NULL);

    if (exit != SQLITE_OK) {
        cerr << "Error Reading Record" << endl;
        return id;
    } else {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            id = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
        return id;
    }

}
