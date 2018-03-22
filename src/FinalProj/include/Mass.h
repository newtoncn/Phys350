//
// Created by da-cam on 21/03/18.
//

#ifndef PROJECT_MASS_H
#define PROJECT_MASS_H

using namespace std;

#include <vector3D.h>


class Mass {
    float m;                                          // The Mass Value.
    Vector3D pos;                               // Position In Space.
	Vector3D vel;                               // Velocity.
	Vector3D force;                             // Force Applied On This Mass At An Instance.

public:
	Mass(float m);                               // Constructor.

	void applyForce(Vector3D force1);

	void init();                            // This Method Sets The Force Values To Zero.

	void simulate(float dt);
};


#endif //PROJECT_MASS_H
