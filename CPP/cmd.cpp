#include "F:/c/headfile/cmds.h"

void (*cmds[])(void) = {&cd, &openfile, &mv, &read, &ren, &dir, &help, &rm, &ver, &dofile, &start, &cls};
	 
wchar_t cmd[CMDSIZE][16] =
{
	L"cd",
	L"open",
	L"mv",
	L"_read_",
	L"ren",
	L"dir",
	L"help",
	L"rm",
	L"ver",
	L"do",
	L"start",
	L"cls"
};

int main()
{
	init();
	for (;;)
	{
goto_back:
		input();
		for (int j = 0; j < CMDSIZE; ++j)
		{
			if (wcscmp(com[0], cmd[j]) == 0)
			{
				(*cmds[j])();
				goto goto_back;
			}
		}
		color(lred);
		wprintf(L"不是有效的命令！\n");
		color(grey);
	}
	return 0;

}
