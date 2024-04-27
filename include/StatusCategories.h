#ifndef STATUS_CATEGORIES_H
#define STATUS_CATEGORIES_H

#include "Database.h"

struct StatusCategory{
    ll int id;
    string name;
    StatusCategory(clli& idx, cs& namex){
        id = idx;
        name = namex;
    }
};

class StatusCategories : public Database{
    private:
        sqlite3* _database;
        const string _name = "StatusCategories";
    public:
        // Constructor
        StatusCategories();

        // Functionality
        bool create(cs&);

        StatusCategory read(clli&);

        bool update(clli&, cs&);

        bool remove(clli&);
};

#endif // STATUS_CATEGORIES_H