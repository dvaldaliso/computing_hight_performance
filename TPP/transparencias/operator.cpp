#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

class Vector
{
private:
    float x, y;
public:
    Vector(float x, float y);
    Vector Add(const Vector& other) const;
    Vector Mult(const Vector& other) const;
    Vector operator+(const Vector& other)const {
        return Add(other);
    };

    //friend Vector operator*(const Vector& lf, const Vector& other) const {};
    float getx()const{return x;}
    float gety()const{return y;}
    ~Vector();
};

Vector::Vector(float x, float y): x{x}, y{y} {}

Vector Vector::Add(const Vector& other) const{
    return Vector(x * other.getx(), y * other.gety());
}
Vector Vector::Mult(const Vector& other) const{
    return Vector(x * other.getx(), y * other.gety());
}
Vector operator*(const Vector& lf, const Vector& other) {
    return Vector(lf.getx() * other.getx(), lf.gety() * other.gety());
}

ostream& operator <<( ostream& outStream , const Vector& vector ) {
return outStream << vector.getx() <<","<< vector.gety()  ;
}


Vector::~Vector()
{
}

int main( int argc, char *argv[] ) {
    Vector position(2,5);
    Vector speed(2,5);
    Vector powerup(4,6);

    Vector sum = position.Add(speed.Mult(powerup));
    Vector sumOperator = position + speed * powerup;
    cout << "valor x " << sum << endl; 
    cout << "valor operador x " << sumOperator << endl; 

  return 0;
}

