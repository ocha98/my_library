template <typename  T>
struct Vector2D {
    T x, y;
    Vector2D(T x=0, T y=0):x(x), y(y){}

   T abs()const {
        return sqrt(norm());
    }

    T norm()const {
        return x*x + y*y;
    }

    //外積(z軸方向のみ)
    T cross(const Vector2D& a) const {
        return x*a.y - y*a.x;
    }

    //単位ベクトルを求める
    Vector2D unitVector() const {
        return Vector2D(*this)/abs();
    }

    Vector2D rotate(const double theta) const {
    //原点中心に回転
        T x = x*cos(theta) - y*sin(theta);
        T y = x*sin(theta) + y*cos(theta);
        return Vector2D(x, y);
    }

    //中心の位置を指定して回転
    Vector2D rotate(const double theta, Vector2D& center) const {
        Vector2D vec(*this);
        vec -= center;
        return vec.rotate(theta) + center;
    }

    //反時計回り90度回転
    Vector2D normal()const {
        return Vector2D(-y, x);
    }

    //中心の位置を指定して反時計回り90度回転
    Vector2D normal(Vector2D& center)const {
        Vector2D vec(*this);
        vec -= center;
        return vec.normal() + center;
    }

    T dot(const Vector2D& a) const {
        return x*a.x + y*a.y;
    }

    Vector2D& operator+=(const Vector2D& a){
        x += a.x;
        y += a.y;
        return *this;
    }

    Vector2D operator+(const Vector2D& a)const {
        return Vector2D(*this) += a;
    }

    Vector2D& operator-=(const Vector2D& a){
        x -= a.x;
        y -= a.y;
        return *this;
    }

    Vector2D operator-(const Vector2D& a)const {
        return Vector2D(*this) -= a;
    }

    Vector2D& operator*= (const T a){
        x *= a;
        y *= a;
        return *this;
    }

    Vector2D operator*(const T a)const {
        return Vector2D(*this) *= a;
    }

    Vector2D& operator/= (const T a){
        x /= a;
        y /= a;
        return *this;
    }

    Vector2D operator/(const T a)const {
        return Vector2D(*this) /= a;
    }

    bool operator==(const Vector2D& a)const {
        return x == a.x && y == a.y;
    }

    bool operator!=(const Vector2D& a)const {
        return x != a.x || y != a.y;
    }
};

template<typename T>
istream& operator>>(istream& is, Vector2D<T>& a){
    T x, y;
    is >> x >> y;
    a.x = x;
    a.y = y;
    return is;
}
