#include <cmath>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <sys/timeb.h>
#define kd(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
#define pi acos(-1)
#define size 50
#define r 5
#define n 1
#define g 0.5
#define v 10
#define theta 45
float vy = -v * sin(theta * pi / 180);
float vx = v * cos(theta * pi / 180);
float x = size / 2;
float y = size / 2;

void WinMove(HWND h)
{
    POINT pt;
    GetCursorPos(&pt);
    SetWindowPos(h, HWND_TOPMOST, pt.x + 10, pt.y + 10, size, size, SWP_NOREDRAW);
}

void PutImage(IMAGE *TargetImage, int x, int y, IMAGE *SourceImage, int TargetWidth, int TargetHeight)
{
    HDC TargetDC = GetImageHDC(TargetImage);
    HDC SourceDC = GetImageHDC(SourceImage);
    SetStretchBltMode(TargetDC, HALFTONE);
    StretchBlt(TargetDC, x, y, TargetWidth, TargetHeight, SourceDC, 0, 0, SourceImage->getwidth(), SourceImage->getheight(), SRCCOPY);
}
void BallMove()
{
    timeb t;
    if (kd('A'))
        vx -= 1;
    if (kd('W'))
        vy -= 1;
    if (kd('D'))
        vx += 1;
    if (kd('S'))
        vy += 1;
    for (int i = 8; i <= 222; ++i)
    {
        if (i == 'W' || i == 'S' || i == 'D' || i == 'A')
            continue;
        if (kd(i))
        {
            ftime(&t); // 获取毫秒
            srand((unsigned)t.millitm);
            vx += (rand() % 7) * pow(-1, rand() % 2);
            vy += (rand() % 7) * pow(-1, rand() % 2);
        }
    }
    vx *= 0.99;
    vy *= 0.99;

    x += vx;
    y += (vy += g);

    if (x > size - r)
    {
        vx *= -0.98;
        x = size - r;
    }
    if (x < r)
    {
        vx *= -0.98;
        x = r;
    }
    if (y > size - r)
    {
        y = size - r;
        vy *= -0.98;
    }
    if (y < r)
    {
        y = r;
        vy *= -0.98;
    }
}
// SSAA 抗锯齿实现画圆
void SSAADrawCircle(IMAGE *LineImage, int x, int y)
{
    SetWorkingImage(LineImage);
    setfillcolor(WHITE);
    solidcircle(r * n, r * n, r * n);
    SetWorkingImage();
    PutImage(NULL, x - r, y - r, LineImage, r * 2, r * 2);
}

int main()
{
    HWND h = initgraph(size, size);
    SetWindowLong(h, GWL_STYLE, GetWindowLong(h, GWL_STYLE) & ~WS_CAPTION);
    BeginBatchDraw();
    IMAGE *LineImage = new IMAGE(r * 2 * n, r * 2 * n);

    for (;;)
    {
        WinMove(h);
        cleardevice();
        BallMove();
        SSAADrawCircle(LineImage, x, y);
        FlushBatchDraw();
        Sleep(15);
    }
    EndBatchDraw();
    return 0;
}