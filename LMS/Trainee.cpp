//
//  Trainee.cpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#include "Trainee.hpp"
#include "LmsSystem.hpp"
#include "User.hpp"
#include "Test.hpp"

void Trainee::viewProfile(LmsSystem& sys){
    User* userPtr = dynamic_cast<User*>(this);
    sys.getReportObj().generateReport(userPtr, sys);
}

void Trainee::viewCourseMaterials(LmsSystem& sys){
    viewEnrolledCourses(sys);
    std::cout << "Enter Course ID:\n>> ";
    int id{};
    std::cin >> id;
    Course c = sys.getCourse(id);
    std::cout << "-------- " << c.getCourseName() << " --------\n";
    std::cout << c.getCourseMaterial() << std::endl;
}

void Trainee::viewEnrolledCourses(LmsSystem& sys){
    std::vector<Course> enrolledCourses{};
    for (int i = 0; i<getCoursesList().size(); ++i){
        std::cout << sys.getCourse(getCoursesList()[i]).getCourseName() << std::endl;
        enrolledCourses.push_back(sys.getCourse(getCoursesList()[i]));
    }

    if(enrolledCourses.size()==0){
        std::cout<<"You are not enrolled in any course\n";
        return;
    }
    std::cout << "Looking at courses " << enrolledCourses.size() << std::endl;
    sys.viewCourses(enrolledCourses);
}

void Trainee::viewReports(LmsSystem& sys){
    User* userPtr = dynamic_cast<User*>(this);
    sys.getReportObj().generateReport(userPtr, sys);
}

void Trainee::takeTest(Course c){}
void Trainee::raiseQuery(std::string &query){
    int cId;
    std::cout << "Enter course id you want to raise query in: ";
    std::cin>>cId;
    std::string q;
    std::cout<<"Enter Your Query: ";
    std::getline(std::cin >> std::ws, q);
    Course c;
    c.addQueries(cId, q);
}

void Trainee::enrollIntoCourses(LmsSystem& sys){
    std::cout << "Select course Id of course you want to enroll\n";
    std::vector<Course> courses = sys.getCourseDetails();
    sys.viewCourses(courses);
    int cid{};
    std::cout << ">> ";
    std::cin >> cid;
    Course c;
    c.addNewTrainee(cid, getRegistraionID());
    addNewCourseInList(std::to_string(cid));
}

void Trainee::generalTasks(LmsSystem& sys){
    std::cout << "------ Trainee " << getName() << " ------\n";
    std::cout << "\nSelect what you want to do:\n";
    std::cout << "1. View Profile\n2. Edit Profile\n";
    std::cout << "3. View Course Materials\n4. Report\n";
    std::cout << "5. View Enrolled Courses\n";
    std::cout << "6. Raise Query\n7. Enroll into Course\n";
    std::cout << "8. View queries + answers\n>> ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        viewProfile(sys);
    } else if (choice == 2) {
        editProfile();
        std::cout<<"To view the changes login again\n";
        return;
    } else if (choice == 3) {
        viewCourseMaterials(sys);
    } else if (choice == 4) {
        viewReports(sys);
    } else if (choice == 5) {
        viewEnrolledCourses(sys);
        std::cout<<"Take test (Y/N): ";
        std::string choice;
        std::cin>>choice;
        if(choice=="Y"){
            std::cout<<"Enter Course Id of the course you want to take test: ";
            int id;
            std::cin>>id;
            Mcq mcqTest;
            int levelOfDifficulty{0};
            std::cout << "Select Level of Difficulty (0/1/2): ";
            std::cin >> levelOfDifficulty;
            std::vector<Course> courses = sys.getCourseDetails();
            int level = mcqTest.setLevelOfDifficulty(levelOfDifficulty);
            mcqTest.takeTest(id,mcqTest.getQuestions(id,level,courses),mcqTest.getAnswers(id,level,courses),getRegistraionID());
                
        }
    }  else if (choice == 6) {
        std::string query = "Example query";
        raiseQuery(query);
    } else if (choice == 7) {
        enrollIntoCourses(sys);
    }else if (choice == 8) {
        Course  c;
        std::cout<<"To see the queries ---- Enter Courseid:  \n";
        int id;
        std::cin>>id;
        c.viewQueryReply(id);
    } else {
        std::cout << "Invalid choice !!\n";
        return;
    }
}

