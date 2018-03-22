//
// Created by da-cam on 21/03/18.
//

#include "../include/Mass.h"

Mass::Mass(float m)// Constructor.
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

void simulate(float dt){
    vel += (force /m) * dt;

    pos += vel *  dt;

}
