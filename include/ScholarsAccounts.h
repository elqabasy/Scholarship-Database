#ifndef SCHOLARS_ACCOUNTS_H
#define SCHOLARS_ACCOUNTS_H

#include "Database.h"

struct Scholar{
    ll int id, personID;
    string username, password;
    Scholar(clli& idx, clli& personIDx, cs& usernamex, cs& passwordx){
        id = idx;
        personID = personIDx;
        username = usernamex;
        password = passwordx;
    }
};

class Scholars : public Database{
    private:
        sqlite3* _database;
        const string _name = "ScholarsAccounts";
    public:
        // Constructor
        Scholars();

        // Functionality
        bool create(clli&, cs&, cs&);

        bool remove(cs&);
        bool remove(clli&);

        bool update(clli&, cs&, cs&);

        Scholar read(cs&);
        Scholar read(clli&);
};

#endif // SCHOLARS_ACCOUNTS_H