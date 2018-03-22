//
// Created by da-cam on 21/03/18.
//

Vector3D::Vector3D(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3D::Display() const
{
    std::cout << x << ", " << y << ", " << z << std::endl;
}