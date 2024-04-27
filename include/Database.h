#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>
#include <iostream>
#include <sqlite3.h>
using namespace std;


#define l long
#define endl '\n';
#define ll long long
#define cld const ld
#define ld long double
#define cs const string
#define clli const ll int

// database.h
class Database {
    private:
        static sqlite3* _database;
    public:
        string _error;

        // Constructor
        Database();

        // Functionality
        bool open(const string&);
        bool execute(const string&);

        // Setters
        void database(sqlite3*);
        void error(const string&);

        // Getters
        string error() const;
        sqlite3* database() const;

        // Destructor
        ~Database();
};

#endif // DATABASE_H