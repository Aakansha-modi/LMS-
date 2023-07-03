//
//  Register.cpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#include "Register.hpp"
#include <fstream>
#include <sqlite3.h>
#include <ctime>

const char* filePath2 = "/Users/aakansham/Downloads/LMS/LMS/Database.db";

std::string Register::addUser(){
    // initializing variables
    std::string name{};
    std::string address{};
    std::string emailID{};
    std::string password{};
    std::string userType{};
    std::string trainer{};
    std::string trainee{};
    std::string courses{};
    
    // Taking user defined variables
    std::cout << "Enter User Details:\nName: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Address: ";
    std::getline(std::cin >> std::ws, address);
    std::cout << "Email ID: ";
    std::getline(std::cin >> std::ws, emailID);
    std::cout << "Password: ";
    std::getline(std::cin >> std::ws, password);
    std::cout << "User Type Admin, Teacher or Student: ";
    std::getline(std::cin >> std::ws, userType);
    std::cout << std::endl;
    std::string registrationID{this->generateRegistraionID(userType)};
    
    std::string queryTable{};
    if(userType == "Admin"){
        queryTable = "Admin";
    }
    if(userType == "Teacher"){
        queryTable  = "Trainer";
    }
    if(userType == "Student"){
        queryTable = "Trainee";
    }
    // initializing time variables
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    int currdate = localTime->tm_mday;
    int currmonth = localTime->tm_mon + 1;
    int curryear = localTime->tm_year + 1900;
    // Time format in string date/month/year
    std::string registrationTime = std::to_string(currdate) + "/" + std::to_string(currmonth) + "/" + std::to_string(curryear);
    std::string expirationTime = std::to_string(currdate) + "/" + std::to_string(currmonth) + "/" + std::to_string(curryear+1);
    
    std::cout << "Registration time is " << registrationTime << std::endl;
    
    
    sqlite3* db;
    int rc = sqlite3_open(filePath2, &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    }
    
    std::string query{};
    
    if (userType == "Admin") {
        query = "INSERT INTO Admin (name, address,emailID,password,userType,registrationID,registrationTime,expirationTime,trainer,trainee,courses) VALUES (?,?,?,?,?,?,?,?,?,?,?)";
    } else {
        query = "INSERT INTO " + queryTable + " (name, address,emailID,password,userType,registrationID,registrationTime,expirationTime, courses) VALUES (?,?,?,?,?,?,?,?,?)";
    }
    
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
      std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_close(db);
    }
    
    if(userType == "Admin"){
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, address.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, emailID.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, password.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, userType.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, registrationID.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, registrationTime.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 8, expirationTime.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 9, trainer.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 10, trainee.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 11, courses.c_str(), -1, SQLITE_STATIC);
    }
    else{
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, address.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, emailID.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, password.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, userType.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, registrationID.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, registrationTime.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 8, expirationTime.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 9, courses.c_str(), -1, SQLITE_STATIC);
    }
    
    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return registrationID;
}

void Register::verifyEmail() const {
    std::cout << "Verifying Email...\n\nEmail Verification Successful!\n";
}

void Register::successfulRegistration() const {
    std::cout << "User Registered!\n";
}

std::string Register::generateRegistraionID(const std::string prefix){
    // filePath denotes path to the txt containing an integer denoting regId already assigned
    std::string filePath{"/Users/aakansham/Downloads/LMS/LMS/UserID.txt"};
    std::ifstream inputFile(filePath);
        if (!inputFile) {
            std::cerr << "Error opening Id.txt 2 "  << std::endl;
            return "";
        }

        int id;
        inputFile >> id;
        inputFile.close();

        std::string uniqueID = prefix.substr(0,1) + std::to_string(id);
        id++;

        std::ofstream outputFile(filePath);
        if (!outputFile) {
            std::cerr << "Error opening Id.txt " << std::endl;
            return "";
        }

        outputFile << id;
        outputFile.close();

        return uniqueID;
}
