//
//  Admin.cpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#include "Admin.hpp"
#include "Course.hpp"
#include "LmsSystem.hpp"
#include <fstream>


void Admin::removeUser(std::string userid) {
    // fetch the table and then remove user
    //std::cout<<"---";
    LmsSystem s;
    s.deleteUser(userid);
}
void Admin::createCourse() {
    std::string courseName{};
    std::string courseDescription{};
    std::string duration{};
    int cost{};
    
    std::cout << "\n------Course Creation------\n";
    std::cout << "Course Name: ";
    std::getline(std::cin >> std::ws, courseName);
    std::cout << "Course Description: ";
    std::getline(std::cin >> std::ws, courseDescription);
    std::cout << "Course Duration: ";
    std::getline(std::cin >> std::ws, duration);
    std::cout << "Course Cost: ";
    std::cin >> cost;
    
    Course c;
    c.setCourse(0, courseName, courseDescription, duration, "", cost, 0, {}, {}, "", {}, "", {}, {});
}

void Admin::updateCourse() {
    std::cout << "Enter Course ID: ";
    int id;
    std::cin >> id;
    std::cout << "\nWhat do you want to update?\n";
    std::cout << "1. Course Description\n2. Course Material\n";
    std::cout << "3. Course Duration\n4. Course Cost\n5. Questions and Answers\n";
    int ch;
    Course c;
    std::cin >> ch;
    if (ch == 1) {
        std::string newDes{};
        std::cout << "Enter new description: ";
        std::getline(std::cin >> std::ws, newDes);
        c.setCourseDescription(id, newDes);
    } else if (ch == 2) {
        std::string newMat{};
        std::cout << "\nEnter new material: ";
        std::getline(std::cin >> std::ws, newMat);
        c.setCourseMaterial(id, newMat);
    } else if (ch == 3) {
        std::string newDur{};
        std::cout << "\nEnter new duration: ";
        std::getline(std::cin >> std::ws, newDur);
        c.setDuration(id, newDur);
    } else if (ch == 4) {
        int newCost{};
        std::cout << "\nEnter new cost: ";
        std::cin >> newCost;
        c.setCost(id, newCost);
    } else if (ch == 5){
        std::string question{};
        std::string answer{};
        std::cout << "Add questions and answer\n";
        std::cout << "Enter Questions: ";
        std::cin >> question;
        std::cout << "Enter Answers: ";
        std::cin >> answer;
        c.setQuestionAnswer(id, question, answer);
    } else {
        std::cout << "Not a valid choice\n";
        return;
    }
    std::cout << std::endl;
}

void Admin::retrieveCourses(LmsSystem& sys) {
    std::vector<Course> courses = sys.getCourseDetails();
    sys.viewCourses(courses);
}

void Admin::removeCourse(int id) {
    LmsSystem s;
    s.deleteCourse(id);
}

void Admin::generateReports(LmsSystem& sys) {
    User* userPtr = dynamic_cast<User*>(this);
    sys.getReportObj().generateReport(userPtr, sys);
}

void Admin::deleteExpiredUsers() {
    std::cout << "\nDeleting expired users...\n";
}

void Admin::generalTasks(LmsSystem& sys) {
    std::cout << "------ Admin " << getName() << " ------\n";
    deleteExpiredUsers();
    std::cout << "\nSelect what you want to do:\n";
    std::cout << "1. Remove User\n2. Create Course\n";
    std::cout << "3. Update Course\n4. Retrieve All Courses\n";
    std::cout << "5. Remove Course\n6. Generate Report\n";
    std::cout << "7. Edit Admin Profile\n>> ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Enter Registration ID of user you want to remove: ";
        std::string id{};
        //std::getline(std::cin >> std::ws, id);
        std:: cin >> id;
        removeUser(id);
        std::cout << "User removed successfully.\n";
    } else if (choice == 2) {
        createCourse();
    } else if (choice == 3) {
        updateCourse();
    } else if (choice == 4) {
        retrieveCourses(sys);
    } else if (choice == 5) {
        //Course c;
        std::cout << "Enter Course ID of user you want to remove: ";
        int id;
        //std::getline(std::cin >> std::ws, id);
        std:: cin >> id;
        removeCourse(id);
    } else if (choice == 6) {
        generateReports(sys);
    } else if (choice == 7) {
        editProfile();
        std::cout<<"To view the changes login again\n";
    } else {
        std::cout << "Invalid choice !!\n";
        return;
    }
}
