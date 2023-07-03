//
//  LmsSystem.hpp
//  LMS
//
//  Created by Isha Sehrawat . on 29/06/23.
//

#ifndef LmsSystem_hpp
#define LmsSystem_hpp

#include <stdio.h>
#include "Course.hpp"
#include "Login.hpp"
#include "Register.hpp"
#include <sqlite3.h>
#include "User.hpp"
#include "Report.hpp"

class LmsSystem{
public:
    // getters
    Login getLoginObj() const {return login;}
    Register getRegisterObj() const {return reg;}
    Report getReportObj() const {return rep;}
    
    // returns the signed in user or newly created user object
    User* signInOrUp();
    // function to create database tables if they dont exist
    void generateDatabase(sqlite3*);
    // returns all courses list
    std::vector<Course> getCourseDetails();
    // returns a single course given course id
    Course getCourse(int id);
    // function to show all courses
    void viewCourses(std::vector<Course>) const;
    // function to retrieve user type object from table given registration id
    User* getUser(const std::string& regID);
    // Delete user
    void deleteUser(std::string);
    void deleteCourse(int);
private:
    std::vector<Course> courseList{};
    Login login{};
    Register reg{};
    Report rep{};
};

#endif /* LmsSystem_hpp */
