#ifndef BANK_ACCOUNTS_H
#define BANK_ACCOUNTS_H

#include <iostream>
#include "Database.h"
using namespace std;

struct BankAccount{
    ll int id, personID;
    ld balance;
    BankAccount(clli& idx, clli& personIDx, cld& balancex){
        id = idx;
        balance = balancex;
        personID = personIDx;
    }
};

class BankAccounts : public Database{
    private:
        sqlite3* _database;
        const string _name = "BankAccounts";
    public:
        // Constructor
        BankAccounts();

        // Functionality
        bool create(clli&, cld&);

        bool remove(clli&);

        bool update(clli&, cld&);

        BankAccount read(clli&);
};

#endif