//
//  Login.hpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#ifndef Login_hpp
#define Login_hpp

#include <stdio.h>
#include "User.hpp"

class LmsSystem;

class Login {
public:
    User* Authenticate(LmsSystem& sys);
    void renewMembership(User* u, LmsSystem& sys);
};

#endif /* Login_hpp */
