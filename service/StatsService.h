//
// Created by Nicolas on 18/11/2020.
//

#ifndef MAIN_CPP_STATISTIQUES_H
#define MAIN_CPP_STATISTIQUES_H


#include <SQLAPI.h>

class StatsService {
public:
    static double getAvarageCartValue();
    static double getMonthlyEarning(SADateTime DateTime);
};


#endif //MAIN_CPP_STATISTIQUES_H
