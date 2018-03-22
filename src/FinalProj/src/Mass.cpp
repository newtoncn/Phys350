//
// Created by da-cam on 21/03/18.
//

#include <Mass.h>

Mass::Mass(float m)// Constructor.
    {
        this->m = m;
		this->init;
    }

void Mass::applyForce(Vector3D force1)
{
	force.x = force.x + force1.x;  // The External Force Is Added To The Force On The Mass.
	force.y = force.y + force1.y;
	force.z = force.z + force1.z;
}


void Mass::init()                             // This Method Sets The Force Values To Zero.
    {
	force = Vector3D(0, 0, 0);
    }

void Mass::simulate(float dt){
    vel += (force / m) * dt;

    pos += vel *  dt;

}
