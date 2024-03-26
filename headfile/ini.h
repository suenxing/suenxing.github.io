#include <stdio.h>
#include <windows.h>

int ReadInt(const char filepath[], const char title[], const char key[])
{
    return GetPrivateProfileInt(title, key, 0, filepath);
}

char *ReadStr(const char filepath[], const char title[], const char key[])
{
    char *buf = (char *)malloc(256);
    GetPrivateProfileString(title, key, "", buf, 256, filepath);
    return buf;
}

void WriteInt(const char filepath[], const char title[], const char key[], int value)
{
    char tmp[64];
    sprintf(tmp, "%d", value);
    WritePrivateProfileString(title, key, tmp, filepath);
}

void WriteInt(const char filepath[], const char title[], const char key[],const char value[])
{
    WritePrivateProfileString(title, key, value, filepath);
}

void WriteStr(const char filepath[], const char title[], const char key[], const char value[])
{
    WritePrivateProfileString(title, key, value, filepath);
}