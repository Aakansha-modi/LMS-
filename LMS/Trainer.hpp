//
//  Trainer.hpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#ifndef Trainer_hpp
#define Trainer_hpp
#include "User.hpp"
#include "Course.hpp"
#include "Time.hpp"
#include <stdio.h>

// Derived Classes
class Trainer : public User {
public:
    // Constructor
    Trainer(std::string name, std::string add, std::string email, std::string pass, std::string usertype, std::string regid, Time dor, Time doe, std::vector<int> coursesList) : User(name, add, email, pass, usertype, regid, dor, doe, coursesList) {}
    ~Trainer(){}
    
    // Other functions
    void getTraineeDetails(LmsSystem& sys);
    void requestCourse(LmsSystem& sys);
    void generalTasks(LmsSystem& sys);
};

#endif /* Trainer_hpp */
