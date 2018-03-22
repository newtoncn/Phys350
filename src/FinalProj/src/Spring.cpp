//
// Created by da-cam on 21/03/18.
//

#include <Spring.h>

Spring::Spring(Mass* mass1, Mass* mass2, float springConstant, float SpringLength, float frictionConstant) {
    this->springConstant = springConstant;               // Set The springConstant
    this->springLength = springLength;               // Set The springLength
    this->frictionConstant = frictionConstant;           // Set The frictionConstant

    this->Mass1* => mass1;                     // Set mass1
    this->Mass2* => mass2;                     // Set mass2
}

void Spring::solve() {
    Vector3D springVector = Mass1->pos - Mass2->pos;      // Vector Between The Two Masses

    float r = springVector.length();                // Distance Between The Two Masses

    Vector3D force;                         // Force Initially Has A Zero Value

    if (r != 0) {                     // To Avoid A Division By Zero... Check If r Is Zero
    // The Spring Force Is Added To The Force
    force += -(springVector / r) * (r - springLength) * springConstant;
    }
}