//
//  Trainee.hpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#ifndef Trainee_hpp
#define Trainee_hpp
#include "User.hpp"
#include "Course.hpp"
#include <stdio.h>

class Trainee : public User {
public:
    // Constructor
    Trainee(std::string name, std::string add, std::string email, std::string pass, std::string usertype, std::string regid, Time dor, Time doe, std::vector<int> coursesList) : User(name, add, email, pass, usertype, regid, dor, doe, coursesList) {}
    ~Trainee(){}

    // Other functions
    void viewProfile(LmsSystem& sys);
    void viewCourseMaterials(LmsSystem& sys);
    void viewReports(LmsSystem& sys);
    void takeTest(Course c);
    void raiseQuery(std::string &query);
    void generalTasks(LmsSystem& sys);
    void viewEnrolledCourses(LmsSystem& sys);
    void enrollIntoCourses(LmsSystem& sys);
};

#endif /* Trainee_hpp */
