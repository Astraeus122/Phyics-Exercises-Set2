#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 
{
public:
    float x, y;

    Vector2(float x = 0, float y = 0) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const 
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const 
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) const 
    {
        return Vector2(x * scalar, y * scalar);
    }
};

#endif
