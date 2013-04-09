#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

struct vector3
{
    float x, y, z;

    vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    vector3() : vector3(0,0,0) {}

    vector3 operator*(float mul)
    {
        return vector3(x*mul, y*mul, z*mul);
    }

    vector3 operator/(float div)
    {
        return vector3(x/div, y/div, z/div);
    }

    vector3 & operator+=(const vector3 &o)
    {
        x += o.x;
        y += o.y;
        z += o.z;
        return *this;
    }

    vector3 & operator-=(const vector3 &o)
    {
        x -= o.x;
        y -= o.y;
        z -= o.z;
        return *this;
    }
};


#endif // PRIMITIVES_HPP
