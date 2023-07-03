//
//  Trainer.cpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#include "Trainer.hpp"
#include "LmsSystem.hpp"
#include "Admin.hpp"

void Trainer::getTraineeDetails(LmsSystem& sys){
    User* userPtr = dynamic_cast<User*>(this);
    sys.getReportObj().generateReport(userPtr, sys);
}

// trainer requests to teach a new course
void Trainer::requestCourse(LmsSystem& sys){
    std::vector<Course> courses = sys.getCourseDetails();
    sys.viewCourses(courses);
    std::cout<<"Enter courseid you want to enroll in: ";
    int id;
    std::cin>>id;
    std::string material;
    std::cout << "Drop Material\n";
    std::getline(std::cin >> std::ws, material);
    std::string questions;
    std::cout<<"Drop Questions\n";
    std::getline(std::cin >> std::ws, questions);
    std::string answers;
    std::cout<<"Drop answers\n";
    std::getline(std::cin >> std::ws, answers);
    Course c;
    c.setQuestionAnswer(id,questions, answers);
    c.setCourseMaterial(id, material);
    c.setTrainerId(id, getRegistraionID());
    
    

     
    
}

void Trainer::generalTasks(LmsSystem& sys){
    std::cout << "------ Trainer " << getName() << " ------\n";
    std::cout << "\nSelect what you want to do:\n";
    std::cout << "1. View Profile\n2. Edit Profile\n";
    std::cout << "3. Request New Course\n";
    std::cout << "4. View/Reply Queries\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        getTraineeDetails(sys);
    } else if (choice == 2) {
        editProfile();
        std::cout<<"To view the changes login again\n";
    } else if (choice == 3) {
        requestCourse(sys);
    } else if (choice == 4) {
        Course c;
        std::cout<<"Enter CourseId you want to see the Queries: ";
        int cId;
        std::cin>>cId;
        c.viewQueries(cId);
    } else {
        std::cout << "Invalid choice !!\n";
        return;
    }
}
