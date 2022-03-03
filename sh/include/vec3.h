#pragma once

template <class T>
class vec3
{
    public:
        vec3();
        vec3(T x, T y, T z):x(x),y(y),z(z){}

        T x,y,z;
};
