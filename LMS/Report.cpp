//
//  Report.cpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#include "Report.hpp"
#include "Trainee.hpp"
#include "Trainer.hpp"
#include "Admin.hpp"
#include <iostream>
#include <typeinfo>
#include "LmsSystem.hpp"

void Report::generateReport(User* u, LmsSystem& sys) {
    if(u->getUserType() == "Teacher"){
        generateReportForTrainer(dynamic_cast<Trainer*>(u));
    }
    if(u->getUserType() == "Student"){
        generateReportForTrainee(dynamic_cast<Trainee*>(u));
    }
    if(u->getUserType() == "Admin"){
        generateReportForAdmin(sys);
    }
}

void Report::generateReportForTrainee(Trainee* t){
    std::cout << "\n------Trainee Report------\n";
    std::cout << "Name: " << t->getName();
    std::cout << "\nRegistration ID: " << t->getRegistraionID() << "\nEmail ID: ";
    std::cout << t->getEmailID() << "\nUser Type: " << t->getUserType() << "\nAddress: ";
    std::cout << t->getAddress() << "\nEnrolled Course Ids: ";
    std::string courses{};
    std::vector<int> a = t->getCoursesList();
    for(int i = 0 ; i<a.size(); ++i){
        courses += std::to_string(a[i]) + " ";
    }
    std::cout << courses;
    std::cout << "\n--------------------------\n";
}

void Report::generateReportForTrainer(Trainer* t){
    std::cout << "\n------Trainee Report------\n";
    std::cout << "Name: " << t->getName();
    std::cout << "\nRegistration ID: " << t->getRegistraionID() << "\nEmail ID: ";
    std::cout << t->getEmailID() << "\nUser Type: " << t->getUserType() << "\nAddress: ";
    std::cout << t->getAddress();
    std::cout << "\n--------------------------\n";
}

void Report::generateReportForAdmin(LmsSystem& sys){
    // Admin can view reports for trainer and trainee
    std::cout << "\n---Admin Report Generation---\n";
    int choice{-1};
    std::cout << "Choose User Type (1/2/3):\n1. Trainer\n2. Trainee\n3. Admin\n>> ";
    std::cin >> choice;
    if(choice == 1) {
        std::string userID{};
        std::cout << "\nEnter Trainer ID:>>\n";
        // print trainer IDs here
        std::cin >> userID;
        // extracting information about user
        User* u = sys.getUser(userID);
        // converting to proper class
        Trainer* t = dynamic_cast<Trainer*>(u);
        // calling trainer function
        generateReportForTrainer(t);
    }
    else if(choice == 2) {
        std::string userID{};
        std::cout << "\nEnter Trainee ID:>>\n";
        // print trainee IDs here
        std::cin >> userID;
        // extracting information about user
        User* u = sys.getUser(userID);
        // converting to proper class
        Trainee* t = dynamic_cast<Trainee*>(u);
        // calling trainer function
        generateReportForTrainee(t);
    }
    else{
        std::cout << "\n------Admin Report------\n";
        User* u = sys.getUser("A0");
        // converting to proper class
        Admin* t = dynamic_cast<Admin*>(u);
        std::cout << "Name: " << t->getName();
        std::cout << "\nRegistration ID: " << t->getRegistraionID() << "\nEmail ID: ";
        std::cout << t->getEmailID() << "\nUser Type: " << t->getUserType() << "\nAddress: ";
        std::cout << t->getAddress();
        std::cout << "\n--------------------------\n";
    }
}
