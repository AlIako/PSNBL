#include "vector3d.h"
#include <cmath>

double distance2V(Vector3D v1, Vector3D v2)
{
    return sqrt((v1.X-v2.X)*(v1.X-v2.X)+(v1.Y-v2.Y)*(v1.Y-v2.Y)+(v1.Z-v2.Z)*(v1.Z-v2.Z));
}

Vector3D::Vector3D()
{
    X = 0;
    Y = 0;
    Z = 0;
}

Vector3D::Vector3D(double x,double y,double z)
{
    X = x;
    Y = y;
    Z = z;
}

Vector3D::Vector3D(const Vector3D & v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
}

Vector3D::Vector3D(const Vector3D & from,const Vector3D & to)
{
    X = to.X - from.X;
    Y = to.Y - from.Y;
    Z = to.Z - from.Z;
}

Vector3D & Vector3D::operator= (const Vector3D & v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
    return *this;
}

Vector3D & Vector3D::operator+= (const Vector3D & v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    return *this;
}

Vector3D Vector3D::operator+ (const Vector3D & v) const
{
    Vector3D t = *this;
    t += v;
    return t;
}

Vector3D & Vector3D::operator-= (const Vector3D & v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
    return *this;
}

Vector3D Vector3D::operator- (const Vector3D & v) const
{
    Vector3D t = *this;
    t -= v;
    return t;
}

Vector3D & Vector3D::operator*= (const double a)
{
    X *= a;
    Y *= a;
    Z *= a;
    return *this;
}

Vector3D Vector3D::operator* (const double a)const
{
    Vector3D t = *this;
    t *= a;
    return t;
}
Vector3D Vector3D::operator* (const Vector3D & v)const
{
    Vector3D t = *this;
    t.X*=v.X;
    t.Y*=v.Y;
    t.Z*=v.Z;
    return t;
}

Vector3D operator* (const double a,const Vector3D & v)
{
    return Vector3D(v.X*a,v.Y*a,v.Z*a);
}

Vector3D & Vector3D::operator/= (const double a)
{
    X /= a;
    Y /= a;
    Z /= a;
    return *this;
}

Vector3D Vector3D::operator/ (const double a)const
{
    Vector3D t = *this;
    t /= a;
    return t;
}

bool Vector3D::operator!= (const Vector3D & v)
{
    if(v.X!=X || v.Y!=Y || v.Z!=Z)
        return true;
    return false;

}
bool Vector3D::operator== (const Vector3D & v)
{
    if(v.X==X && v.Y==Y && v.Z==Z)
        return true;
    return false;

}
Vector3D Vector3D::crossProduct(const Vector3D & v)const
{
    Vector3D t;
    t.X = Y*v.Z - Z*v.Y;
    t.Y = Z*v.X - X*v.Z;
    t.Z = X*v.Y - Y*v.X;
    return t;
}

double Vector3D::length()const
{
    return sqrt( X*X + Y*Y + Z*Z);
}
bool Vector3D::isNull(double value)
{
    return X==value && Y==value && Z==value;
}
void Vector3D::write(std::string nom)
{
    if(nom!="")
        std::cerr << nom << ": ";

    std::cerr << "X: "<< X <<", Y: " << Y << ", Z: " << Z << std::endl;
}
//transforme coordonées en "left-handed"
Vector3D Vector3D::toLeft()
{
    return Vector3D(X,Z,Y);
}

Vector3D & Vector3D::normalize()
{
    (*this) /= length();
    return (*this);
}


