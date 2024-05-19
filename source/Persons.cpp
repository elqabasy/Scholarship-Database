#include "../include/Persons.h"


/* Constructor */
Persons::Persons(){
    _database = database();
}


/* Functionality */
bool Persons::create(cs& name, clli& nationality_id, cs& birth_date, cs& education, cld& english_score) {
    const string query = "INSERT INTO " + _name + " (name, nationality_id, birth_date, education, english_score) VALUES (?, ?, ?, ?, ?);";
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _error = "Error preparing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, nationality_id);
    sqlite3_bind_text(stmt, 3, birth_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, education.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 5, english_score);

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

Person Persons::read(clli& id){
    // get data by id
    sqlite3_stmt *stmt;
    string sql = "SELECT * FROM " + _name + " WHERE id = ?";
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int64(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            ll int id = sqlite3_column_int64(stmt, 0);
            string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            ll int nationality_id = sqlite3_column_int64(stmt, 2);
            string birth_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            string education = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            long double english_score = sqlite3_column_double(stmt, 5);
            sqlite3_finalize(stmt);
            return Person(id, name, nationality_id, birth_date, education, english_score);
        }
    }
    sqlite3_finalize(stmt);
    return Person(-1, "", -1, "", "", -1);
}
Person Persons::read(cs& name){
    /* test main */
    // get data by name
    sqlite3_stmt *stmt;
    string sql = "SELECT * FROM " + _name + " WHERE name = ?";
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            clli id = sqlite3_column_int64(stmt, 0);
            cs name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            clli nationality_id = sqlite3_column_int64(stmt, 2);
            cs birth_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            string education = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            cld english_score = sqlite3_column_double(stmt, 5);
            sqlite3_finalize(stmt);
            return Person(id, name, nationality_id, birth_date, education, english_score);
        }
    }
    sqlite3_finalize(stmt);
    return Person(-1, "", -1, "", "", -1);
}

bool Persons::update(clli& id, cs& new_name = "-1", clli& new_nationality_id = -1, cs& new_birth_date = "-1", cs& new_education = "-1", cld& new_english_score = -1){
    const string sql = "UPDATE " + _name + " SET name = ?, nationality_id = ?, birth_date = ?, education = ?, english_score = ? WHERE ID = ?;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Error Preparing Statement" << endl;
        return false;
    }

    if(new_name != "-1"){
        sqlite3_bind_text(stmt, 1, new_name.c_str(), -1, SQLITE_STATIC);
    }
    if(new_nationality_id != -1){
        sqlite3_bind_int64(stmt, 2, new_nationality_id);
    }
    if(new_birth_date != "-1"){
        sqlite3_bind_text(stmt, 3, new_birth_date.c_str(), -1, SQLITE_STATIC);
    }

    if(new_education != "-1"){
        sqlite3_bind_text(stmt, 4, new_education.c_str(), -1, SQLITE_STATIC);    
    }

    if(new_english_score != -1){
        sqlite3_bind_double(stmt, 5, new_english_score);
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

bool Persons::remove(cs& name){
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
bool Persons::remove(clli& id){
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
Persons::~Persons(){

}