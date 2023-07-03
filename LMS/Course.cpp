#include "Course.hpp"
#include <iostream>
#include <sqlite3.h>
#include <sstream>

const char* filePath = "/Users/aakansham/Downloads/LMS/LMS/Database.db";

Course::Course (int cid, std::string cName, std::string cDescription, std::string cDuration ,std::string cMaterial, int cCost, int cTotalEnrollments, std::vector<std::string> cQuestions , std::vector<std::string> cAnswers, std::string cTrainer, std::vector<std::string> tData, std::string tID, std::vector<std::string> cQueries, std::vector<std::string> cReply) {
      courseId = cid;
      courseName = cName;
      courseDescription = cDescription;
      duration = cDuration;
      courseMaterial = cMaterial;
      cost = cCost;
      totalEnrollments = cTotalEnrollments;
      questions = cQuestions;
      answer = cAnswers;
      courseTrainer = cTrainer;
      traineeData = tData;
      trainerId = tID;
      queries = cQueries;
      reply = cReply;
}


// update course
void Course::setCourse (int courseId, std::string courseName, std::string courseDescription, std::string duration, std::string courseMaterial, int cost, int totalEnrollments, std::vector<std::string> questions, std::vector<std::string> answer, std::string courseTrainer, std::vector<std::string> traineeData, std::string trainerId, std::vector<std::string> queries, std::vector<std::string> reply) {
  sqlite3* db;
  int rc = sqlite3_open(filePath, &db);
  if (rc != SQLITE_OK) {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    return;
  }
  // Prepare the SQL statement
  std::string query = "INSERT INTO course (courseId, courseName,courseDescription,duration,courseMaterial,cost,totalEnrollments,questions,answer,courseTrainer, traineeData, trainerId, queries, reply) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
  sqlite3_stmt* stmt;
  //std::cout<<courseId;
  rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);
    return;
  }
  std::stringstream ss;
  for (size_t i = 0; i < questions.size(); ++i) {
    ss << questions[i];
    if (i != questions.size() - 1) {
      ss << ",";
    }
  }
  std::string serializedquestions = ss.str();
  std::stringstream aa;
  for (size_t i = 0; i < answer.size(); ++i) {
    aa << answer[i];
    if (i != answer.size() - 1) {
      aa << ",";
    }
  }
  std::string serializedanswer = aa.str();
  std::stringstream td;
  for (size_t i = 0; i < traineeData.size(); ++i) {
    td << traineeData[i];
    if (i != traineeData.size() - 1) {
     td << ",";
    }
  }
  std::string traineeList = td.str();
  std::stringstream tq;
  for (size_t i = 0; i < queries.size(); ++i) {
    tq << queries[i];
    if (i != queries.size() - 1) {
     tq << ",";
    }
  }
  std::string traineeQueries = tq.str();
  std::stringstream tr;
  for (size_t i = 0; i < reply.size(); ++i) {
    tr << reply[i];
    if (i != reply.size() - 1) {
     tr << ",";
    }
  }
  std::string trainerReply = tr.str();
  // Bind the username and password values to the SQL statement
  sqlite3_bind_int(stmt, 1, generateCourseID());
  sqlite3_bind_text(stmt, 2, courseName.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, courseDescription.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, duration.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, courseMaterial.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 6, cost);
  sqlite3_bind_int(stmt, 7, totalEnrollments);
  sqlite3_bind_text(stmt, 8, serializedquestions.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 9, serializedanswer.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 10, courseTrainer.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 11, traineeList.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 12, trainerId.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 13, traineeQueries.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 14, trainerReply.c_str(), -1, SQLITE_STATIC);
  // Execute the SQL statement
  rc = sqlite3_step(stmt);
  // Clean up
  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return;
}

// update course description
void Course::setCourseDescription(int courseId, std::string courseDescription){
    sqlite3* db;
    int rc = sqlite3_open(filePath, &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    std::string updateQuery = "UPDATE Course SET courseDescription = ? WHERE courseId = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
    
    sqlite3_bind_text(stmt, 1, courseDescription.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, courseId);
    
    rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    std::cout << "Course Description Updated Successfully!!\n" << std::endl;
}

// update course duration
void Course::setDuration(int courseId,std::string duration) {
    sqlite3* db;
    int rc = sqlite3_open(filePath, &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    std::string updateQuery = "UPDATE Course SET duration = ? WHERE courseId = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
    
    sqlite3_bind_text(stmt, 1, duration.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, courseId);
    
    rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    std::cout << "Course Duration Updated Successfully!!\n" << std::endl;
}

void Course::setCourseMaterial(int courseId,std::string courseMaterial){
    sqlite3* db;
    int rc = sqlite3_open(filePath, &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    std::string updateQuery = "UPDATE Course SET courseMaterial = ? WHERE courseId = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
    
    sqlite3_bind_text(stmt, 1, courseMaterial.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, courseId);
    
    rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    std::cout << "Course Material Updated Successfully!!" << std::endl;
}

void Course::setTrainerId(int courseId,std::string regId){
    sqlite3* db;
    int rc = sqlite3_open(filePath, &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    std::string updateQuery = "UPDATE Course SET trainerId = ? WHERE courseId = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
    
    sqlite3_bind_text(stmt, 1, regId.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, courseId);
    
    rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    std::cout << "Course Trainer Updated Successfully!!" << std::endl;
}

// update the cost of the course
void Course::setCost(int courseId,int cost){
    sqlite3* db;
    int rc = sqlite3_open(filePath, &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    std::string updateQuery = "UPDATE course SET cost = ? WHERE courseId = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
    
    sqlite3_bind_int(stmt, 1, cost);
    sqlite3_bind_int(stmt, 2, courseId);
    
    rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    std::cout << "Course Cost Updated Successfully!!\n" << std::endl;
}

// update the question and answers
void Course::setQuestionAnswer(int courseId, std::string questions, std::string answer) {
    sqlite3* db;
    int rc = sqlite3_open(filePath, &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
//    std::string query = "SELECT questions,answer FROM Course WHERE courseId = ?";
    sqlite3_stmt* stmt;
//    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
//       if (rc != SQLITE_OK) {
//           std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
//            return;
//    }
//    sqlite3_bind_int(stmt, 1, courseId);
//
//    int columnCount = sqlite3_column_count(stmt);
//    //std::cout<<columnCount;
//    const unsigned char* ques;
//    std::vector<std::vector<std::string>> questionAnswerList{};
//    while (sqlite3_step(stmt) == SQLITE_ROW) {
//        for (int i = 0; i < columnCount; i++) {
//            //std::cout<<sqlite3_column_text(stmt, i)<<"-----";
//            std::vector<std::string> temp{};
//            ques = sqlite3_column_text(stmt, i);
//            std::string word(reinterpret_cast<const char*>(ques));
//            //std::cout<<ques;
//            std::stringstream ss(word);
//            std::string token;
//            while (std::getline(ss, token, ',')) {
//                temp.push_back(token);
//            }
//            questionAnswerList.push_back(temp);
//        }
//    }
//
//    questionAnswerList[0][qnum] = questions;
//    questionAnswerList[1][qnum] = answer;
//
//    std::ostringstream ossQues;
//    std::ostringstream ossAns;
//
//    for (size_t i = 0; i < questionAnswerList[0].size(); i++) {
//        //std::cout<<questionAnswerList[0].size() << "+";
//        ossQues << questionAnswerList[0][i];
//        if (i != questionAnswerList[0].size() - 1) {
//                ossQues << ",";
//        }
//    }
//
//    // split answer string
//    for (size_t i = 0; i < questionAnswerList[1].size(); i++) {
//        ossAns << questionAnswerList[1][i];
//        if (i != questionAnswerList[1].size() - 1) {
//                ossAns << ",";
//        }
//    }
//
//    std::string updatedQuestion = ossQues.str();
//    std::string updatedAnswer = ossAns.str();
    
    std::string updateQuery = "UPDATE Course SET questions = ? , answer = ? WHERE courseId = ?";
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
    
    sqlite3_bind_text(stmt, 1, questions.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, answer.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, courseId);
    //std::cout<<rc;
    rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    std::cout<<"Course Questions and Answers Updated Successfully!!\n";
}

void Course::getTotalEnrollments(int courseId, std::vector<Course> courses) {
    std::cout<<courses[courseId-1].totalEnrollments;
}

std::vector<std::string> Course::getQuestions(int courseId, std::vector<Course> courses){
    std::vector<std::string> ques = courses[courseId].questions;
    return ques;
}

std::vector<std::string> Course::getAnswer(int courseId, std::vector<Course> courses){
    std::vector<std::string> ans = courses[courseId].answer;
    return  ans;
}

int Course::generateCourseID(){
    // filePath denotes path to the txt containing an integer denoting regId already assigned
    std::string filePath{"/Users/aakansham/Downloads/LMS/LMS/CourseID.txt"};
    std::ifstream inputFile(filePath);
        if (!inputFile) {
            std::cerr << "Error opening Course Id.txt "  << std::endl;
            return -1;
        }

        int id;
        inputFile >> id;
        inputFile.close();
        int uniqueID = id;
        id++;

        std::ofstream outputFile(filePath);
        if (!outputFile) {
            std::cerr << "Error opening Course Id.txt " << std::endl;
            return -1;
        }

        outputFile << id;
        outputFile.close();

        return uniqueID;
}

void Course::addQueries(int courseId, std::string q){
      sqlite3* db;
      int rc = sqlite3_open(filePath, &db);
      if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      std::string query = "SELECT queries FROM Course WHERE courseId = ?";
      sqlite3_stmt* stmt;
      rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
      if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      rc = sqlite3_bind_int(stmt, 1, courseId);
      if (rc != SQLITE_OK) {
        std::cout << "Cannot bind parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
      }
      std::string qList{};
      while (sqlite3_step(stmt) == SQLITE_ROW) {
        qList = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
      }
      if(qList=="") {
        qList += q;
      }
      else {
        qList += ',' + q;
      }
      std::string updateQuery = "UPDATE Course SET queries = ? WHERE courseId = ?";
      sqlite3_stmt* ustmt;
      rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &ustmt, nullptr);
      if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
          return;
      }
      sqlite3_bind_text(ustmt, 1, qList.c_str(), -1, SQLITE_STATIC);
      sqlite3_bind_int(ustmt, 2, courseId);
      rc = sqlite3_step(ustmt);
        if (rc != SQLITE_DONE) {
          std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
          return;
        }
      // Clean up
      sqlite3_finalize(stmt);
      sqlite3_close(db);
      std::cout<<"New query added Successfully!!\n";
    }
    

void Course::viewQueries(int courseId){
    sqlite3* db;
    int rc = sqlite3_open(filePath, &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    std::string query = "SELECT queries FROM Course WHERE courseId = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
      std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    rc = sqlite3_bind_int(stmt, 1, courseId);
    if (rc != SQLITE_OK) {
      std::cout << "Cannot bind parameter: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_finalize(stmt);
      sqlite3_close(db);
      return;
    }
    std::string qList{};
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      qList = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }
    std::vector<std::string> queryList;
    std::stringstream ss(qList);
        while (ss.good()) {
            std::string qr;
            getline(ss, qr, ',');
            queryList.push_back(qr);
        }
    for(int i=0;i<queryList.size();i++){
        std::cout<<"Query"<<i+1<<" "<<queryList[i]<<std::endl;
    }
    std::cout<<"Enter query number you want to ans: "<<std::endl;
    int qid;
    std::cin>>qid;
    std::string reply;
    std::cout<<"Enter your response"<<std::endl;
    std::getline(std::cin >> std::ws, reply);
    addReply(courseId, reply);
    
}

void Course::addReply(int courseId, std::string r){
     sqlite3* db;
      int rc = sqlite3_open(filePath, &db);
      if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      std::string query = "SELECT reply FROM Course WHERE courseId = ?";
      sqlite3_stmt* stmt;
      rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
      if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
      rc = sqlite3_bind_int(stmt, 1, courseId);
      if (rc != SQLITE_OK) {
        std::cout << "Cannot bind parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
      }
      //std::cout<<SQLITE_ROW;
      std::string rList{};
      while (sqlite3_step(stmt) == SQLITE_ROW) {
        rList = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
      }
      if(rList=="") {
        rList+=r;
      }
      else {
        rList += ',' + r;
      }
      std::string updateQuery = "UPDATE Course SET reply = ? WHERE courseId = ?";
      sqlite3_stmt* ustmt;
      rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &ustmt, nullptr);
      if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
          return;
      }
      sqlite3_bind_text(ustmt, 1, rList.c_str(), -1, SQLITE_STATIC);
      sqlite3_bind_int(ustmt, 2, courseId);
      rc = sqlite3_step(ustmt);
        if (rc != SQLITE_DONE) {
          std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
          return;
        }
      
      // Clean up
      sqlite3_finalize(stmt);
      sqlite3_close(db);
      std::cout<<"New reply added successfully!!\n";
}

void Course::addNewTrainee(int courseId, std::string regId) {
    sqlite3* db;
    int rc = sqlite3_open(filePath, &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    std::string query = "SELECT traineeData, totalEnrollments FROM Course WHERE courseId = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
      std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    rc = sqlite3_bind_int(stmt, 1, courseId);
    if (rc != SQLITE_OK) {
      std::cout << "Cannot bind parameter: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_finalize(stmt);
      sqlite3_close(db);
      return;
    }
    std::string tList{};
    int tEnrol{};
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      tList = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
      tEnrol= (sqlite3_column_int(stmt, 1));
    }
    if(tList==""){
        tList+=regId;
    }
    else{
        tList += ',' + regId;
    }
    tEnrol += 1;
    std::string updateQuery = "UPDATE Course SET traineeData = ?, totalEnrollments = ? WHERE courseId = ?";
    sqlite3_stmt* ustmt;
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &ustmt, nullptr);
    if (rc != SQLITE_OK) {
      std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        //return false;
    }
    sqlite3_bind_text(ustmt, 1, tList.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(ustmt, 2, tEnrol);
    sqlite3_bind_int(ustmt, 3, courseId);
    rc = sqlite3_step(ustmt);
      if (rc != SQLITE_DONE) {
        std::cerr << "Failed to update course: " << sqlite3_errmsg(db) << std::endl;
        return;
      }
    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    std::cout<<"New Trainee added Successfully!!\n";
  }


void Course::viewQueryReply(int courseId){
    sqlite3* db;
    int rc = sqlite3_open(filePath, &db);
    if (rc != SQLITE_OK) {
      std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    std::string query = "SELECT queries ,reply FROM Course WHERE courseId = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
      std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
      return;
    }
    rc = sqlite3_bind_int(stmt, 1, courseId);
    if (rc != SQLITE_OK) {
      std::cout << "Cannot bind parameter: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_finalize(stmt);
      sqlite3_close(db);
      return;
    }
    std::string qList{};
    std::string rList{};
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      qList = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        rList = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    }
    std::vector<std::string> queryList{};
    std::stringstream ss(qList);
        while (ss.good()) {
            std::string qr;
            getline(ss, qr, ',');
            queryList.push_back(qr);
        }
    std::vector<std::string> replyList{};
    std::stringstream rl(rList);
        while (rl.good()) {
            std::string qr;
            getline(rl, qr, ',');
            replyList.push_back(qr);
        }
    for(int i=0;i<queryList.size();i++){
        std::cout<<"Query"<<i+1<<" "<<" - "<<queryList[i]<<std::endl;
    }
    for(int i=0;i<replyList.size();i++){
        std::cout<<"Reply of query"<<i+1<<" - "<<replyList[i]<<std::endl;
    }
}





