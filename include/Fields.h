#ifndef FIELDS_H
#define FIELDS_H
#include <tuple>
#include <iostream>
#include "Database.h"
using namespace std;

struct Field{
    ll int id;
    string name, description;
    Field(clli& idx, cs& namex, cs& descriptionx){
        id = idx;
        name = namex;
        description = descriptionx;
    }
};

class Fields : public Database{
    private:
        sqlite3* _database;
        const string _name = "Fields";
    public:
        // Constructor
        Fields();

        // Functionality
        bool create(cs&, cs&);

        Field read(clli&);

        bool update(clli&, cs&, cs&);

        bool remove(clli&);
};


#endif // FIELDS_H