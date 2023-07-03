//
// Test.cpp
// LMS
//
// Created by Kriti Dubey on 29/06/23.
//
#include "Test.hpp"
#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <cstring>
int Test::takeTest(int courseId, const std::vector<std::string>& questions, const std::vector<std::string>& answers, std::string regId) {
  // Give questions to the user
  std::vector<std::string> userAnswers{};
  for (int i = 0 ; i < questions.size() ; i++) {
    std::cout << "Question " << i+1 << ": " << questions[i] << std::endl;
    std::string answer;
    std::cout << "Your answer: ";
    std::cin >> answer;
    userAnswers.push_back(answer);
  }
  // Send user answers to evaluate
  int score = evaluate(courseId, userAnswers, answers);
  int status{} ;
  // Display the score
  if(score >= (0.8 * questions.size())) {
    status = 1;
    std::cout << "Your score: " << score << "\n";
    std::cout << "------------" << std::endl;
    std::cout << "Congrats!! you passed the course" << std::endl;
  }
  else {
    status = 0;
    std::cout << "Your score: " << score << "\n";
    std::cout << "------------" << std::endl;
    std::cout << "Sorry!! you failed the course" << std::endl;
  }
  //std::cout<<"------"<<regId;
  saveScore(courseId, regId, score, status);
  return score;
}
void Test::saveScore(int courseId, std::string traineeId, int score, int status){
  sqlite3* db;
  //std::cout<<traineeId;
  int rc = sqlite3_open("/Users/aakansham/Downloads/LMS/LMS/Database.db", &db);
  if (rc != SQLITE_OK) {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
  }
  std::string query = "INSERT INTO testResult (courseId, traineeId, score, status) VALUES (?,?,?,?)";
   sqlite3_stmt* stmt;
   //std::cout<<courseId;
   rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
   if (rc != SQLITE_OK) {
    std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
  sqlite3_close(db);
  //return false;
 }
  sqlite3_bind_int(stmt, 1, courseId);
  sqlite3_bind_text(stmt, 2, traineeId.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 3, score);
  sqlite3_bind_int(stmt, 4, status);
  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  sqlite3_close(db);
}
int Test::setLevelOfDifficulty(int levelOfDifficulty) {
  // set the level of difficulty
  m_levelOfDifficulty = levelOfDifficulty;
  return m_levelOfDifficulty;
}
int Test::evaluate(int courseId, std::vector<std::string> userAnswers, std::vector<std::string> answersList) {
  // evaluate the naswers
  int score{};
  //std::cout<<answersList.size();
  for(size_t i=0; i<userAnswers.size(); i++) {
    std::string userAnswerLower = userAnswers[i];
    std::transform(userAnswerLower.begin(), userAnswerLower.end(), userAnswerLower.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    std::string correctAnswerLower = answersList[i];
    std::transform(correctAnswerLower.begin(), correctAnswerLower.end(), correctAnswerLower.begin(), [](unsigned char c) {
      return std::tolower(c);
    });
    if (userAnswerLower == correctAnswerLower) {
          score++;
    }
  }
  return score;
}
std::vector<std::string> Mcq::getQuestions(int courseId, int levelOfDifficulty, std::vector<Course> courses) {
  std::vector<std::string> questionsList{};
  //std::cout<<questions.size()<<"---"<<courseId;
  questionsList = courses[courseId].getQuestions(courseId,courses);
  if(levelOfDifficulty == 0 && questionsList.size() >= 2){
    return std::vector<std::string>(questionsList.begin(), questionsList.begin() + 2);
  }
  else if(levelOfDifficulty == 1 && questionsList.size() >= 20) {
    return std::vector<std::string>(questionsList.begin(), questionsList.begin() + 20);
  }
  else if(levelOfDifficulty == 2 && questionsList.size() >= 30) {
    return std::vector<std::string>(questionsList.begin(), questionsList.begin() + 30);
  }
  else {
    std::cout << "Sorry! Questions Not Available" << std::endl;
  }
  return {};
}
std::vector<std::string> Mcq::getAnswers(int courseId, int levelOfDifficulty, std::vector<Course> courses) {
  std::vector<std::string> answersList{};
  answersList = courses[courseId].getAnswer(courseId,courses);
    //std::cout<<answersList.size();
  if(levelOfDifficulty == 0 && answersList.size() >= 2){
    return std::vector<std::string>(answersList.begin(), answersList.begin() + 2);
  }
  else if(levelOfDifficulty == 1 && answersList.size() >= 20) {
    return std::vector<std::string>(answersList.begin(), answersList.begin() + 20);
  }
  else if(levelOfDifficulty == 2 && answersList.size() >= 30) {
    return std::vector<std::string>(answersList.begin(), answersList.begin() + 30);
  }
  return {};
}
