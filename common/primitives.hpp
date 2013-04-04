#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

struct vector3
{
    vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    vector3() : vector3(0,0,0) {}
    float x, y, z;
};


#endif // PRIMITIVES_HPP
