#include <iostream>
using namespace std;

/* Notes
    - Header Files Should Be Included As Your Needs. 
*/
#include "container.cpp"

/* This Is An Object Of Database Contain The Instance Of Your Scholarship Reference Value */
Database SCHOLARSHIPS_DATABASE;

/* those objects are tables, you will use them to do CRUD operations on SCHOLARSHIP_DATABASE */

/* NOTE: CRUD Operations are: 
    [C] Create > create new record
    [R] Read   > select record or more than one from the database.tableName
    [U] Update > update record by another constrains
    [D] Delete > delete record by another constrains
*/

/* simple example: how to use this interface*/
void USAGE(){
    /* for example: i want to apply CRUD operations on Table scholarships sss*/
    Scholarships SH;
    
    /* Create Params : {description, fieldID, budget, degree}*/
    SH.create("Add description here.", 1, 19600, "Add degree here.");


    /* for example: i want to apply CRUD operations on Table scholarships sss*/
    BankAccounts BA;

    /* Read Params : {personID, fieldID, budget, degree} */
    // PARAMETER 1 -> BA.ID
    BA.read(1); // return Object of type struct::BankAccount(id, persons_id, balance)
    BA.remove(1);  // this will remove record with id = 1
    BA.update(1, 0); // this will update balance to 0 
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