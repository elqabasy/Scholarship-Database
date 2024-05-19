#ifndef BANK_ACCOUNTS_H
#define BANK_ACCOUNTS_H

#include <iostream>
#include "Database.h"
using namespace std;

struct BankAccount{
    ld _balance;
    lli _id, _person_id;
    BankAccount(clli& id, clli& person_id, cld& balance) :_id(id),  _person_id(person_id),  _balance(balance) {}
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

        BankAccount read(clli&);

        bool update(clli&, cld&);

        bool remove(clli&);

        // Destructor
        ~BankAccounts();
};
#endif


