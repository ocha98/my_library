Vector3 center_cross_product(Vector3 o, Vector3 a, Vector3 b){
    Vector3 aa = a - o;
    Vector3 bb = b - o;
    return aa.cross_product(bb);
}