template <typename  T>
struct Vector3D {
    T x, y, z;
    Vector3D(T x=0, T y=0, T z=0):x(x), y(y), z(z){}
    Vector3D cross(const Vector3D& b)const{
        Vector3D cross;
        cross.x = y*b.z - z*y;
        cross.y = z*b.x - x*b.z;
        cross.z = x*b.y - y*b.x;
        return cross;
    }

    T dot(const Vector3D& a) const {
        return x*a.x + y*a.y + z*a.z;
    }

    Vector3D operator-(const Vector3D& a)const{
        return Vector3D(*this) -= a;
    }

    Vector3D operator+(const Vector3D& a)const{
        return Vector3D(*this) += a;
    }

    Vector3D& operator+=(const Vector3D& a)const {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }

    Vector3D& operator-=(const Vector3D& a)const {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }
};