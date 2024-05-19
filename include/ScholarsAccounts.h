#ifndef SCHOLARS_ACCOUNTS_H
#define SCHOLARS_ACCOUNTS_H

#include "Database.h"

struct Scholar{
    lli _id, _person_id;
    string _username, _password;
    Scholar(clli& id, clli& person_id, cs& username, cs& password) : _id(id), _person_id(person_id), _username(username), _password(password){}
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

        Scholar read(cs&);
        Scholar read(clli&);

        bool update(clli&, cs&, cs&);

        bool remove(cs&);
        bool remove(clli&);

        // Destructor
        ~Scholars();
};

#endif // SCHOLARS_ACCOUNTS_H