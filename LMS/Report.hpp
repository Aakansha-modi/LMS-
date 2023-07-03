//
//  Report.hpp
//  LMS
//
//  Created by Isha Sehrawat . on 28/06/23.
//

#ifndef Report_hpp
#define Report_hpp

#include <stdio.h>
#include "User.hpp"
#include "Trainee.hpp"
#include "Trainer.hpp"

class LmsSystem;

class Report {
public:
    void generateReport(User* u, LmsSystem& sys);
    void generateReportForTrainee(Trainee* t);
    void generateReportForTrainer(Trainer* t);
    void generateReportForAdmin(LmsSystem& sys);
};

#endif /* Report_hpp */
