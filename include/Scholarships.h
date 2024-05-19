#ifndef SCHOLARSHIPS_H
#define SCHOLARSHIPS_H

#include "Database.h"

struct Scholarship{
    ld _budget;
    lli _id, _field_id;
    string _description, _degree;
    Scholarship(clli& id, cs& description, clli& field_id, cld& budget, cs& degree) : _id(id), _description(description), _field_id(field_id), _budget(budget), _degree(degree) {}
};

class Scholarships : public Database{
    private:
        sqlite3* _database;
        const string _name = "Scholarships";
    public:
        // Constructor
        Scholarships();

        // Functionality
        bool create(cs&, clli&, cld&, cs&);

        Scholarship read(clli&);

        bool update(clli&, cs&, clli&, cld&, cs&);

        bool remove(clli&);

        // Constructor
        ~Scholarships();
};
#endif // SCHOLARSHIPS_H