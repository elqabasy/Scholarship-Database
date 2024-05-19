#ifndef FIELDS_H
#define FIELDS_H
#include <tuple>
#include <iostream>
#include "Database.h"
using namespace std;

struct Field{
    ll int _id;
    string _name, _description;
    Field(clli& id, cs& name, cs& description) : _id(id), _name(name), _description(description){}
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
        
        // Destructor
        ~Fields();
};
#endif // FIELDS_H