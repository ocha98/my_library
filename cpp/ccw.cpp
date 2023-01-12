template<typename T>
int ccw(const Vector2D<T>& a, Vector2D<T> b, Vector2D<T> c){
    b -= a;
    c -= a;

    T cross = b.cross(c);
    if(cross > 0){
        // a->b->cで反時計回り
        return 1;
    }
    if(cross < 0){
        // a->b->c で時計回り
        return -1;
    }

    T dot = b.dot(c);
    if(dot < 0){
        //a->bに対しa->cが180度逆
        return 2;
    }

    if(b.norm() < c.norm()){
        //a->b->cと一方向に進む
        return -2;
    }
    //a->c->bと一方向に進む
    return 0;
}
