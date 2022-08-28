struct Vector3 {
    int x, y, z;
    Vector3(int x, int y, int z):x(x), y(y), z(z){}
    Vector3(){}
    Vector3 cross_product(const Vector3& b)const{
        Vector3 cross;
        cross.x = y*b.z - z*y;
        cross.y = z*b.x - x*b.z;
        cross.z = x*b.y - y*b.x;
        return cross;
    }

    Vector3 operator-(const Vector3& a)const{
        Vector3 v;
        v.x = x - a.x;
        v.y = y - a.y;
        v.z = z - a.z;
        return v;
    }

    Vector3 operator+(const Vector3& a)const{
        Vector3 v;
        v.x = x + a.x;
        v.y = y + a.y;
        v.z = z + a.z;
        return v;
    }
};