#ifndef STATUS_CATEGORIES_H
#define STATUS_CATEGORIES_H

#include "Database.h"

struct StatusCategory{
    lli _id;
    string _name;
    StatusCategory(clli& id, cs& name) : _id(id), _name(name) {}
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

        // Destructor
        ~StatusCategories();

};
#endif // STATUS_CATEGORIES_H