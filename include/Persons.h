#ifndef PERSONS_H
#define PERSONS_H

#include "Database.h"

struct Person{
    string name, education, birth_date;
    long double english_score;
    ll int id, nationality_id;
    Person(ll int idx, string namex, ll int nationality_idx, string birth_datex, string educationx, ld english_scorex){
        id = idx;
        name = namex;
        education = educationx;
        birth_date = birth_datex;
        english_score = english_scorex;
        nationality_id = nationality_idx;
    }
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

        bool remove(cs&);
        bool remove(clli&);

        bool update(clli&, cs&, clli&, cs&, cs&, cld&);

        Person read(cs&);
        Person read(clli&);
};

#endif // PERSONS_H