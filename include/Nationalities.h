#ifndef NATIONALITIES_H
#define NATIONALITIES_H

#include "Database.h"

class Nationalities : public Database{
    private:
        sqlite3* _database;
        const string _name = "Nationalities";
    public:
        // Constructor
        Nationalities();

        // Functionality
        bool create(const string&);
        bool remove(const string&);
        bool remove(const ll int&);
        bool update(const ll int&, const string&);

        string read(const ll int&);
        ll int read(const string&);
};

#endif // NATIONALITIES_H