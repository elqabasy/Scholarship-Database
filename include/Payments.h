#ifndef PAYMENTS_H
#define PAYMENTS_H

#include "Database.h"

struct Payment{
    ld _amount;
    string _createDate;
    ll int _id, _scholarshipID, _bankAccountID;
    Payment(clli& id, clli& schoID, clli& bankID, cld& amount, cs& createDate) : _id(id), _scholarshipID(schoID), _bankAccountID(bankID), _createDate(createDate), _amount(amount){}
};

class Payments : public Database{
    private:
        sqlite3* _database;
        const string _name = "Payments";
    public:
        // Constructor
        Payments();

        // Functionality
        /* CRUD Operations approach*/
        bool create(clli&, clli&, cld&);

        Payment read(clli&);

        bool update(clli&, cld&);

        bool remove(clli&);

        // Destructor
        ~Payments();

};

#endif // PAYMENTS_H