#include "../include/Database.h"

// Static members
sqlite3* Database::_database = nullptr;

// Constructor
Database::Database(){
    
}

// Functionality
bool Database::open(const string& filename){
    if (sqlite3_open(filename.c_str(), &_database)) {
        _error = "Can't open database: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error;
        return false;
    }
    return true;
}
bool Database::execute(const string& sql){
    char* zErrMsg = nullptr;
    if (sqlite3_exec(_database, sql.c_str(), nullptr, nullptr, &zErrMsg) != SQLITE_OK) {
        _error =  "SQL error: ";
        _error += zErrMsg;
        cerr << _error;
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

// Setters
void Database::error(const string& error){
    _error = error;
}
void Database::database(sqlite3* database){
    _database = database;
}

// Getters
string Database::error() const{
    return _error;
}
sqlite3* Database::database() const{
    return _database;
}

// Destructor
Database::~Database(){
    if (_database) {
        sqlite3_close(_database);
    }
}