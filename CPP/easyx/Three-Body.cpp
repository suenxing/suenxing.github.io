#include <cstdio>
#include <cstdlib>
#include <cmath>
struct Vector
{
    float x;
    float y;
    float z;
};

class Body
{
private:
    Vector _coordinate;
    Vector _speed;
    float _mass;

public:
    Body(float mass, Vector coord);
    void move(Vector force, float time);
    Vector get_speed();
    Vector get_coord();
};

Body::Body(float mass, Vector coord)
{
    _coordinate = coord;
    _mass = mass;
    _speed.x = 0;
    _speed.y = 0;
    _speed.z = 0;
}

void Body::move(Vector force, float time)
{
    Vector accel;
    accel.x = force.x / _mass;
    accel.y = force.y / _mass;
    accel.z = force.z / _mass;

    _speed.x += accel.x * time;
    _speed.y += accel.y * time;
    _speed.z += accel.z * time;

    _coordinate.x += _speed.x * time;
    _coordinate.y += _speed.y * time;
    _coordinate.z += _speed.z * time;
}

Vector Body::get_speed()
{
    return _speed;
}

Vector Body::get_coord()
{
    return _coordinate;
}

const float G = 6.67e-11;

void output_vector(Vector vec, char *comment)
{
    printf("%s: ", comment);
    printf("x: %f, y: %f, z: %f\n", vec.x, vec.y, vec.z);
}

Vector g_force(float m1, Vector p1, float m2, Vector p2, float m3, Vector p3)
{
    float r = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z));
    Vector force;
    float f = G * (m1 * m2) / (r * r);
    force.x = f / r * (p2.x - p1.x);
    force.y = f / r * (p2.y - p1.y);
    force.z = f / r * (p2.z - p1.z);

    r = sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y) + (p1.z - p3.z) * (p1.z - p3.z));
    f = G * (m1 * m3) / (r * r);
    force.x += f / r * (p3.x - p1.x);
    force.y += f / r * (p3.y - p1.y);
    force.z += f / r * (p3.z - p1.z);
    return force;
}

int main()
{

    float m1 = 1e10;
    float m2 = 1e10;
    float m3 = 1e10;

    Vector p1;
    p1.x = 0;
    p1.y = 1;
    p1.z = 0;
    Body b1 = Body(m1, p1);

    Vector p2;
    p2.x = 0.866;
    p2.y = -0.5;
    p2.z = 0;
    Body b2 = Body(m2, p2);

    Vector p3;
    p3.x = -0.866;
    p3.y = -0.5;
    p3.z = 0;
    Body b3 = Body(m3, p3);

    for (int i = 0; i < 100; i++)
    {
        b1.move(g_force(m1, b1.get_coord(), m2, b2.get_coord(), m3, b3.get_coord()), 0.1);
        b2.move(g_force(m2, b2.get_coord(), m1, b1.get_coord(), m3, b3.get_coord()), 0.1);
        b3.move(g_force(m3, b3.get_coord(), m2, b2.get_coord(), m1, b1.get_coord()), 0.1);
        printf("Time: %f\n", (float)i / 10.0);
        output_vector(b1.get_coord(), "b1 coord");
        output_vector(b2.get_coord(), "b2 coord");
        output_vector(b3.get_coord(), "b3 coord");
        printf("\n");
    }
    return 0;
}
