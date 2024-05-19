#ifndef PERSONS_H
#define PERSONS_H

#include "Database.h"
struct Person{
    ld _english_score;
    ll int _id, _nationality_id;
    string _name, _education, _birth_date;
    Person(clli& id, cs& name, clli& nationality_id, cs& birth_date, cs& education, cld english_score) : _id(id), _name(name), _nationality_id(nationality_id), _birth_date(birth_date), _education(education), _english_score(english_score){}
};

class Persons : public Database{
    private:
        sqlite3* _database;
        const string _name = "Persons";
    public:
        // Constructor
        Persons();

        // Functionality
        bool create(cs&, clli&, cs&, cs&, cld&);

        Person read(cs&);
        Person read(clli&);

        bool update(clli&, cs&, clli&, cs&, cs&, cld&);

        bool remove(cs&);
        bool remove(clli&);

        // Destructor
        ~Persons();
};
#endif // PERSONS_H