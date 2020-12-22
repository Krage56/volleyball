#include "v2.h"
#include <cmath>
#include <stdexcept>

V2::V2()
{
    v[0] = 0;
    v[1] = 0;
}

V2::V2(double x, double y){
    v[0] = x;
    v[1] = y;
}

void V2::swap(V2 &other){
    std::swap(x(), other.x());
    std::swap(y(), other.y());
}


double V2::len()const{
    return sqrt(v[0] * v[0] + v[1] * v[1]);
}

const V2& V2::normalize(){
    if(!operator bool()){
        throw std::runtime_error("normalize() for trivial V2 called");
    }

     double normalizer = 1.0 / len();
     V2 res = (*this) * (normalizer);
     swap(res);
     return *this;
}

V2::V2(const V2& copyVec){
    v[0] = copyVec.v[0];
    v[1] = copyVec.v[1];
}
