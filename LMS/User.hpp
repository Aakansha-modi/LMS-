//
//  User.hpp
//  LMS
//
//  Created by Isha Sehrawat . on 27/06/23.
//

#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Time.hpp"
#include "Course.hpp"

class LmsSystem;

// Base class
class User {
public:
    // Constructors
    User(std::string userName, std::string userAddress, std::string userEmail, std::string userPassword, std::string userType, std::string userRegID, Time userDOR, Time userDOE, std::vector<int> coursesList);
    
    virtual ~User(){}
    
    // Getters for all attributes
    std::string getName() const{return name;}
    std::string getAddress() const{return address;}
    std::string getEmailID() const{return emailID;}
    std::string getPassword() const{return password;}
    std::string getUserType() const{return userType;}
    std::string getRegistraionID() const {return registrationID;}
    std::vector<int> getCoursesList() const {return coursesList;}
    
    // Setters for all attributes
    // User can edit profile hence these setters are added
    void setName(std::string userName) {name = userName;}
    void setAddress(std::string &userAddress) {address = userAddress;}
    void setEmailID(std::string &userEmail) {emailID = userEmail;}
    void setPassword(std::string &userPassword) {password = userPassword;}
    void setUserType(std::string &userUserType) {userType = userUserType;}
    void setRegistrationID(std::string &userRegistrationID) {registrationID = userRegistrationID;}
    void setDateOfReg(int d, int m, int y);
    void setDateOfExp(int d, int m, int y);
    
    // updation
    void updateAddress(std::string);
    void updateEmailId(std::string);
    void updatePassword(std::string);
   // void updateCourseList(std::string);
    void addNewCourseInList(std::string);
    
    void editProfile();
    bool logOut();
    virtual void generalTasks(LmsSystem&) = 0;
//    void generalTasks();
    
private:
    std::string name{};
    std::string address{};
    std::string emailID{};
    std::string password{};
    std::string userType{};
    std::string registrationID{};
    Time dateOfReg{};
    Time dateOfExp{};
    std::vector<int> coursesList{};
};

#endif /* User_hpp */
