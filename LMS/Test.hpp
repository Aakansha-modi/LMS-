//
// Test.hpp
// LMS
//
// Created by Kriti Dubey on 29/06/23.
//
#ifndef Test_hpp
#define Test_hpp
#include <iostream>
#include <vector>
#include "Course.hpp"

class Test {
public:
  int takeTest(int, const std::vector<std::string>&, const std::vector<std::string>&, std::string);
  int setLevelOfDifficulty(int);
  int evaluate(int, std::vector<std::string>, std::vector<std::string>);
  void saveScore(int, std::string, int, int);
private:
  int m_numberOfQuestions{};
  int m_levelOfDifficulty{};
};

class Mcq : public Test {
public:
  std::vector<std::string> getQuestions(int,int,std::vector<Course>);
  std::vector<std::vector<std::string>> getOptions(int);
  std::vector<std::string> getAnswers(int,int,std::vector<Course>);
private:
  std::vector<std::string> questions{};
  //std::vector<std::vector<std::string>> options{};
  std::vector<std::string> answers{};
};

#endif /* Test_hpp */
