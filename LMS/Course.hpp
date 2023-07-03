// Course.hpp
// LMS
//
// Created by Aakansha Modi on 27/06/23.
//
#ifndef Course_hpp
#define Course_hpp
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>

class Course {
public:
    
    Course(){}
    Course(int, std::string, std::string, std::string, std::string, int, int, std::vector<std::string>, std::vector<std::string>, std::string, std::vector<std::string>, std::string, std::vector<std::string>, std::vector<std::string>);
  // Setters
    void setCourse (int,std::string,std::string,std::string,std::string,int,int,std::vector<std::string> ,std::vector<std::string>,std::string,std::vector<std::string>,std::string,std::vector<std::string>,std::vector<std::string>);
    void setCourseDescription(int,std::string);
    void setDuration(int,std::string);
    void setCourseMaterial(int,std::string);
    void setCost(int,int);
    void setQuestionAnswer(int,std::string,std::string);
    void addNewTrainee(int, std::string);
    void addQueries(int, std::string);
    void addReply(int, std::string);
    void setTrainerId(int, std::string);
    
    
    
  // normal getters
    int getCourseId(){return courseId;}
    std::string getCourseName(){return courseName;}
    std::string getCourseDescription(){return courseDescription;}
    std::string getDuration(){return duration;}
    std::string getCourseMaterial(){return courseMaterial;}
    int getCost(){return cost;}
    int getTotalEnrollments(){return totalEnrollments;}
    
    
  // special Gettters
  void getcourseId(std::vector<Course>);
  void getTotalEnrollments(int,std::vector<Course>);
  std::vector<std::string> getQuestions(int,std::vector<Course>); //Pass questions and options from mcq as an argument
  std::vector<std::string> getAnswer(int,std::vector<Course>); //pass answer as an argument from mcq
  int generateCourseID();
   // View queries
  void viewQueries(int);
  void viewQueryReply(int);
    
private:
    int courseId{};
    std::string courseName{};
    std::string courseDescription{};
    std::string duration{};
    std::string courseMaterial{};
    int cost{};
    int totalEnrollments{};
    std::vector<std::string> questions{};
    std::vector<std::string> answer{};
    std::string courseTrainer{};
    std::vector<std::string> traineeData{};
    std::string trainerId{};
    std::vector<std::string> queries{};
    std::vector<std::string> reply{};
};

#endif /* Course_hpp */
