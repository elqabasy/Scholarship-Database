#ifndef SCHOLARSHIPS_H
#define SCHOLARSHIPS_H

#include "Database.h"

struct Scholarship{
    ld budget;
    ll int id, fieldID;
    string description, degree;
    Scholarship(clli& idx, cs& descriptionx, clli& fieldIDx, cld& budgetx, cs& degreex){
        id = idx;
        budget = budgetx;
        degree = degreex;
        fieldID = fieldIDx;
        description = descriptionx;
    }
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
};
#endif // SCHOLARSHIPS_H