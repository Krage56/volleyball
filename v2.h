#ifndef V2_H
#define V2_H

class V2
{
private:
    double v[2];
public:
    V2();
    V2(double x, double y);
    V2(const V2& copyVec);
// coordinate accessors
    double& x() {return v[0];}
    double x() const {return v[0];}

    double& y() {return v[1];}
    double y() const {return v[1];}
    void swap( V2& other);
// Chech if vector is not trivial
    operator bool() const {return v[0] || v[1];}

// operator +
    V2 operator+(const V2& other) const
    { return V2(v[0]+other.v[0], v[1]+other.v[1]); }

// operator -
    V2 operator-(const V2& other) const
    { return V2(v[0]-other.v[0], v[1]-other.v[1]); }

// operator V2 * V2
    double operator*(const V2& other) const
    { return v[0]*other.v[0] + v[1]* other.v[1]; }

// operator V2 * double
    V2 operator*(double s) const
    {	return V2(s*v[0], s* v[1]);	}

    double len() const;

    const V2& normalize();

};

#endif // V2_H
