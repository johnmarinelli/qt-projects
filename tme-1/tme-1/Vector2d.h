#ifndef VECTOR2D_H
#define VECTOR2D_H

template <typename T>
struct Vector2d
{
    T x;
    T y;

    Vector2d(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator<(const Vector2d& other) const
    {
        return x < other.x || y < other.y;
    }
};

#endif // VECTOR2D_H
