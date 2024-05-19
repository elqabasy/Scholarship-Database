#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <iostream>
#include <sqlite3.h>
#include "Database.h"
using namespace std;

struct Application{
    ll int id, personID, scholarshipID, statusID;
    string createDate;
    Application(clli& idx, clli& personIDx, clli& scholarshipIDx, clli& statusIDx, cs& createDatex){
        id = idx;
        personID = personIDx;
        statusID = statusIDx;
        createDate = createDatex;
        scholarshipID = scholarshipIDx;
    }
};

class Applications : public Database{
    private:
        sqlite3* _database;
        const string _name = "Applications";
    public:
        // Constructor
        Applications();

        // CRUD Operations
        bool create(clli&, clli&, clli&);

        Application read(clli&);

        bool update(clli&, clli&, clli&, clli&);

        bool remove(clli&);

        // Destructor
        ~Applications();
};
#endif


/* Next Features
    - Getters for every member data by ApplicationID
*/