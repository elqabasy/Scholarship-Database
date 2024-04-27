#include "../include/Persons.h"

Persons::Persons(){
    _database = database();
}

bool Persons::create(cs& name, clli& nationalityID, cs& birthDate, cs& education, cld& englishScore) {
    const string query = "INSERT INTO " + _name + " (name, nationality_id, birth_date, education, english_score) VALUES (?, ?, ?, ?, ?);";
    
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(_database, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        _error = "Error preparing statement: ";
        _error += sqlite3_errmsg(_database);
        cerr << _error << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, nationalityID);
    sqlite3_bind_text(stmt, 3, birthDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, education.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 5, englishScore);

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

bool Persons::update(clli& id, cs& newName = "-1", clli& newNationalityID = -1, cs& newBirthDate = "-1", cs& newEducation = "-1", cld& newEnglishScore = -1){
    const string sql = "UPDATE " + _name + " SET name = ?, nationality_id = ?, birth_date = ?, education = ?, english_score = ? WHERE ID = ?;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cerr << "Error Preparing Statement" << endl;
        return false;
    }

    if(newName != "-1"){
        sqlite3_bind_text(stmt, 1, newName.c_str(), -1, SQLITE_STATIC);
    }
    if(newNationalityID != -1){
        sqlite3_bind_int64(stmt, 2, newNationalityID);
    }
    if(newBirthDate != "-1"){
        sqlite3_bind_text(stmt, 3, newBirthDate.c_str(), -1, SQLITE_STATIC);
    }

    if(newEducation != "-1"){
        sqlite3_bind_text(stmt, 4, newEducation.c_str(), -1, SQLITE_STATIC);    
    }

    if(newEnglishScore != -1){
        sqlite3_bind_double(stmt, 5, newEnglishScore);
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