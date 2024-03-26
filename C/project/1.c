#include <graphics.h>
#include <conio.h>
#include <math.h>

#define PI 3.1415926535
#define GRAVITY 9.8
#define LENGTH_SCALE 10

struct Pendulum
{
    double length;
    double mass;
    double angle;
    double angularVelocity;
    double angularAcceleration;
};

void updatePendulum(struct Pendulum *pendulum, double dt)
{
    double numerator = -GRAVITY * sin(pendulum->angle);
    double denominator = pendulum->length;
    pendulum->angularAcceleration = numerator / denominator;
    pendulum->angularVelocity += pendulum->angularAcceleration * dt;
    pendulum->angle += pendulum->angularVelocity * dt;
}

void drawPendulum(struct Pendulum *pendulum, int centerX, int centerY)
{
    int x1, y1;

    x1 = centerX + pendulum->length * sin(pendulum->angle);
    y1 = centerY + pendulum->length * cos(pendulum->angle);

    line(centerX, centerY, x1, y1);
    fillcircle(x1, y1, 5);
}

int main()
{
    initgraph(500, 500);

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    struct Pendulum pendulum1 = {100, 5, PI / 2, 0, 0};
    struct Pendulum pendulum2 = {75, 4, PI / 2, 0, 0};
    struct Pendulum pendulum3 = {50, 3, PI / 2, 0, 0};

    double dt = 0.5;

    BeginBatchDraw();
    while (!kbhit())
    {
        cleardevice();

        updatePendulum(&pendulum1, dt);
        updatePendulum(&pendulum2, dt);
        updatePendulum(&pendulum3, dt);

        drawPendulum(&pendulum1, centerX, centerY);
        drawPendulum(&pendulum2, centerX + pendulum1.length * sin(pendulum1.angle), centerY + pendulum1.length * cos(pendulum1.angle));
        drawPendulum(&pendulum3, centerX + pendulum1.length * sin(pendulum1.angle) + pendulum2.length * sin(pendulum2.angle),
                     centerY + pendulum1.length * cos(pendulum1.angle) + pendulum2.length * cos(pendulum2.angle));
        FlushBatchDraw();
        Sleep(20);
    }
    EndBatchDraw();
    closegraph();
    return 0;
}
