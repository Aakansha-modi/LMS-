//
//  LmsSystem.cpp
//  LMS
//
//  Created by Isha Sehrawat . on 29/06/23.
//

#include "LmsSystem.hpp"

#include "Time.hpp"
#include "Admin.hpp"
#include "Trainee.hpp"
#include "Trainer.hpp"

#include <iostream>
#include <sqlite3.h>
#include <sstream>

const char* filePath1 = "/Users/aakansham/Downloads/LMS/LMS/Database.db";

void LmsSystem::generateDatabase(sqlite3* db){
    std::cout << "Generating dummy dataset...\n";
    
    // Creating table Admin
    std::string createTableQuery = "CREATE TABLE IF NOT EXISTS Admin (name TEXT, address TEXT, emailID TEXT, password TEXT, userType TEXT, registrationID TEXT PRIMARY KEY, registrationTime TEXT, expirationTime TEXT, trainer TEXT, trainee TEXT, courses TEXT)";
    char* errMsg = 0;
    int rc = sqlite3_open(filePath1, &db);
    rc = sqlite3_exec(db, createTableQuery.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
    
    
    // Creating table Trainer
    createTableQuery = "CREATE TABLE IF NOT EXISTS Trainer (name TEXT, address TEXT, emailID TEXT, password TEXT, userType TEXT, registrationID TEXT PRIMARY KEY, registrationTime TEXT, expirationTime TEXT, courses TEXT)";
    errMsg = 0;
    rc = sqlite3_open(filePath1, &db);
    rc = sqlite3_exec(db, createTableQuery.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
    
    // Creating table Trainee
    createTableQuery = "CREATE TABLE IF NOT EXISTS Trainee (name TEXT, address TEXT, emailID TEXT, password TEXT, userType TEXT, registrationID TEXT PRIMARY KEY, registrationTime TEXT, expirationTime TEXT, courses TEXT)";
    errMsg = 0;
    rc = sqlite3_open(filePath1, &db);
    rc = sqlite3_exec(db, createTableQuery.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
    
    // Creating table Course
      createTableQuery = "CREATE TABLE IF NOT EXISTS course (courseId INTEGER PRIMARY KEY, courseName TEXT, courseDescription TEXT, duration TEXT, courseMaterial TEXT, cost INTEGER, totalEnrollments INTEGER, questions TEXT, answer TEXT, courseTrainer TEXT, traineeData TEXT, trainerId TEXT, queries TEXT, reply TEXT)";
       errMsg = 0;
       rc = sqlite3_exec(db, createTableQuery.c_str(), 0, 0, &errMsg);
       if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
       }
    
      // Creating table testResult
      createTableQuery = "CREATE TABLE IF NOT EXISTS testResult (courseId INTEGER PRIMARY KEY, traineeId TEXT, score INTEGER, status TEXT)";
       errMsg = 0;
       rc = sqlite3_exec(db, createTableQuery.c_str(), 0, 0, &errMsg);
       if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
       }
    
    std::cout << "Dataset Generation Successfull!!\n";
}

User* LmsSystem::signInOrUp(){
    std::cout << "\n1. Sign in\n2. Sign Up\nEnter Choice: ";
    int choice{};
    std::cin >> choice;
    if (choice == 1){
        std::cout << "\n\n------Sign In------\n";
        // Calling the authentication function to login the user
        return getLoginObj().Authenticate(*this);
    }
    if (choice == 2){
        std::cout << "\n\n------Sign Up------\n";
        // Calling add user to take inputs and create new user information
        std::string registrationID = getRegisterObj().addUser();
        getRegisterObj().verifyEmail();
        getRegisterObj().successfulRegistration();
        return getUser(registrationID);
    }
    return nullptr;
}


// get the course details from the table
std::vector<Course> LmsSystem::getCourseDetails() {
      std::vector<Course> courses;
      sqlite3* db;
      int rc = sqlite3_open(filePath1, &db);
      if (rc != SQLITE_OK) {
       std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
          return {};
      }
      std::string query = "SELECT courseId, courseName, courseDescription, duration, courseMaterial , cost, totalEnrollments, questions, answer, courseTrainer, traineeData, trainerId, queries, reply FROM course";
      sqlite3_stmt* stmt;
       rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
          std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
          return courses;
        }
      while (sqlite3_step(stmt) == SQLITE_ROW) {
        int cid = sqlite3_column_int(stmt, 0);
        std::string cName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string cDescription = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string cDuration = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string courseMaterial = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        int cCost = sqlite3_column_int(stmt, 5);
        int ctotalEnrollments = sqlite3_column_int(stmt, 6);
        std::vector<std::string> v;
        std::string q(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        std::stringstream ss(q);
        std::string token;
        while (std::getline(ss, token, ',')) {
          v.push_back(token);
        }
        std::vector<std::string> va;
        std::string a(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        std::string cTrainer = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
        std::stringstream sa(a);
        while (std::getline(sa, token, ',')) {
          va.push_back(token);
        }
        std::vector<std::string> tData;
        std::string tList(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
        std::string tID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11));
        std::stringstream trData(tList);
        while (std::getline(trData, token, ',')) {
          tData.push_back(token);
        }
        std::vector<std::string> tQueries;
        std::string qList(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12)));
        std::stringstream trQueries(qList);
        while (std::getline(trQueries, token, ',')) {
          tQueries.push_back(token);
        }
        std::vector<std::string> tReply;
        std::string rList(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12)));
        std::stringstream trReply(rList);
        while (std::getline(trReply, token, ',')) {
          tReply.push_back(token);
        }
        Course course(cid, cName, cDescription, cDuration, courseMaterial, cCost, ctotalEnrollments, v, va,cTrainer, tData, tID, tQueries, tReply);
        courses.push_back(course);
      }
      sqlite3_finalize(stmt);
      return courses;
}

void LmsSystem::viewCourses(std::vector<Course> courses) const {
    for(int i=0;i<courses.size();i++){
        std::cout << "Course ID: " << courses[i].getCourseId() << " Course Name: " << courses[i].getCourseName() << std::endl;
    }
}

User* LmsSystem::getUser(const std::string& regID) {
    sqlite3* db;
    int rc = sqlite3_open(filePath1, &db);
    std::string query{};
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    }
    
    if(regID[0] == 'A') {
        query = "SELECT * FROM Admin WHERE registrationID = ?" ;
    }
    else if(regID[0] == 'T') {
        query = "SELECT * FROM Trainer WHERE registrationID = ?" ;
    }
    else if (regID[0] == 'S'){
        query = "SELECT * FROM Trainee WHERE registrationID = ?" ;
    }
    else {
        std::cout << "Invalid User type\n";
        return nullptr;
    }
    
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    rc = sqlite3_bind_text(stmt, 1, regID.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
            std::cout << "Cannot bind parameter: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return nullptr;
        }
    std::string name{}, address{}, emailID{}, password{}, userType{}, registrationID{}, registrationTime{}, expirationTime{}, trainerString{}, traineeString{}, course{};
    
    std::vector<int> userCourse;
    std::vector<std::string> trainer;
    std::vector<std::string> trainee;
    
    if(regID[0] == 'A'){
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            emailID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            userType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            registrationID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            registrationTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            expirationTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
            trainerString = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
            traineeString = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
            course = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
        }
        std::stringstream t(trainerString);
        std::string token;
        while (std::getline(t, token, ',')) {
          trainer.push_back(token);
        }
        
        std::stringstream tt(traineeString);
        while (std::getline(tt, token, ',')) {
          trainee.push_back(token);
        }
    } else {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            emailID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            userType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            registrationID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            registrationTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            expirationTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
            course = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        }
    }
    
    Time RTime(registrationTime);
    Time ETime(expirationTime);
    
    std::stringstream ss(course);
    std::string token;
    while (std::getline(ss, token, ',')) {
      userCourse.push_back(std::stoi(token));
    }

    
    sqlite3_finalize(stmt);
    
    if(regID[0] == 'A'){
       User *u = new Admin(name, address, emailID, password, userType, registrationID, RTime, ETime, trainer, trainee, userCourse);
        return u;
    }
    else if(regID[0] == 'T'){
       User *u = new Trainer(name, address, emailID, password, userType, registrationID, RTime, ETime, userCourse);
        return u;
    }
    else if(regID[0] == 'S'){
       User *u = new Trainee(name, address, emailID, password, userType, registrationID, RTime, ETime, userCourse);
        return u;
    }
    return nullptr;
}


Course LmsSystem::getCourse(int id){
    Course c;
    std::vector<Course> courses = getCourseDetails();
    for (int i = 0; i<courses.size(); ++i){
        if (courses[i].getCourseId() == id){
            return courses[i];
        }
    }
    return c;
}

void LmsSystem::deleteUser(std::string regId){
    sqlite3* db;
    int rc = sqlite3_open(filePath1, &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to open the database: " << sqlite3_errmsg(db) << std::endl;
        return ;
        }
    std::string sql;
    if(regId[0]=='A'){
        sql = "DELETE FROM Admin WHERE registrationID = ?;";
    }
    else if(regId[0]=='T'){
        sql = "DELETE FROM Trainer WHERE registrationID = ?;";
    }
    else {
        std::cout<<"------";
        sql = "DELETE FROM Trainee WHERE registrationID = ?;";
    }
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare the SQL statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return ;
       }
    rc = sqlite3_bind_text(stmt, 1, regId.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to bind the parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return ;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute the SQL statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return ;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    std::cout << "User deleted successfully." << std::endl;
    }

void LmsSystem::deleteCourse(int cID){
    sqlite3* db;
    int rc = sqlite3_open(filePath1, &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to open the database: " << sqlite3_errmsg(db) << std::endl;
        return ;
        }
    std::string sql = "DELETE FROM Course WHERE courseId = ?;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare the SQL statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return ;
       }
    rc = sqlite3_bind_int(stmt, 1, cID);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to bind the parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return ;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute the SQL statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return ;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    std::cout << "Course deleted successfully." << std::endl;
    }
