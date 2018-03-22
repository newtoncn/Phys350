//
// Created by da-cam on 21/03/18.
//

#ifndef PROJECT_SPRING_H
#define PROJECT_SPRING_H

#include "Mass.h"

class Spring {
    Mass Mass1, Mass2;
    float springConstant, springLength, frictionConstant;

public:

    Spring(Mass mass1, Mass mass2, float springConstant, float springLength, float frictionConstant);

private:

    void solve();

};

#endif //PROJECT_SPRING_H
