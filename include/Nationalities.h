#ifndef NATIONALITIES_H
#define NATIONALITIES_H

#include "Database.h"

class Nationalities : public Database{
    private:
        sqlite3* _database;
        cs& _name = "Nationalities";
    public:
        // Constructor
        Nationalities();

        // Functionality
        bool create(cs&);

        lli read(cs&);
        string read(clli&);

        bool update(clli&, cs&);

        bool remove(cs&);
        bool remove(clli&);

        /* Destructor */
        ~Nationalities();
};

#endif // NATIONALITIES_H