//
//  Admin.hpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#ifndef Admin_hpp
#define Admin_hpp
#include "User.hpp"
#include "Trainee.hpp"
#include "Trainer.hpp"
#include "Course.hpp"
#include <stdio.h>
#include "Time.hpp"

//class LmsSystem;

class Admin : public User {
public:
    // Constructor
    Admin(std::string name, std::string add, std::string email, std::string pass, std::string usertype, std::string regid, Time dor, Time doe, std::vector<std::string> trainer, std::vector<std::string> trainee, std::vector<int> coursesList) : User(name, add, email, pass, usertype, regid, dor, doe, coursesList) {
        // The registration ID for admin is A0
        std::string s = "A0";
        this->setRegistrationID(s);
        trainersList = trainer;
        traineesList = trainee;
    }
    ~Admin(){}
    // General functions for admin
    void removeUser(std::string);
    void createCourse();
    void updateCourse();
    void retrieveCourses(LmsSystem& sys);
    void removeCourse(int);
    void generateReports(LmsSystem& sys);
    void deleteExpiredUsers();
    std::string generateCourseID();
    void generalTasks(LmsSystem& sys);
    
private:
    std::vector<std::string> trainersList{};
    std::vector<std::string> traineesList{};
};

#endif /* Admin_hpp */
