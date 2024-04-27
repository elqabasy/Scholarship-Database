#ifndef PAYMENTS_H
#define PAYMENTS_H

#include "Database.h"

struct Payment{
    ld amount;
    string createDate;
    ll int id, scholarshipID, bankAccountID;
    Payment(clli& idx, clli& scholarshipIDx, clli& bankAccountIDx, cld& amountx, cs& createDatex){
        id = idx;
        amount = amountx;
        createDate = createDatex;
        scholarshipID = scholarshipIDx;
        bankAccountID = bankAccountIDx;
    }
};

class Payments : public Database{
    private:
        sqlite3* _database;
        const string _name = "Payments";
    public:
        // Constructor
        Payments();

        // Functionality
        bool create(clli&, clli&, cld&);

        Payment read(clli&);

        bool update(clli&, cld&);

        bool remove(clli&);
};

#endif // PAYMENTS_H