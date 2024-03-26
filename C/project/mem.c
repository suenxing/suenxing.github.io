#include <stdio.h>
#include <windows.h>
#include <locale>
#include <io.h>
#include <random>

#define SEED 131

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

int money = 0;
wc uch[] = L"□"; /* ░▒▓█■□△▲▼▽○●◆◇□■★☆▷▶◀◁♤♠♥♡♢♦♣♧ */
wc ws[] = L"，。、‘’；“”【】、（）！《》？ \n\t　1234567890";

/* 更改控制台文字颜色 */
void color(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x % 16);
}

/* 随机数 */
unsigned int ran32(unsigned int x)
{
    return x ^= (x ^= (x ^= x << 13) >> 17) << 5;
}

/* 保存数据 */
void saveData()
{
    FILE *data = fopen("txt.data", "w");
    fprintf(data, "%d", money);
}

/* 初始化 */
void init()
{
    FILE *data;
    if (access("txt.data", 0))
    {
        data = fopen("txt.data", "w");
    }
    else
    {
        data = fopen("txt.data", "r");
    }

    if (data == NULL)
    {
        wprintf(L"啊哦，出错了，无法打开txt.data文件\n");
        system("pause");
        exit(-1);
        
    }
    fscanf(data, "%d", &money);
    fclose(data);
}

/* 直接默写模式 */
void recite3()
{
    char s[256];
    wc word[512], in[512];
    unsigned short p = 0, len = 0, times = 0;
    FILE *text = NULL;
    wc ch;

    wprintf(L"[直接默写]默写方法：系统输出上文，你写出下文\n");

    do
    {
        wprintf(L"请输入要背诵的文本的路径【不能有空格！】（可拖拽文本文件到此处以输入绝对路径）：");
        scanf("%s", s);
        fflush(stdin);

        /* 判断文件是否可行 */
        if ((text = fopen(s, "r")) == NULL)
        {
            wprintf(L"文件打不开！\n");
        }
        else
        {
            break;
        }
    } while (1);

    color(lwhite);
    wprintf(L"[系统]");

    /* 正片开始 */
    for (; !feof(text);)
    {

        ch = fgetwc(text);
        wprintf(L"%lc", ch);
        for (int i = 0; i < sizeof(ws) / sizeof(ws[0]); ++i)
        {
            if (ch == ws[i])
            {
                p = !p;
                len = 0;

                for (; !feof(text);)
                {
                    ch = fgetwc(text);
                    for (int i = 0; i < sizeof(ws) / sizeof(ws[0]); ++i)
                    {
                        if (ch == ws[i])
                        {
                            p = !p;
                            word[len] = L'\0';
                            wprintf(L"%lc\n", ch);
                            goto gotoOUT;
                        }
                    }
                    word[len++] = ch;
                    wprintf(uch);
                }

            gotoOUT:
                color(grey);
                wscanf(L"%s", &in);
                fflush(stdin);

                do
                {
                    color(grey);
                    wscanf(L"%s", &in);
                    fflush(stdin);

                    if (!wcscmp(word, in)) /* 是否相同 */
                    {
                        color(lgreen);
                        wprintf(L"> 输入正确 金币+1 <\n");
                        ++money;
                        break;
                    }

                    if (++times >= 5)
                    {
                        color(lred);
                        wprintf(L"> 试错过多，正确答案为");
                        color(lpurple);
                        wprintf(L" %ls ", word);
                        color(lred);
                        wprintf(L"<\n");
                        times = 0;
                        break;
                    }
                    else
                    {
                        color(lred);
                        wprintf(L"> 输入有误 金币-1 <\n");
                        --money;
                    }
                } while (1);

                color(lwhite);
                wprintf(L"[系统]");

                break;
            }
        }
    }
}

/* 开头无空模式 */
void recite2()
{
    char s[256];
    FILE *text = NULL;
    wc ch;

    wprintf(L"[开头无空]背诵方法：系统输出残缺的全文，你通过残缺部分的提示，完整地背出全文。请先读熟后再背诵\n");

    do
    {
        wprintf(L"请输入要背诵的文本的路径【不能有空格！】（可拖拽文本文件到此处以输入绝对路径）：");
        scanf("%s", s);
        fflush(stdin);

        /* 判断文件是否可行 */
        if ((text = fopen(s, "r")) == NULL)
        {
            wprintf(L"文件打不开！\n");
        }
        else
        {
            break;
        }
    } while (1);

    color(lwhite);
    wprintf(L"[系统]");

    /* 正片开始 */
    for (; !feof(text);)
    {
    gotoCONTINUE:
        ch = fgetwc(text);

        for (int i = 0; i < sizeof(ws) / sizeof(ws[0]); ++i)
        {
            if (ch == ws[i])
            {
                wprintf(L"%lc%lc", ch, fgetwc(text));
                goto gotoCONTINUE;
            }
        }

        wprintf(uch);
    }
    color(lyellow);
    printf("\n");
    system("pause");
}

/* 随机设空模式 */
void recite1()
{
    char s[256];
    unsigned short p = 0;
    FILE *text = NULL;

    wc ch;

    wprintf(L"[随机设空]背诵方法：系统输出残缺的全文，你通过残缺部分的提示，完整地背出全文。请先读熟后再背诵\n");

    do
    {
        wprintf(L"请输入要背诵的文本的路径【不能有空格！】（可拖拽文本文件到此处以输入绝对路径）：");
        scanf("%s", s);
        fflush(stdin);

        /* 判断文件是否可行 */
        if ((text = fopen(s, "r")) == NULL)
        {
            wprintf(L"文件打不开！\n");
        }
        else
        {
            break;
        }
    } while (1);

    wprintf(L"请输入空占比（单位：%%）：");
    scanf("%hu", &p);
    fflush(stdin);

    while (1)
    {
        if (1 <= p && p <= 100)
            break;
        wprintf(L"输入有误！需在1~100之间\n");
        scanf("%hu", &p);
        fflush(stdin);
    }

    color(lwhite);
    wprintf(L"[系统]");

    /* 正片开始 */
    for (unsigned int i=0; !feof(text);++i)
    {

        ch = fgetwc(text);

        for (int i = 0; i < sizeof(ws) / sizeof(ws[0]); ++i)
        {
            if (ch == ws[i])
            {
                goto gotoLOOP;
            }
        }
        srand((unsigned)time(NULL));
        if (ran32(((i+(unsigned)time(NULL)+rand())*ch)&0x7FFFFFFF)%100<= p)
        {
            /* ░▒▓█■□△▲▼▽○●◆◇□■★☆▷▶◀◁♤♠♥♡♢♦♣♧ */
            wprintf(uch);
        }
        else
        {
        gotoLOOP:
            wprintf(L"%lc", ch);
        }
    }
    color(lyellow);
    printf("\n");
    system("pause");
}

/* 抄写模式 */
void copy()
{
    unsigned int len = 0;
    char s[256];

    FILE *text = NULL;
    wc m[512], in[512];
    wc ch;
    wc ws[] = L"，。、‘’；“”【】、（）！《》？";

    wprintf(L"抄写方法：系统出一句，你就打一句（按Enter键提交），越专注记得越牢，边抄读效果更好~\n");

    do
    {
        wprintf(L"请输入要背诵的文本的路径【不能有空格！】（可拖拽文本文件到此处以输入绝对路径）：");
        scanf("%s", s);
        fflush(stdin);

        /* 判断文件是否可行 */
        if ((text = fopen(s, "r")) == NULL)
        {
            wprintf(L"文件打不开！\n");
        }
        else
        {
            break;
        }
    } while (1);

    color(lwhite);
    wprintf(L"[系统]");
    /* 正片开始 */
    for (; !feof(text);)
    {
        ch = fgetwc(text);
        for (int i = 0; i < sizeof(ws) / sizeof(ws[0]); ++i)
        {
            if (ch == ws[i])
            {
                ch = fgetwc(text);
                wprintf(L"\n");
                m[len] = L'\0';
                len = 0;

                do
                {
                    color(grey);
                    wscanf(L"%s", &in);
                    fflush(stdin);

                    if (!wcscmp(m, in)) /* 是否相同 */
                    {
                        color(lgreen);
                        wprintf(L"> 输入正确 金币+1 <\n");
                        ++money;
                        break;
                    }
                    else
                    {
                        color(lred);
                        wprintf(L"> 输入有误 金币-1 <\n");
                        --money;
                    }
                } while (1);

                color(lwhite);
                wprintf(L"[系统]");

                break;
            }
        }
        m[len++] = ch;
        wprintf(L"%lc", ch);
    }
    color(lyellow);
    wprintf(L"[系统]背书完成！奖励 100 金币\n");
}

/* 菜单 */
void menu()
{
    int select;
    color(lyellow);
    wprintf(
        L"=================================\n"
        L"=\t背文程序a4.2 by Marcus\t=\n"
        L"=\t拥有金币：%d\t\t=\n"
        L"=\t[1]逐句抄写模式\t\t=\n"
        L"=\t[2]随机设空模式\t\t=\n"
        L"=\t[3]开头无空模式\t\t=\n"
        L"=\t[4]直接默写模式\t\t=\n"
        L"=\t[0]退出背文程序\t\t=\n",
        money);
gotoMENU:
    scanf("%d", &select);
    fflush(stdin);
    switch (select)
    {
    case 4:
        system("cls");
        recite3();
        break;
    case 3:
        system("cls");
        recite2();
        break;
    case 2:
        system("cls");
        recite1();
        break;
    case 1:
        /* SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){0, 0}); */
        system("cls");
        copy();
        break;
    case 0:
        exit(0);
        break;
    default:
        goto gotoMENU;
        break;
    }
}

/* 哈希函数 */
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131313; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

/* 卡密 */
void kami()
{
    char pw[32];
    color(lyellow);
    wprintf(L"请输入卡密：");
    while (1)
    {
        scanf("%32s", pw);
        fflush(stdin);
        /* fDHO#Aw4RTXKb&zC:8pjMO2Hw[oa4~ 189955908 */
        if (BKDRHash(pw) == 189955908)
        {
            wprintf(L"卡密正确！\n");
            system("cls");
            break;
        }
        else
        {
            color(lred);
            wprintf(L"卡密不正确！\n");
        }
    }
}

int main()
{
    setlocale(LC_ALL, "chs");
    //kami();
    menu();
    system("pause");
    return 0;
}
