#include <iostream>
using namespace std;

/* Those header files should be included as your needs. */
#include "include/Fields.h"
#include "include/Persons.h"
#include "include/Database.h"
#include "include/Payments.h"
#include "include/Applications.h"
#include "include/BankAccounts.h"
#include "include/Scholarships.h"
#include "include/Nationalities.h"
#include "include/StatusCategories.h"
#include "include/ScholarsAccounts.h"

/* this is an object of Database contain the instance of your scholarship refrence value */
Database SCHOLARSHIPS_DATABASE;

/* those objects are tables, you will use them to do CRUD operations on SCHOLARSHIP_DATABASE */

/* NOTE: CRUD Operations are: 
    [C] Create > create new record
    [R] Read   > select record or more than one from the database.tableName
    [U] Update > update record by another constrainst
    [D] Delete > delete record by another constrainst
*/

/* simple example: how to use this interface*/
void USAGE(){
    /* for example: i want to apply CRUD operations on Table scholarships sss*/
    Scholarships SCHOLARSHIPS;

    /* Create Params : {description, fieldID, budget, degree}*/
    SCHOLARSHIPS.create("Add description here.", 1, 19600, "Add degree here.");


    /* for example: i want to apply CRUD operations on Table scholarships sss*/
    BankAccounts BANKACCOUNTS;

    /* Read Params : {personID, fieldID, budget, degree} */
    // PARAMETER 1 -> BANKACCOUNT.ID
    BANKACCOUNTS.read(1); // return Object of type struct::BankAccount(id, persons_id, balance)
    BANKACCOUNTS.remove(1);  // this will remove record with id = 1
    BANKACCOUNTS.update(1, 0); // this will update balance to 0 
    /* NOTE: Every class [table] has it's own functions with CRUD operation functions */
}

int main(){
    Database DB;
    try{
        if (!DB.open("../scholarship.db")){
            cout << DB.error() << endl;
        }else{
            USAGE();
        }
        
    }catch(const exception& ERROR){
        cerr << ERROR.what() << endl;
    }
    system("pause");
    return 0;
}

/* NOTE: IF there is any quesion or feature, please remind me. */