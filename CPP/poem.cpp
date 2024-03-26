#include <windows.h>
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    LPCTSTR lpFileName = "F:\\c\\CPP\\test.ini";
    // 写入配置
    BOOL res = WritePrivateProfileString("app", L"name", L"1", lpFileName);

    // 读配置
    LPWSTR content[100];
    DWORD v = GetPrivateProfileString("app", L"name", L""), content, 100, lpFileName);

    // 读数值
    DWORD resv = GetPrivateProfileInt("app", L"name", 0, lpFileName);

    // 读取所有节名

    resv == GetPrivateProfileSectionNames(content, 100, lpFileName);

    // 读取节下的所有键值
    resv = GetPrivateProfileSection("app", content, 100, lpFileName);
}
