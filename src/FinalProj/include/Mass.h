//
// Created by da-cam on 21/03/18.
//

#ifndef PROJECT_MASS_H
#define PROJECT_MASS_H

using namespace std;

#include "vector3D.h"


class Mass {
    float m;                                          // The Mass Value.
    vector3D pos;                               // Position In Space.
    vector3D vel;                               // Velocity.
    vector3D force;                             // Force Applied On This Mass At An Instance.

public:
    Mass(float m)                               // Constructor.
    {
        this->m = m;
    }

    void applyForce(Vector3D force)
    {
        this->force += force;                        // The External Force Is Added To The Force On The Mass.
    }

    void init()                             // This Method Sets The Force Values To Zero.
    {
        force.x = 0;
        force.y = 0;
        force.z = 0;
    }
};


#endif //PROJECT_MASS_H
