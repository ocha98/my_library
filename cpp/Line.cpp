template<typename T>
struct Line {
    Vector2D<T> p1;
    Vector2D<T> p2;
    Line(Vector2D<T>& p1, Vector2D<T>& p2):p1(p1), p2(p2){}

    //直線の方向ベクトルを返す
    Vector2D<T> direction() const {
        return Vector2D(p2.x - p1.x, p2.y - p1.y);
    }

    bool is_parallel(const Line& l) const {
        Vector2D d1 = l.direction();
        Vector2D d2 = direction();
        return d1.cross(d2) == 0;
    }

    bool is_vertical(const Line& l) const {
        Vector2D d1 = l.direction();
        Vector2D d2 = direction();
        return d1.dot(d2) == 0;
    }

    Vector2D<T> cross_point(const Line& l) const {
        T t = (p1 - l.p1).cross(l.p2 - l.p1) / (l.p2 - l.p1).cross(p2 - p1);
        return p1 + (p2 - p1)*t;
    }

    bool is_intersect(const Line& l) const {
        int v = ccw(p1, p2, l.p1);
        int w = ccw(p1, p2, l.p2);

        int p = ccw(l.p1, l.p2, p1);
        int q = ccw(l.p1, l.p2, p2);

        return v*w <= 0 && p*q <= 0;
    }
};