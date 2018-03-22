//
// Created by da-cam on 21/03/18.
//

#include <vector3D.h>

Vector3D::Vector3D(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::Vector3D() {}

void Vector3D::Display() const
{
    std::cout << x << ", " << y << ", " << z << std::endl;
}

Vector3D operator+(const Vector3D&  other) {
	//Define how should the classes be added here

	//Example addition of private fields within V
	

	//Return the 'added' object as a new instance of class V
	return V(field1);