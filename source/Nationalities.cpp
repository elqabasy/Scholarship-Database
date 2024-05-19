#include "../include/Nationalities.h"


/* Constructor */
Nationalities::Nationalities(){
    _database = database();
}

/* Functionality */
bool Nationalities::create(cs& name) {
    cs query = "INSERT INTO " + _name + " (name) VALUES (?);";
    
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

string Nationalities::read(const lli& id){
    sqlite3_stmt *stmt;
    cs sql = "SELECT name FROM " + _name + " WHERE ID = " + to_string(id) + ";";
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
lli Nationalities::read(cs& name){
    sqlite3_stmt *stmt;
    string sql("SELECT ID FROM " + _name + " WHERE NAME = '" + name + "';");

    lli id = -1;
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

bool Nationalities::update(const lli& id, cs& name){
    char* messageError;
    cs sql = "UPDATE " + _name + " SET name = '" + name + "' WHERE ID = " + to_string(id) + ";";

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

bool Nationalities::remove(cs& name){
    char* messageError;
    cs sql = "DELETE FROM " + _name + " WHERE name = " + name + ";";

    int exit = sqlite3_exec(_database, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error Deleting Record" << endl;
        sqlite3_free(messageError);
        return false;
    } else {
        return true;
    }
}
bool Nationalities::remove(const lli& id){
    char* messageError;
    cs sql = "DELETE FROM" + _name + "WHERE ID = " + to_string(id) + ";";

    int exit = sqlite3_exec(_database, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error Deleting Record" << endl;
        sqlite3_free(messageError);
        return false;
    } else {
        return true;
    }
}

/* Destructor */
Nationalities::~Nationalities(){

}