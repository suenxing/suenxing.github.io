#include <conio.h>
#include <cstdio>
#include <stdlib.h>
#include <ctime>
#include <cstring>
#include <io.h>
#include <windows.h>
#include <locale>
#include <wchar.h>
#include <algorithm>

#define CMDSIZE 12

using namespace std;

typedef wchar_t wc;

enum colors
{
	black,
	blue,
	green,
	lake,
	red,
	purple,
	yellow,
	white,
	grey,
	lblue,
	lgreen,
	cyan,
	lred,
	lpurple,
	lyellow,
	lwhite,
};

wc com[16][256]; /* 输入信息 */
wc head[256];	 /* 文件头（目录） */
wc file[256];	 /* 文件名 */

/* 更改控制台文字颜色 */
void color(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x % 16);
}

/* 清空控制台 */
void cls()
{
	system("cls");
}

/* 格式化输出文件大小 */
void mksize(const struct _finddata_t fileinfo)
{
	wc name[260];
	mbstowcs(name, fileinfo.name, 260);
	if (fileinfo.size > 1073741824) /* 1GB */
	{
		wprintf(L"%-8.2lf GB\t%ls\n", fileinfo.size / 1073741824.0, name);
	}
	else if (fileinfo.size > 1048576) /* 1MB */
	{
		wprintf(L"%-8.2lf MB\t%ls\n", fileinfo.size / 1048576.0, name);
	}
	else if (fileinfo.size > 1024) /* 1KB */
	{
		wprintf(L"%-8.2lf KB\t%ls\n", fileinfo.size / 1024.0, name);
	}
	else
	{
		wprintf(L"%-8lu B\t%ls\n", fileinfo.size, name);
	}
}
/* 帮助 */
void help()
{
	color(lyellow);
	wprintf(
		L"help 打开帮助\n"
		L"cd [文件夹] 进入文件夹\n"
		L"cls 清空控制台\n"
		L"dir 显示文件夹内文件\n"
		L"read 读取文件内容\n"
		L"rename [旧文件名] [新文件名] 重命名文件\n"
		L"mv [旧文件名] [新文件地址] 移动当前目录下的文件到新的地址\n"
		L"open [文件名] 打开当前目录下的指定文件\n"
		L"rm [文件名/*] 删除当前目录下的指定文件(*为删除所有)\n"
		L"ver 查看版本信息\n"
		L"start 运行程序/打开网页 (system函数套壳)\n"
		L"do [文件操作符] [文件名] {内容} 对当前目录指定文件进行操作(w 覆写 / r 读取 / a 追加)\n");
}
/* 输入 */
void input()
{
	int i = 0;
	wc *s, str[256];
	memset(com, 0, sizeof(com));
	color(grey);
	wprintf(L"%ls>", head);
	color(lwhite);
	_getws(str);
	fflush(stdin);
	color(grey);
	s = wcstok(str, L" ");
	while (s != NULL)
	{
		wcscpy(com[i++], s);
		s = wcstok(NULL, L" ");
	}
}
/* 移动文件 */
void mv()
{
	wc file[256];
	wcscpy(file, head);
	wcscat(file, com[1]);
	if (_waccess(file, F_OK))
	{
		color(lred);
		wprintf(L"%ls 不存在 !\n", com[1]);
		color(grey);
		return;
	}
	else
	{
		if (_wrename(file, com[2]))
		{
			color(lred);
			wprintf(L"移动失败！\n");
			color(grey);
		}
		else
		{
			color(lgreen);
			wprintf(L"移动成功！\n");
			color(grey);
		}
	}
}
/* 重命名文件 */
void ren()
{
	wc f1[256];
	wc f2[256];
	wcscpy(f1, head);
	wcscat(f1, com[1]);
	wcscpy(f2, head);
	wcscat(f2, com[2]);
	if (_waccess(f1, F_OK))
	{
		color(lred);
		wprintf(L"%ls 不存在 !\n", com[1]);
		color(grey);
		return;
	}
	else
	{
		if (_wrename(f1, f2))
		{
			color(lred);
			wprintf(L"改名失败！\n");
			color(grey);
		}
		else
		{
			color(lgreen);
			wprintf(L"改名成功！\n");
			color(grey);
		}
	}
}
/* 进入文件夹 */
void cd()
{
	/* 相对路径 */
	if (wcscmp(com[1], L"here") == 0)
	{
		wc path[256];
		wcscpy(path, head);
		wcscat(path, com[2]);
		for (int i = 3; wcslen(com[i]) != 0; ++i)
		{
			wcscat(path, L" ");
			wcscat(path, com[i]);
		}
		if (_waccess(path, F_OK))
		{
			color(lred);
			wprintf(L"%ls 不存在 !\n", path);
			color(grey);
		}
		else
		{
			color(lgreen);
			wprintf(L"%ls 可用 !\n", path);
			if (!(path[wcslen(path) - 1] == '/' || path[wcslen(path) - 1] == '\\'))
			{
				wcscat(path, L"/");
			}
			wcscpy(head, path);
			color(grey);
		}
		return;
	}
	/* 绝对路径 */
	for (int i = 2; wcslen(com[i]) != 0; ++i)
	{
		wcscat(com[1], L" ");
		wcscat(com[1], com[i]);
	}
	if (_waccess(com[1], F_OK))
	{
		color(lred);
		wprintf(L"%ls 不存在 !\n", com[1]);
		color(grey);
	}
	else
	{
		color(lgreen);
		wprintf(L"%ls 可用 !\n", com[1]);
		if (!(com[1][wcslen(com[1]) - 1] == '/' || com[1][wcslen(com[1]) - 1] == '\\'))
		{
			wcscat(com[1], L"/");
		}
		wcscpy(head, com[1]);
		color(grey);
	}
}
/* 打开文件 */
void openfile()
{
	wc h[256];
	wcscpy(h, head);
	wc *st = wcscat(head, com[1]);
	if (_waccess(st, F_OK))
	{
		color(lred);
		wprintf(L"%ls 不存在 !\n", st);
		wcscpy(head, h);
		color(grey);
	}
	else
	{
		wcscpy(file, st);
		color(lgreen);
		wprintf(L"%ls 可用 !\n", file);
		wcscpy(head, h);
		color(grey);
	}
}
/* 读取文件 */
void read()
{
	color(lred);
	wprintf(L"该功能已废除！请改用do r [文件名] 代替！");
	FILE *f = NULL;
	f = _wfopen(file, L"r");
	fseek(f, 0, SEEK_END);
	color(cyan);
	wprintf(L"[读取 %s 大小为 %.2fKB]\n", file, ftell(f) / 1000.0);
	color(lyellow);
	fseek(f, 0, SEEK_SET);
	for (; !feof(f);)
	{
		wprintf(L"%lc", fgetwc(f));
	}
	wprintf(L"\n");
	color(grey);
	fclose(f);
}
/* 展示内容 */
void dir()
{
	struct _finddata_t fileinfo;
	long fHandle;
	int i = 0;
	char h[256];
	wcstombs(h, head, 256);
	if ((fHandle = _findfirst(strcat(h, "./*"), &fileinfo)) == -1L)
	{
		color(cyan);
		wprintf(L"当前目录下没有文件\n");
		color(grey);
		return;
	}
	else
	{
		color(cyan);
		wprintf(L"文件大小\t\t\t文件名称\n");
		color(lyellow);
		do
		{
			++i;
			mksize(fileinfo);
		} while (_findnext(fHandle, &fileinfo) == 0);
	}
	color(lgreen);
	_findclose(fHandle);
	wprintf(L"文件数量：%d\n", i);
	color(grey);
}
/* 版本信息 */
void ver()
{
	wprintf(L"\nMarcus [版本 1.0.0000]\n");
}

/* 删除 */
void rm()
{
	if (wcscmp(com[1], L"*") == 0)
	{
		struct _wfinddata_t fileinfo;
		long fHandle;
		int i = 0;
		wc h[256];
		wcscpy(h, head);
		if ((fHandle = _wfindfirst(wcscat(h, L"./*"), &fileinfo)) == -1L)
		{
			color(cyan);
			wprintf(L"当前目录下没有文件\n");
			color(grey);
			return;
		}
		else
		{
			do
			{
				wcscpy(h, head);
				wcscat(h, fileinfo.name);
				if (_wremove(h))
				{
					color(lred);
					wprintf(L"删除失败 %ls ！\n", fileinfo.name);
					color(grey);
				}
				else
				{
					color(lgreen);
					wprintf(L"删除成功 %ls \n", fileinfo.name);
					++i;
					color(grey);
				}
			} while (_wfindnext(fHandle, &fileinfo) == 0);
		}
		color(lgreen);
		_findclose(fHandle);
		wprintf(L"删除文件数量：%d\n", i);
		color(grey);
	}
	else
	{
		wc f[256];
		wcscpy(f, head);
		wcscat(f, com[1]);
		if (_wremove(f))
		{
			color(lred);
			wprintf(L"删除 %ls 失败！\n", f);
			color(grey);
		}
		else
		{
			color(lgreen);
			wprintf(L"成功删除 %ls \n", f);
			color(grey);
		}
	}
}
/* 操作 */
void dofile()
{
	wc h[256];
	wcscpy(h, head);
	wcscat(h, com[2]);
	FILE *f = NULL;
	if ((f = _wfopen(h, com[1])) == NULL)
	{
		color(lred);
		wprintf(L"打开文件失败！\n");
		color(grey);
		fclose(f);
		return;
	}

	if (wcscmp(com[1], L"r") == 0)
	{
		fseek(f, 0, SEEK_END);
		color(cyan);
		wprintf(L"[读取 %ls 大小为 %.2fKB]\n", h, ftell(f) / 1000.0);
		color(lyellow);
		if (ftell(f) < 1)
		{
			fclose(f);
			wprintf(L"文件为空。\n");
			color(grey);
			return;
		}
		fseek(f, 0, SEEK_SET);
		for (; !feof(f);)
		{
			wprintf(L"%lc", fgetwc(f));
		}
		wprintf(L"\n");
		color(grey);
	}
	if (wcscmp(com[1], L"w") == 0)
	{
		if (fputws(com[3], f) < 0)
		{
			color(lred);
			wprintf(L"操作失败！\n");
			color(grey);
		}
		else
		{
			color(lgreen);
			wprintf(L"操作成功！\n");
			color(grey);
		}
	}
	if (wcscmp(com[1], L"a") == 0)
	{
		if (fputws(com[3], f) < 0)
		{
			color(lred);
			wprintf(L"操作失败！\n");
			color(grey);
		}
		else
		{
			color(lgreen);
			wprintf(L"操作成功！\n");
			color(grey);
		}
	}
	fclose(f);
}
/* 打开程序/网站 */
void start()
{
	wc s[256] = L"start ";
	wcscat(s, head);
	wcscat(s, com[1]);
	_wsystem(s);
}
void init()
{
	setlocale(LC_ALL, "chs");
	memset(com, 0, sizeof(com));
	memset(head, 0, sizeof(head));
	memset(file, 0, sizeof(file));
	GetTempPathW(sizeof(head), head);
}
