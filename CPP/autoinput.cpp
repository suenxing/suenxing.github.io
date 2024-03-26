#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#define max 8
struct time
{
	int h;
	int m;
} tmtb[max] = {
	{13, 30}, {18, 40}, {18, 50}, {18, 50}, {19, 0}, {19, 15}, {19, 30}, {21, 0}};

void PressKey(BYTE key)
{
	keybd_event(key, 0, 0, 0);
	Sleep(100);
	keybd_event(key, 0, 2, 0);
}
void PressKey(BYTE key1, BYTE key2)
{
	keybd_event(key1, 0, 0, 0);
	keybd_event(key2, 0, 0, 0);
	Sleep(100);
	keybd_event(key1, 0, 2, 0);
	keybd_event(key2, 0, 2, 0);
}

int setClip(const char *data)
{
	int contentSize = strlen(data) + 1;
	HGLOBAL hMemory;
	LPTSTR lpMemory;
	if (!OpenClipboard(NULL))
		return 0; /* 打开剪切板 */
	if (!EmptyClipboard())
		return 0; /* 清空剪切板 */
	if (!(hMemory = GlobalAlloc(GMEM_MOVEABLE, contentSize)))
		return 0; /* 对剪切板分配内存 */
	if (!(lpMemory = (LPTSTR)GlobalLock(hMemory)))
		return 0;										/* 锁定内存区域 */
	memcpy_s(lpMemory, contentSize, data, contentSize); /* 复制数据到内存区域 */
	GlobalUnlock(hMemory);								/* 解除内存锁定 */
	if (!SetClipboardData(CF_TEXT, hMemory))
		return 0;	  /* 设置剪切板数据 */
	CloseClipboard(); /* 关闭剪切板 */
	return 1;
}

void sendmsg(char *text)
{
	setClip(text);
	PressKey(VK_CONTROL, 'V');
	PressKey(VK_MENU, 'S');
}

int main()
{
	char text[max][64] = {
		"中午好呀", "下午好啊，这个点你应该放学了", "在学校过得咋样", "今天都学了些啥内容，都能消化吗", "今天周五，你明天就能休息了，开心吗", "你作业多吗，都有些啥", "记得早点睡觉，熬夜对身体不好", "晚自习真难熬，足足四个小时"};
	time_t rawtime;
	tm *info;
	HWND h = FindWindowW(L"TXGuiFoundation", L"江云英 Eden");
	for (int order = 0; order < max;)
	{

		time(&rawtime);
		info = gmtime(&rawtime);
		if (info->tm_hour + 8 >= tmtb[order].h && info->tm_min >= tmtb[order].m)
		{
			h = FindWindowW(L"TXGuiFoundation", L"江云英 Eden");
			SetForegroundWindow(h);
			sendmsg(text[order]);
			printf("第%d讯息已发出，内容是：%s [%d:%d]\n", order, text[order], info->tm_hour + 8, info->tm_min);
			order++;
		}
		else
		{
			printf("未到达指定时间 [%d:%d]\n", info->tm_hour + 8, info->tm_min);
			_sleep(300000);
		}
	}
	system("shutdown -s -t 1");
	exit(0);
}
