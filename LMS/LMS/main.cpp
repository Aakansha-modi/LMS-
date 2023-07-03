// General Header Files
#include <iostream>
#include <set>
#include <string>
#include <sqlite3.h>
#include <typeinfo>

// Helper Header Files
#include "Time.hpp"
#include "LmsSystem.hpp"

// LMS classes header files
#include "Course.hpp"
#include "User.hpp"
#include "Admin.hpp"
#include "Trainee.hpp"
#include "Trainer.hpp"
#include "Login.hpp"
#include "Register.hpp"
#include "Report.hpp"



int main(){
    // Creating singleton class objects
    LmsSystem sys{};
    sqlite3* db{};
    sys.generateDatabase(db);
    User* currentUser = sys.signInOrUp();
    // if problem in signing in/up, exit code
    if(!currentUser){return 0;}
    do{
        currentUser->generalTasks(sys);
    }while(!currentUser->logOut());
    return 0;
}


//const std::type_info& typeInfo = typeid(sys);
//std::cout << "Class Type: " << typeInfo.name() << std::endl;

/*if (Trainer* t = dynamic_cast<Trainer*>(u)) {
    delete t;
        }
else if (Trainee* t = dynamic_cast<Trainee*>(u)){
    delete t;
}
else if (Admin* t = dynamic_cast<Admin*>(u)){
    delete t;
}
*/
