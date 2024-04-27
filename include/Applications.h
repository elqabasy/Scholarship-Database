#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <sqlite3.h>
#include <iostream>
#include "Database.h"
using namespace std;

#define l long
// #define endl '\n';
#define ll long long
#define cld const ld
#define ld long double
#define cs const string
#define clli const ll int


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

        // Functionality
        bool create(clli&, clli&, clli&);

        Application read(clli&);

        bool update(clli&, clli&, clli&, clli&);

        bool remove(clli&);
};
#endif