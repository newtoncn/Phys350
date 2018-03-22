//
// Created by da-cam on 21/03/18.
//

#ifndef PHYS350_VECTOR3D_H
#define PHYS350_VECTOR3D_H

#include <iostream>

class Vector3D
{
public:
    double x, y, z;

    Vector3D(double x, double y, double z);

	Vector3D();

    void Display() const;
};

#endif //PHYS350_VECTOR3D_H
