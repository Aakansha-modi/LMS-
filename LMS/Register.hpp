//
//  Register.hpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#ifndef Register_hpp
#define Register_hpp

#include <stdio.h>
#include "User.hpp"

class Register {
public:
    // Constructor reads the count of users from file to incorporate out of session entries in files
    Register(){
        //count = int(readFile("registrationCount.txt"));
    }
    std::string generateRegistraionID(std::string);
    std::string addUser();
    void verifyEmail() const;
    void successfulRegistration() const;
private:
    int count{};
};

#endif /* Register_hpp */
