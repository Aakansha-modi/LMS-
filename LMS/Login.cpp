//
//  Login.cpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#include "Login.hpp"
#include "User.hpp"
#include "LmsSystem.hpp"

User* Login::Authenticate(LmsSystem& sys){
    std::cout << "Enter Registration ID: ";
    std::string r{};
    std::getline(std::cin >> std::ws, r);
    std::cout << "Enter Password: ";
    std::string pass{};
    std::getline(std::cin >> std::ws, pass);
    std::cout << std::endl;
    // Extracting the user details using the registration id and checking if password matches
    User* u = sys.getUser(r);
    if (u->getPassword() == pass){
        std::cout << "Login Successful\n";
        return sys.getUser(r);
    }
    else{
        std::cout << "Wrong Password or Registration ID\n";
        return nullptr;
    }
}

void Login::renewMembership(User* u, LmsSystem& sys){
    std::cout<< "\n------Membership Renewal------\n";
    std::string registrationID = sys.getRegisterObj().addUser();
    sys.getRegisterObj().verifyEmail();
    sys.getRegisterObj().successfulRegistration();
    std::cout << "\nMembership Renewal successful.\n";
}
