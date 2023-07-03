//
//  User.cpp
//  LMS
//
//  Created by Isha Sehrawat . on 27/06/23.
//

#include "User.hpp"
#include "Time.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>

const char* filePath3 = "/Users/aakansham/Downloads/LMS/LMS/Database.db";

User::User(std::string userName, std::string userAddress, std::string userEmail, std::string userPassword, std::string userrType, std::string userRegID, Time userDOR, Time userDOE, std::vector<int> userCoursesList){
    name = userName;
    address = userAddress;
    emailID = userEmail;
    password = userPassword;
    userType = userrType;
    registrationID = userRegID;
    dateOfReg = Time(userDOR);
    dateOfExp = Time(userDOE);
    coursesList = userCoursesList;
}

bool User::logOut(){
    std::string op{};
    std::cout << "Want to logout? (Yes/No)\n";
    std::getline(std::cin >> std::ws, op);
    return (op == "Yes") ? true : false;
}

void User::editProfile(){
    std::cout << "What do you want to update:\n";
    std::cout << "1. Address\n2. Email\n3. Password\n4. Course List\n>> ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Enter new address\n>> ";
        std::string newAdd{};
        std::getline(std::cin >> std::ws, newAdd);
        updateAddress(newAdd);
    } else if (choice == 2) {
        std::cout << "Enter new email ID\n>> ";
        std::string newEmail{};
        std::getline(std::cin >> std::ws, newEmail);
        updateEmailId(newEmail);
    } else if (choice == 3){
        std::cout << "Enter new password\n>> ";
        std::string newPass{};
        std::getline(std::cin >> std::ws, newPass);
        updatePassword(newPass);
    }
//    else if (choice == 4){
//        std::cout << "Enter new course list\n>> ";
//        std::string newCourses{};
//        std::getline(std::cin >> std::ws, newCourses);
//        updateCourseList(newCourses);
//    }
}

void User::updateAddress(std::string newAddress) {
      std::string regId = getRegistraionID();
      sqlite3* db;
      int rc = sqlite3_open(filePath3, &db);
      if (rc != SQLITE_OK) {
       std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      std::string uType;
      if (regId[0] == 'A')
        uType = "Admin";
      else if (regId[0] == 'T')
        uType = "Trainer";
      else if (regId[0] == 'S')
        uType = "Trainee";
      else {
        std::cout << "Invalid User Type!!" << std::endl;
        return;
      }
      std::string updateQuery = "UPDATE " + uType + " SET address = ? WHERE registrationID = ?";
      sqlite3_stmt* stmt;
      rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
      if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      sqlite3_bind_text(stmt, 1, newAddress.c_str(), -1, SQLITE_STATIC);
      sqlite3_bind_text(stmt, 2, regId.c_str(), -1, SQLITE_STATIC);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE) {
        std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      // Clean up
      sqlite3_finalize(stmt);
      sqlite3_close(db);
      std::cout << "User Address Updated Successfully!!" << std::endl;
}

void User::updateEmailId(std::string newEmail) {
      std::string regId = getRegistraionID();
      sqlite3* db;
      int rc = sqlite3_open(filePath3, &db);
      if (rc != SQLITE_OK) {
       std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      std::string uType;
      if(regId[0] == 'A')
        uType = "Admin";
      else if(regId[0] == 'T')
        uType = "Trainer";
      else if(regId[0] == 'S')
        uType = "Trainee";
      else {
        std::cout << "Invalid User Type!!" << std::endl;
        return;
      }
      std::string updateQuery = "UPDATE " + uType + " SET emailID = ? WHERE registrationID = ?";
      sqlite3_stmt* stmt;
      rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
      if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      sqlite3_bind_text(stmt, 1, newEmail.c_str(), -1, SQLITE_STATIC);
      sqlite3_bind_text(stmt, 2, regId.c_str(), -1, SQLITE_STATIC);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE) {
        std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      // Clean up
      sqlite3_finalize(stmt);
      sqlite3_close(db);
      std::cout << "User Email ID Updated Successfully!!" << std::endl;
}

void User::updatePassword(std::string newPassword) {
      std::string regId = getRegistraionID();
      sqlite3* db;
      int rc = sqlite3_open(filePath3, &db);
      if (rc != SQLITE_OK) {
       std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      std::string uType{};
      if(regId[0] == 'A')
        uType = "Admin";
      else if(regId[0] == 'T')
        uType = "Trainer";
      else if(regId[0] == 'S')
        uType = "Trainee";
      else {
        std::cout << "Invalid User Type!!" << std::endl;
        return;
      }
      std::string updateQuery = "UPDATE " + uType + " SET password = ? WHERE registrationID = ?";
      sqlite3_stmt* stmt;
      rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
      if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_STATIC);
      sqlite3_bind_text(stmt, 2, regId.c_str(), -1, SQLITE_STATIC);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE) {
        std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      // Clean up
      sqlite3_finalize(stmt);
      sqlite3_close(db);
      std::cout << "User Password Updated Successfully!!" << std::endl;
}

//void User::updateCourseList(std::string newCourseList) {
//      std::string regId = getRegistraionID();
//      sqlite3* db;
//      int rc = sqlite3_open(filePath3, &db);
//      if (rc != SQLITE_OK) {
//       std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
//        return;
//      }
//      std::string uType;
//      if(regId[0] == 'A')
//        uType = "Admin";
//      else if(regId[0] == 'T')
//        uType = "Trainer";
//      else if(regId[0] == 'S')
//        uType = "Trainee";
//      else {
//        std::cout << "Invalid User Type!!" << std::endl;
//        return;
//      }
//      std::string updateQuery = "UPDATE " + uType + " SET courses = ? WHERE registrationID = ?";
//      sqlite3_stmt* stmt;
//      rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
//      if (rc != SQLITE_OK) {
//        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
//        return;
//      }
//      sqlite3_bind_text(stmt, 1, newCourseList.c_str(), -1, SQLITE_STATIC);
//      sqlite3_bind_text(stmt, 2, regId.c_str(), -1, SQLITE_STATIC);
//      rc = sqlite3_step(stmt);
//      if (rc != SQLITE_DONE) {
//        std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
//        return;
//      }
//      // Clean up
//      sqlite3_finalize(stmt);
//      sqlite3_close(db);
//      std::cout << "User Address Updated Successfully!!" << std::endl;
//}

void User::addNewCourseInList(std::string newCourse){
    sqlite3* db;
    std::string regID = getRegistraionID();
    int rc = sqlite3_open(filePath3, &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    std::string query = "SELECT courses FROM Trainee WHERE registrationID = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
      std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    rc = sqlite3_bind_text(stmt, 1, regID.c_str(), -1,SQLITE_STATIC);
    if (rc != SQLITE_OK) {
      std::cout << "Cannot bind parameter: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_finalize(stmt);
      sqlite3_close(db);
      return;
    }
    std::string cList{};
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      cList = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }
    if(cList == ""){
        cList += newCourse;
    }
    else{
        cList += ',' + newCourse;
    }

    std::string updateQuery = "UPDATE Trainee SET courses = ? WHERE registrationID = ?";
    
    sqlite3_stmt* ustmt;
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &ustmt, nullptr);
    if (rc != SQLITE_OK) {
      std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        //return false;
    }
    sqlite3_bind_text(ustmt, 1, cList.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(ustmt, 2, regID.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(ustmt);
      if (rc != SQLITE_DONE) {
        std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    std::cout<<"New course inserted Successfully!!\n";
}
